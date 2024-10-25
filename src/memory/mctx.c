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
#include "utils.h"

MemoryContext CURRENT_MEMORY_CONTEXT;

MemoryContext TOP_MEMORY_CONTEXT;
MemoryContext MESSAGE_MEMORY_CONTEXT;


/* Create MemoryContext.
 * Thist abstract function not really to create MemoryContext and it just
 * make up base info and link to others MemoryContext.
 * */
MemoryContext MemoryContextCreate(MemoryContext node, MemoryContext parent, 
                                  const char *name, ContextType type) {

    /* Make up base Info. */
    node->name = name;
    node->type = type;
    node->parent = parent;
    node->allocated_size = 0;
    node->firstChild = NULL;
    node->presChild = NULL;
    node->nextChild = NULL;
    
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
