#include "mctx.h"
#include <stdint.h>

typedef struct AllocBlockData *AllocBlock;
typedef struct AllocSetContext *AllocSet;

typedef struct AllocSetContext{
    MemoryContextData header;   /* Implement standard MemoryContext and must position first */
    AllocBlock blocks;         /* Header of AllocBlock list. */
} AllocSetContext;

typedef struct AllocBlockData {
    AllocSet set;
    AllocBlock pres;
    AllocBlock next;
    char *freeptr;          /* Start of free space of this block. */
    char *endptr;           /* End of free space of this block. */
} AllocBlockData;

typedef struct AllocChunkData {
    uint32_t offset;
} AllocChunkData;

#define ALLOC_SET_CXT_SIZE sizeof(AllocSetContext)
#define ALLOC_BLOCK_SIZE sizeof(AllocBlockData)
#define ALLOC_CHUNK_SIZE sizeof(AllocChunkData)

#define FETCH_ALLOC_BLOCK(set) (AllocBlockData *)((char *)set + ALLOC_BLOCK_SIZE)


/* The implement MemoryContextCreate in AllocSetContext. */
MemoryContext AllocSetMemoryContextCreate(MemoryContext parent, char *name, uint32_t max_block_size);

/* Allocate from AllocSetContext. */
void *AllocSetAlloc(MemoryContext context, size_t size);


