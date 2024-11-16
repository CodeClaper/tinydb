/***************************** Memory Context Module. *************************************** 
 * Auth:        JerryZhou 
 * Created:     2024/10/16 
 * Modify:      2024/10/16 
 * Locataion:   src/memory/mectx.c
 *
 *********************************************************************************************/

#include <stdint.h>
#include <time.h>
#include "data.h"
#include "mctx.h"
#include "asctx.h"
#include "utils.h"

MemoryContext CURRENT_MEMORY_CONTEXT;

MemoryContext TOP_MEMORY_CONTEXT;
MemoryContext MESSAGE_MEMORY_CONTEXT;


static MemoryContextMethods mctx_methods[] = {
    /* AllocSetContext implements. */
    [ALLOC_SET_ID].alloc = AllocSetAlloc,
    [ALLOC_SET_ID].free = AllocSetFree,
    [ALLOC_SET_ID].realloc = AllocSetRealloc,
    [ALLOC_SET_ID].delete_context = AllocSetDelete
};


/* Create MemoryContext.
 * Thist abstract function not really to create MemoryContext and it just
 * make up base info and link to others MemoryContext.
 * */
MemoryContext MemoryContextCreate(MemoryContext node, MemoryContext parent, 
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

    return node;
}

void MemoryContextDelete(MemoryContext node, ContextType type) {

}


void *MemoryContextSwitchTo(MemoryContext currentConext) {
    MemoryContext old = currentConext;
    CURRENT_MEMORY_CONTEXT = currentConext;
    return old;
}
