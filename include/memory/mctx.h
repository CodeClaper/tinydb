#include "data.h"

#ifndef MCTX_H
#define MCTX_H

typedef enum {
    ALLOC_SET_CTX
} ContextType;

typedef struct MemoryContextData* MemoryContext; 

typedef struct MemoryContextData {
    const char *name;
    ContextType type;
    uint32_t allocated_size;
    MemoryContext parent;
    MemoryContext firstChild;
    MemoryContext presChild;
    MemoryContext nextChild;
} MemoryContextData;


/* Create MemoryContext.
 * Thist abstract function not really to create MemoryContext and it just
 * make up the relation of MemoryContext.
 * */
MemoryContext MemoryContextCreate(MemoryContext node, MemoryContext parent, const char *name, ContextType type);

void MemoryContextDelete(MemoryContext node, ContextType type);

#endif
