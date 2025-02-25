#include <stdbool.h>
#include <string.h>
#include "rwlock.h"
#include "shmem.h"
#include "utils.h"

#ifndef BUFMGR_H
#define BUFMGR_H

typedef int BlockNum;
typedef int Buffer;

/* Use half of shared memory to store buffer. 
 * So the BUFFER_SLOT_NUM as flowing. */
#define BUFFER_SLOT_NUM  ((SHMEM_SIZE) / (2 * PAGE_SIZE))

/* Buffer tag. */
typedef struct BufferTag {
    char tableName[MAX_TABLE_NAME_LEN];
    BlockNum blockNum;
} BufferTag;

/* Buffer Desc. */
typedef struct BufferDesc {
    Buffer buffer;          /* Buffer value, corresponding to page number. */
    volatile int refcount;  /* Reference count. */
    RWLockEntry *lock;      /* RW lock. */
    s_lock      io_lock;    /* IO lock.*/
} BufferDesc;


/* Return if both BufferTags equals. */
static inline bool BufferTagEquals(BufferTag *tag1, BufferTag *tag2) {
    return (tag1->blockNum == tag2->blockNum) 
                && streq(tag1->tableName, tag2->tableName);
}

/* Return if the BufferTag is empty. */
static inline bool BufferTagEmpty(BufferTag tag) {
    return is_null(tag.tableName) && tag.blockNum == 0;
}

/* Make the BufferTag empty. */
static inline void MakeBufferTagEmpty(BufferTag *tag) {
    tag->blockNum = 0;
    memset(tag->tableName, 0, MAX_TABLE_NAME_LEN);
}

/* Init BufMgr. */
void InitBufMgr();

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
