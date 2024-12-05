#include "exlock.h"

#ifndef BUFMGR_H
#define BUFMGR_H

typedef int Buffer;

/* Buffer Desc. */
typedef struct BufferDesc {
    Buffer buffer;          /* Buffer value, corresponding to page number. */
    volatile int refcount;  /* Reference count. */
    ExLockEntry *lock;      /* Exclusive lock. */
} BufferDesc;

/* Read Buffer.
 * Get shared buffer data via Buffer value. 
 * */
void *ReadBuffer(Table *table, Buffer buffer);

/* Read Buffer Inner.
 * Get shared buffer data via Buffer value. 
 * */
void *ReadBufferInner(char *table_name, Pager *pager, Buffer buffer);

/* Release Buffer.
 * Release Buffer after using. 
 * And the function is called aftert ReadBuffer. 
 * */
void ReleaseBuffer(Table *table, Buffer buffer);

/* Release Buffer Inner.
 * Release Buffer after using. 
 * And the function is called aftert ReadBuffer. 
 * */
void ReleaseBufferInner(Pager *pager, Buffer buffer);

/* LocK Buffer. 
 * Try to acquire the exclusive content lock in BufferDesc.
 * */
void LockBuffer(Table *table, Buffer buffer);

/* Unlock Buffer
 * Unlock the exclusive content lock in BufferDesc.
 * */
void UnlockBuffer(Table *table, Buffer buffer);

#endif
