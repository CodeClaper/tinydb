/***************************************** Buffer Manager Module ****************************************
 * Auth:        JerryZhou
 * Created:     2024/12/04
 * Modify:      2024/12/04
 * Locataion:   src/memory/bufmgr.c
 * Description: The buffer manager supports the way to manipulate the page data.
 * Not recommand that you get page data via the pager manager direactly, but the buffer manager indireactly.
 * This module aims to avoid page data update conficting and minimize the impact on read and write performance 
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
#include "log.h"

/*
 * Sync Lock. 
 */
static s_lock *sync_lock;

/* Pager size valid.
 * The pager pages size may equals to the buffer size or less one when not synchronized.
 * */
#define PAGER_SIZE_VALID(pager)\
    ((pager->size == pager->buffers->size) || (pager->size == pager->buffers->size - 1))

/* Check Pager Buffers valid. */
static void CheckPagerBuffersValid(Pager *pager) {
    Assert(pager->buffers != NULL);
    /* Double check to avoid cache issue. */
    assert_true(PAGER_SIZE_VALID(pager) || PAGER_SIZE_VALID(pager), 
                "Pager size %d != buffer size %d", 
                pager->size, 
                pager->buffers->size);
}

/* Create BufferDesc. */
static BufferDesc *CreateBufferDesc(Buffer buffer) {
    Assert(in_shared_memory());
    /* Generate new Buffer. */
    BufferDesc *buff_desc = instance(BufferDesc);
    buff_desc->refcount = 0;
    buff_desc->buffer = buffer; 
    init_spin_lock(&buff_desc->io_lock);
    buff_desc->lock = instance(RWLockEntry);
    InitRWlock(buff_desc->lock, buffer);
    return buff_desc;
}

/* Init BufMgr. */
void InitBufMgr() {
    switch_shared();
    sync_lock = instance(s_lock);
    init_spin_lock(sync_lock);
    switch_local();
}

/* Read Buffer.
 * Get shared buffer data via Buffer value. */
void *ReadBuffer(Table *table, Buffer buffer) {
    return ReadBufferInner(
        get_table_name(table), 
        table->pager, 
        buffer
    );
}

/* Read Buffer.
 * Get shared buffer data via Buffer value. */
void *ReadBufferInner(char *table_name, Pager *pager, Buffer buffer) {

    /* Check Pager Buffer valid. */
    CheckPagerBuffersValid(pager);

    /* If buffers missing the buffer, we will create the 
     * BufferDesc, and store it in shared memory. */
    if (buffer >= pager->buffers->size) {
        acquire_spin_lock(sync_lock);

        /* Double check. */
        if (buffer >= pager->buffers->size) {
            switch_shared();

            BufferDesc *buff_desc = CreateBufferDesc(buffer);
            append_list(pager->buffers, buff_desc);

            switch_local();
        }

        release_spin_lock(sync_lock);
    }

    ListCell *lc = list_nth_cell(pager->buffers, buffer);
    if (lfirst(lc) == NULL) {
        acquire_spin_lock(sync_lock);
        
        /* Double check. */
        lc = list_nth_cell(pager->buffers, buffer);
        if (lfirst(lc) == NULL) {
            switch_shared();

            BufferDesc *buff_desc = CreateBufferDesc(buffer);
            lfirst(lc) = buff_desc;

            switch_local();
        }

        release_spin_lock(sync_lock);
    }

    BufferDesc *buff_desc = lfirst(lc);
    
    /* Acquire the Rwlock in RW_READERS mode. */
    AcquireRWlock(buff_desc->lock, RW_READERS);

    db_log(TRACE, "Acquire RWLock: %p and buffer: %d and owner: %d and writer: %d and reader: %d.", 
           buff_desc, buff_desc->buffer, buff_desc->lock->owner->size, buff_desc->lock->waiting_writer, buff_desc->lock->waiting_reader);
    
    /* Increase the refcount. */
    buff_desc->refcount++;

    /* Get the shared buffer data. */
    return get_page(table_name, pager, buffer);
}

/* Release Buffer.
 * Release Buffer after using. 
 * And the function is called aftert ReadBuffer. */
void ReleaseBuffer(Table *table, Buffer buffer) {
    ReleaseBufferInner(table->pager, buffer);
}

/* Release Buffer Inner.
 * Release Buffer after using. 
 * And the function is called aftert ReadBuffer. 
 * */
void ReleaseBufferInner(Pager *pager, Buffer buffer) {

    /* Check Pager Buffer valid. */
    CheckPagerBuffersValid(pager);

    ListCell *lc = list_nth_cell(pager->buffers, buffer);
    BufferDesc *buff_desc = (BufferDesc *) lfirst(lc);
    Assert(buff_desc != NULL);

    db_log(TRACE, "Will release RWLock: %p and buffer: %d and owner: %d and writer: %d and reader: %d.", 
           buff_desc, buff_desc->buffer, buff_desc->lock->owner->size, buff_desc->lock->waiting_writer, buff_desc->lock->waiting_reader);

    /* Release the Rwlock. */
    ReleaseRWlock(buff_desc->lock);

    /* Descrease the refcount. */
    buff_desc->refcount--;
}


/* Lock Buffer. 
 * Try to acquire the exclusive content lock in BufferDesc. 
 * */
void LockBuffer(Table *table, Buffer buffer) {
    Pager *pager = table->pager;

    /* Check Pager Buffer valid. */
    CheckPagerBuffersValid(pager);

    /* If buffers missing the buffer, we will create the 
     * BufferDesc, and store it in shared memory. */
    if (buffer >= pager->buffers->size) {
        acquire_spin_lock(sync_lock);

        /* Double check. */
        if (buffer >= pager->buffers->size) {
            switch_shared();

            BufferDesc *buff_desc = CreateBufferDesc(buffer);
            append_list(pager->buffers, buff_desc);

            switch_local();
        }

        release_spin_lock(sync_lock);
    }

    ListCell *lc = list_nth_cell(pager->buffers, buffer);
    if (lfirst(lc) == NULL) {
        acquire_spin_lock(sync_lock);
        
        /* Double check. */
        lc = list_nth_cell(pager->buffers, buffer);
        if (lfirst(lc) == NULL) {
            switch_shared();

            BufferDesc *buff_desc = CreateBufferDesc(buffer);
            lfirst(lc) = buff_desc;

            switch_local();
        }
        release_spin_lock(sync_lock);
    }

    BufferDesc *buff_desc = lfirst(lc);
    Assert(buff_desc != NULL);

    /* Try to acquire the exclusive lock. */
    AcquireRWlock(buff_desc->lock, RW_WRITER);
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

    /* Release the writer lock. */
    ReleaseRWlock(buff_desc->lock);
}

