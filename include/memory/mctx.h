#include "data.h"

#ifndef MCTX_H
#define MCTX_H

typedef struct MemoryContextData* MemoryContext; 

typedef struct MemoryContextData {
    uint32_t alloc_size;
    char name[MAX_COLUMN_NAME_LEN];
    MemoryContext parent;
    MemoryContext firstChild;
    MemoryContext pres;
    MemoryContext next;
} MemoryContextData;

#endif
