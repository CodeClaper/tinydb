/***************************** Shared Memory Module *****************************************
 * Auth:        JerryZhou
 * Created:     2024/10/24
 * Modify:      2024/10/25
 * Locataion:   src/memory/asctx.c
 * 
*********************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "asctx.h"
#include "mctx.h"
#include "mctx.h"
#include "mem.h"
#include "bit.h"
#include "utils.h"
#include "asserts.h"

void *AllocSetAllocNewBlock(MemoryContext context, size_t size);
void *AllocSetAllocChunkFromBlock(MemoryContext context, AllocBlock block, size_t size);

/* Index of AllocSet free size 
 * --------------------------
 * At this pointer we must compute ceil(log2(size >> ALLOC_MINBITS))
 * This is the same as
 *      leftmost_32_pos((size - 1) >> ALLOC_MINBITS) + 1
 * or equivalently
 *      leftmost_32_pos(size - 1) - ALLOC_MINBITS + 1
 * -------------------------
 * */
static inline int AllocSetFreeIndex(size_t size) {
    int idx = size > (1 << ALLOC_MINBITS) 
            ? leftmost_32_pos(size -1) - ALLOC_MINBITS + 1
            : 0;
    Assert(idx < ALLOC_FREELISTS_NUM);
    return idx;
}

/* The implement MemoryContextCreate in AllocSetContext. */
MemoryContext AllocSetMemoryContextCreate(MemoryContext parent, char *name, uint32_t max_block_size) {
    size_t blk_size;
    AllocSet set;
    AllocBlock block;

    /* Block size at least include AllocSetContext size + AllocBlock size + at lest one AllocChunk size.*/
    blk_size = ALLOC_SET_CXT_SIZE + ALLOC_BLOCK_SIZE + ALLOC_CHUNK_SIZE;
    blk_size = max_size(blk_size, max_block_size);
    blk_size = MAXALIGN(blk_size);

    /* Alloc from system. */
    set = (AllocSet) malloc(blk_size);

    /* Assignment. */
    block = KEEPER_ALLOC_BLOCK(set);
    block->set = set;
    block->pres = NULL;
    block->next = NULL;
    block->freeptr = ((char *) block) + ALLOC_BLOCK_SIZE;
    block->endptr = ((char *) set) + blk_size;

    set->blocks = block;
    set->next_block_size = max_block_size;

    return MemoryContextCreate((MemoryContext) set, 
                               NULL, 
                               "AllocSet", 
                               ALLOC_SET_CTX, 
                               ALLOC_SET_ID);
}

/* Allocate from AllocSetContext. */
void *AllocSetAlloc(MemoryContext context, size_t size) {

    size_t blk_size, free_size;
    int fdx;
    AllocChunk chunk;

    AllocSet set = (AllocSet) context;
    Assert(set->blocks);
    AllocBlock block = set->blocks;

    /* Find there is enough chunk in FreeList. */
    fdx = AllocSetFreeIndex(size);
    chunk = set->free_list[fdx];
    if (non_null(chunk)) {
        set->free_list[fdx] = chunk->next;
        return CHUNK_GET_POINTER(chunk);
    }

    blk_size = MAXALIGN(ALLOC_CHUNK_SIZE + size);

    /* Get block free space size. 
     * If it has enough free space, allocate from current block. 
     * Otherwise, generate new block and allocate from that. */
    free_size = block->endptr - block->freeptr;
    if (free_size < size) 
        return AllocSetAllocNewBlock(context, size);

    /* There is enough space on the block. */
    return AllocSetAllocChunkFromBlock(context, block, size);
}


/* Allocate Chunk from Current Block. */
void *AllocSetAllocChunkFromBlock(MemoryContext context, AllocBlock block, size_t size) {
    /* Allocate chunk must less max limit.*/
    Assert(size < MAX_ALLOC_CHUNK_SIZE);
    AllocChunk chunk = (AllocChunk) block->freeptr;
    block->endptr += (size + ALLOC_CHUNK_SIZE);
    chunk->offset = block->freeptr - (char *)block;
    chunk->msize = size;
    chunk->next = NULL;
    Assert(block->freeptr <= block->endptr);
    return CHUNK_GET_POINTER(chunk);
}


/* Allocate from New Block. */
void *AllocSetAllocNewBlock(MemoryContext context, size_t size) {
    size_t blk_size;
    AllocSet set = (AllocSet) context;

    Assert(set->blocks != NULL); 

    blk_size = set->next_block_size;
    AllocBlock block = (AllocBlock) malloc(blk_size);

    block->freeptr = ((char *) block) + ALLOC_BLOCK_SIZE;
    block->endptr = ((char *) block) + blk_size;
    block->set = set;
    block->next = set->blocks;
    block->pres = NULL;

    set->blocks->pres = block;
    set->blocks = block;

    context->allocated_size += blk_size;

    return AllocSetAllocChunkFromBlock(context, block, size);
}

/* Free in AllocSetContext. */
void AllocSetFree(void *ptr) {
    Assert(ptr);
    AllocChunk chunk = POINTER_GET_CHUNK(ptr);
    AllocBlock block = CHUNK_GET_BLOCK(chunk);
    AllocSet set = block->set;
    int fdx = AllocSetFreeIndex(chunk->msize);
    chunk->next = set->free_list[fdx];
    set->free_list[fdx] = chunk;
}

/* Reallocate in AllocSetContext. */
void *AllocSetRealloc(void *ptr, size_t size) {

    AllocChunk chunk = POINTER_GET_CHUNK(ptr);
    AllocBlock block = CHUNK_GET_BLOCK(chunk);
    AllocSet set = block->set;
    int fdx = AllocSetFreeIndex(chunk->msize);
    size_t old_size = CHUNK_GET_SIZE_FROM_FREE_LIST_IDX(fdx);

    if (old_size >= size) 
        return ptr; 
    else {
        void *nptr = AllocSetAlloc((MemoryContext) set, size);
        memcpy(nptr, ptr, old_size);
        AllocSetFree(ptr);
        return nptr;
    }
}

/* Reset AllocSetContext. 
 * Free all memory which is allocated in the given set.
 * */
void AllocSetReset(MemoryContext context) {
    AllocSet set = (AllocSet) context;
    AllocBlock block = set->blocks;

    while (non_null(block)) {
        AllocBlock next = block->next;
        context->allocated_size -= block->endptr - ((char *) block);
        free(block);
        block = next;
    }
}

/* Delete AllocSetContext. 
 * Free all memory which is allocated in the given set.
 * Unlike AllocSetReset, this will also free AllocSet self.
 * */
void AllocSetDelete(MemoryContext context) {
    AllocSetReset(context);
    free((AllocSet) context);
}


