/***************************************** Buffer Manager Module ****************************************
 * Auth:        JerryZhou
 * Created:     2024/12/04
 * Modify:      2024/12/04
 * Locataion:   src/memory/bufmgr.c
 * Description: The buffer manager supports the way to manipulate the page data.
 * Not recommand that you get data via the pager manager direactly, but the buffer manager indireactly.
 * It aims to avoid page data update conficting and minimize the impact on read and write performance 
 * in concurrent scenarios.
 *
 * -----------------
 * Basic routine:
 *   (1) Lockless routine:
 *       ReadBuffer -> ReleaseBuffer
 *   (2) Lock routine:
 *       ReadBuffer -> LockBuffer -> UnlockBuffer -> ReleaseBuffer
 *
 * -----------------
 * Lockless routine
 * Get data via ReadBuffer and manipulate without lock. These lockless manipulations includes:
 *   (1) update row
 *   (2) append row witout moving page data.
 *
 * It`s not neccessary to use locking mechanisma for manipulation (1) and (2) under the MVVC mechanism.
 *
 * When we get data via ReadBuffer and the refcount will increase. The refcount is import for
 * LockBuffer. After using the page data, must to release the data via ReadBuffer. And the 
 * refcount will descrease.
 *
 * ---------------
 * Lock routine:
 * Get data via ReadBuffer and then if you want to manipulate the data exclusivly, call LockBuffer. 
 * These lock manipulations includes:
 * (1) Move page data.
 * (2) Split page.
 *
 * When calling LockBuffer, it maybe block until satisfing two condition:
 * (1) Acquire the exclusive lock.
 * (2) The refcount to be one (only itself).
 * It release the exclusive content lock via UnlockBuffer.
 ************************************************************************************************************
 */

#include <unistd.h>
#include "bufmgr.h"
#include "asserts.h"
#include "mmgr.h"
#include "table.h"
#include "pager.h"


/* Check Pager Buffers valid. */
static void CheckPagerBuffersValid(Pager *pager) {
    Assert(pager->buffers != NULL);
    Assert(pager->size == pager->buffers->size);
}

/* Create BufferDesc. */
static BufferDesc *CreateBufferDesc(Buffer buffer) {
    /* Generate new Buffer. */
    BufferDesc *buff_desc = instance(BufferDesc);
    buff_desc->refcount = 0;
    buff_desc->buffer = buffer; 
    buff_desc->lock = instance(ExLockEntry);
    init_exlock(buff_desc->lock);
    return buff_desc;
}

/* Read Buffer.
 * Get shared buffer data via Buffer value. 
 * */
void *ReadBuffer(Table *table, Buffer buffer) {
    Pager *pager = table->pager;

    /* Check Pager Buffer valid. */
    CheckPagerBuffersValid(pager);

    /* If buffers missing the buffer, we will create the 
     * BufferDesc, and store it in shared memory. */
    if (buffer >= pager->buffers->size) {
        switch_shared();

        BufferDesc *buff_desc = CreateBufferDesc(buffer);
        append_list(pager->buffers, buff_desc);

        switch_local();
    }

    ListCell *lc = list_nth_cell(pager->buffers, buffer);
    if (lfirst(lc) == NULL) {
        switch_shared();

        BufferDesc *buff_desc = CreateBufferDesc(buffer);
        lfirst(lc) = buff_desc;

        switch_local();
    }

    BufferDesc *buff_desc = lfirst(lc);
    
    /* Wait until the exclusive lock released. */
    wait_for_exlock(buff_desc->lock);
    
    /* Increase the refcount. */
    buff_desc->refcount++;

    /* Get the shared buffer data. */
    return get_page(
        get_table_name(table), 
        table->pager, 
        buffer
    );
}

/* Release Buffer.
 * Release Buffer after using. 
 * And the function is called aftert ReadBuffer. 
 * */
void ReleaseBuffer(Table *table, Buffer buffer) {
    Pager *pager = table->pager;

    /* Check Pager Buffer valid. */
    CheckPagerBuffersValid(pager);

    ListCell *lc = list_nth_cell(pager->buffers, buffer);
    BufferDesc *buff_desc = (BufferDesc *) lfirst(lc);
    Assert(buff_desc != NULL);

    /* Descrease the refcount. */
    buff_desc->refcount--;
}


/* Lock Buffer. 
 * Lock Buffer must satisfy two conditions:
 * (1) Acquire the exclusive lock.
 * (2) The refcount to be one (only itself).
 * */
void LockBuffer(Table *table, Buffer buffer) {
    Pager *pager = table->pager;

    /* Check Pager Buffer valid. */
    CheckPagerBuffersValid(pager);

    /* If buffers missing the buffer, we will create the 
     * BufferDesc, and store it in shared memory. */
    if (buffer >= pager->buffers->size) {
        switch_shared();

        BufferDesc *buff_desc = CreateBufferDesc(buffer);
        append_list(pager->buffers, buff_desc);

        switch_local();
    }

    ListCell *lc = list_nth_cell(pager->buffers, buffer);
    if (lfirst(lc) == NULL) {
        switch_shared();
        BufferDesc *buff_desc = CreateBufferDesc(buffer);
        lfirst(lc) = buff_desc;
        switch_local();
    }

    BufferDesc *buff_desc = lfirst(lc);
    
    /* Try to acquire the exclusive lock. */
    acquire_exlock(buff_desc->lock);

    /* Wait for refcount to one (left only itself). */
    while (buff_desc->refcount != 1) {
        usleep(DEFAULT_SPIN_INTERVAL);
    }
}

/* Unlock Buffer
 * Unlock the exclusive content lock in BufferDesc.
 * */
void UnlockBuffer(Table *table, Buffer buffer) {
    Pager *pager = table->pager;

    /* Check Pager Buffer valid. */
    CheckPagerBuffersValid(pager);

    ListCell *lc = list_nth_cell(pager->buffers, buffer);
    BufferDesc *buff_desc = (BufferDesc *) lfirst(lc);
    Assert(buff_desc != NULL);
    
    /* Try to release the exclusive lock. */
    release_exlock(buff_desc->lock);
}

