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
#include <time.h>
#include "asctx.h"
#include "mctx.h"
#include "mctx.h"
#include "mem.h"
#include "utils.h"

/* The implement MemoryContextCreate in AllocSetContext. */
MemoryContext AllocSetMemoryContextCreate(MemoryContext parent, char *name, uint32_t max_block_size) {
    size_t blk_size;
    AllocSet set;
    AllocBlock block;

    /* Block size at least include AllocSetContext size, AllocBlock size and at lest one AllocChunk size.*/
    blk_size = ALLOC_SET_CXT_SIZE + ALLOC_BLOCK_SIZE + ALLOC_CHUNK_SIZE;
    blk_size = max_size(blk_size, max_block_size);
    blk_size = MAXALIGN(blk_size);

    /* Alloc from system. */
    set = (AllocSet) malloc(blk_size);

    /* Assignment. */
    block = FETCH_ALLOC_BLOCK(set);
    block->set = set;
    block->pres = NULL;
    block->next = NULL;
    block->freeptr = ((char *) block) + ALLOC_BLOCK_SIZE;
    block->endptr = ((char *) block) + blk_size;

    set->blocks = block;

    return MemoryContextCreate((MemoryContext) set, NULL, "", ALLOC_SET_CTX);
}

/* Allocate from AllocSetContext. */
void *AllocSetAlloc(MemoryContext context, size_t size) {
    AllocSet set = (AllocSet) context;
    return NULL;
}
