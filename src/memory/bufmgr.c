/***************************** Buffer Manager Module *****************************************
* Auth:        JerryZhou
* Created:     2024/12/04
* Modify:      2024/12/04
* Locataion:   src/memory/bufmgr.c
* Description: In TinyDb, buffer is corresponding to table page. Not allowed to manipulate
* page directly instead of via buffer.
*
* Basic routine:
*   (1) ReadBuffer -> ReleaseBuffer
*   (2) ReadBuffer -> LockBuffer -> UnlockBuffer -> ReleaseBuffer
*********************************************************************************************
*/

#include <unistd.h>
#include "bufmgr.h"
#include "asserts.h"
#include "mmgr.h"
#include "table.h"
#include "pager.h"

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
    Assert(pager->buffers != NULL);

    /* Expeed buffers. */
    if (buffer > pager->buffers->size) {
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
    Assert(pager->buffers != NULL);

    ListCell *lc = list_nth_cell(pager->buffers, buffer);
    BufferDesc *buff_desc = (BufferDesc *) lfirst(lc);
    Assert(buff_desc != NULL);

    /* Descrease the refcount. */
    buff_desc->refcount--;
}


/* LocK Buffer. 
 * Lock Buffer must satisfy two conditions:
 * (1) Acquire the exclusive lock.
 * (2) The refcount to be one (only itself).
 * */
void LockBuffer(Table *table, Buffer buffer) {
    Pager *pager = table->pager;
    Assert(pager->buffers != NULL);

    /* Expeed buffers. */
    if (buffer > pager->buffers->size) {
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

    /* Wait for refcount to one. */
    while (buff_desc->refcount != 1) {
        usleep(DEFAULT_SPIN_INTERVAL);
    }
}

/* Unlock Buffer
 * Unlock the exclusive content lock in BufferDesc.
 * */
void UnlockBuffer(Table *table, Buffer buffer) {
    Pager *pager = table->pager;
    Assert(pager->buffers != NULL);

    ListCell *lc = list_nth_cell(pager->buffers, buffer);
    BufferDesc *buff_desc = (BufferDesc *) lfirst(lc);
    Assert(buff_desc != NULL);
    
    /* Try to release the exclusive lock. */
    release_exlock(buff_desc->lock);
}

