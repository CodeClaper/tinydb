#include <stdint.h>
#include <stdio.h>
#include "mctx.h"

#define ALLOCSET_NUM_FREELISTS  11

typedef struct AllocBlockData *AllocBlock;
typedef struct AllocSetContext *AllocSet;
typedef struct AllocChunkData *AllocChunk;

typedef struct AllocSetContext{
    MemoryContextData header;                       /* Implement standard MemoryContext and must position first */
    AllocBlock blocks;                              /* Header of AllocBlock list. */
    AllocChunk free_list[ALLOCSET_NUM_FREELISTS];   /* Free chunk list. */ 
    uint32_t next_block_size;                       /* Next block size used when allocating new block. */
} AllocSetContext;

typedef struct AllocBlockData {
    AllocSet set;
    AllocBlock pres;
    AllocBlock next;
    char *freeptr;          /* Start of free space of this block. */
    char *endptr;           /* End of free space of this block. */
} AllocBlockData;

typedef struct AllocChunkData {
    uint32_t offset;            /* The offset to AllocBlock. */
    size_t msize;               /* Allocated memory size.*/
    AllocChunk next;            /* Next AllocChunk, use in free list. */
} AllocChunkData;

#define ALLOC_MINBITS 3             /* Smallest chunk size is 8 bytes. */
#define ALLOC_FREELISTS_NUM 11      /* FreeLists num. */
#define MAX_ALLOC_CHUNK_SIZE  0xFFFFFFFFFF 

#define ALLOC_SET_CXT_SIZE sizeof(AllocSetContext)
#define ALLOC_BLOCK_SIZE sizeof(AllocBlockData)
#define ALLOC_CHUNK_SIZE sizeof(AllocChunkData)

#define KEEPER_ALLOC_BLOCK(set) \
            ((AllocBlockData *) ((char *) set + ALLOC_BLOCK_SIZE))

#define CHUNK_GET_POINTER(chunk) \
            ((void *) ((char *) chunk + ALLOC_CHUNK_SIZE))

#define POINTER_GET_CHUNK(ptr) \
            ((AllocChunkData *) ((char *) ptr - ALLOC_CHUNK_SIZE))

#define CHUNK_GET_BLOCK(chunk) \
            ((AllocBlockData *) ((char *) chunk - chunk->offset))

#define CHUNK_GET_SIZE_FROM_FREE_LIST_IDX(fdx) \
            ((((size_t) 1) << ALLOC_MINBITS) << (fdx))

/* The implement MemoryContextCreate in AllocSetContext. */
MemoryContext AllocSetMemoryContextCreate(MemoryContext parent, char *name, uint32_t max_block_size);

/* Allocate from AllocSetContext. */
void *AllocSetAlloc(MemoryContext context, size_t size);

/* Free in AllocSetContext. */
void AllocSetFree(void *ptr);

/* Reallocate in AllocSetContext. */
void *AllocSetRealloc(void *ptr, size_t size);

/* Reset AllocSetContext. */
void AllocSetReset(MemoryContext context);

/* Delete AllocSetContext. */
void AllocSetDelete(MemoryContext context);

