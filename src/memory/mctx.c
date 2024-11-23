/***************************** Memory Context Module. *************************************** 
 * Auth:        JerryZhou 
 * Created:     2024/10/16 
 * Modify:      2024/10/16 
 * Locataion:   src/memory/mectx.c
 *
 *********************************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "mctx.h"
#include "asctx.h"
#include "utils.h"

MemoryContext CURRENT_MEMORY_CONTEXT = NULL;
MemoryContext TOP_MEMORY_CONTEXT = NULL;
MemoryContext MASTER_MEMORY_CONTEXT = NULL;
MemoryContext CACHE_MEMORY_CONTEXT = NULL;
MemoryContext MESSAGE_MEMORY_CONTEXT = NULL;


static MemoryContextMethods mctx_methods[] = {
    /* AllocSetContext implements. */
    [ALLOC_SET_ID].alloc = AllocSetAlloc,
    [ALLOC_SET_ID].free = AllocSetFree,
    [ALLOC_SET_ID].realloc = AllocSetRealloc,
    [ALLOC_SET_ID].reset = AllocSetReset,
    [ALLOC_SET_ID].delete_context = AllocSetDelete
};

/* MemoryContextInit.
 * Start up the memory-context subsystem. */
void MemoryContextInit(void) {
    TOP_MEMORY_CONTEXT = AllocSetMemoryContextCreate(NULL, "TopMemoryContext", DEFAULT_MAX_BLOCK_SIZE);
    MemoryContextSwitchTo(TOP_MEMORY_CONTEXT);
}


/* Create MemoryContext.
 * Thist abstract function not really to create MemoryContext and it just
 * make up base info and link to others MemoryContext.
 * */
void MemoryContextCreate(MemoryContext node, MemoryContext parent, 
                                  const char *name, ContextType type, 
                                  MemoryContextMethodID id) {
    /* Make up base Info. */
    node->name = name;
    node->type = type;
    node->parent = parent;
    node->allocated_size = 0;
    node->firstChild = NULL;
    node->presChild = NULL;
    node->nextChild = NULL;
    node->context_methods = &mctx_methods[id];
    
    /* Link node to peer nodes. */
    if (non_null(parent)) {
        if (non_null(parent->firstChild)) 
            parent->firstChild->presChild = node;
        parent->firstChild = node;
    }
}

/* MemoryContextReset. 
 * Release all space allocate within a context and also its children contexts. */
void MemoryContextReset(MemoryContext context) {
    context->context_methods->reset(context);
}

/* Delete the MemoryContext. */
void MemoryContextDelete(MemoryContext context) {
    MemoryContext current = context;
    context->context_methods->delete_context(context);
}


/* Switch to MemoryContext. */
void *MemoryContextSwitchTo(MemoryContext currentConext) {
    MemoryContext old = currentConext;
    CURRENT_MEMORY_CONTEXT = currentConext;
    return old;
}


/* Alloc from MemoryContext. */
void *MemoryContextAlloc(size_t size) {
    MemoryContext context = CURRENT_MEMORY_CONTEXT;
    return context->context_methods->alloc(context, size);
}


/* Free from MemoryContext. */
void MemoryContextFree(void *ptr) {
    MemoryContext context = CURRENT_MEMORY_CONTEXT;
    context->context_methods->free(ptr);
}

/* Realloc from MemoryContext. */
void *MemoryContextRealloc(void *pointer, size_t size) {
    MemoryContext context = CURRENT_MEMORY_CONTEXT;
    return context->context_methods->realloc(pointer, size);
}

/* Strdup from MemoryContext. */
char *MemoryContextStrdup(char *str) {
    size_t len = strlen(str) + 1;
    char *nstr = MemoryContextAlloc(len);
    memcpy(nstr, str, len);
    return nstr;
}
