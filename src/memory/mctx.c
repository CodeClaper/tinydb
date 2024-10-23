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

MemoryContext CURRENT_MEMORY_CONTEXT;

MemoryContext TOP_MEMORY_CONTEXT;
MemoryContext MESSAGE_MEMORY_CONTEXT;


MemoryContext MemoryContextCreate(const char* name, MemoryContext parent, uint32_t init_mem_size) {
    return NULL;
}


void MemoryContextDelete(MemoryContext *mContext) {

}


void *MemoryContextSwitchTo(MemoryContext currentConext) {
    MemoryContext old = currentConext;
    CURRENT_MEMORY_CONTEXT = currentConext;
    return old;
}
