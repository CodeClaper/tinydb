#include "data.h"

#ifndef MCTX_H
#define MCTX_H

typedef struct MemoryContextData* MemoryContext; 

typedef enum {
    ALLOC_SET_CTX
} ContextType;

/* The unique identifier of implements of MemoryContext. */
typedef enum MemoryContextMethodID {
    ALLOC_SET_ID
} MemoryContextMethodID;

typedef struct MemoryContextMethods {
    void *(*alloc)(MemoryContext context, size_t size);
    void (*free)(void *ptr);
    void *(*realloc)(void *ptr, size_t size);
    void (*reset)(MemoryContext context);
    void (*delete_context)(MemoryContext context);
} MemoryContextMethods;

typedef struct MemoryContextData {
    const char *name;                           /* MemoryContext name. */
    ContextType type;                           /* MemoryContext type. */
    uint32_t allocated_size;                    /* Has allocated size.*/
    MemoryContextMethods *context_methods;      /* Vertual functon table. */
    MemoryContext parent;                       /* The parent MemoryContext. */
    MemoryContext firstChild;                   /* The first MemoryContext child. */
    MemoryContext presChild;                    /* The previous MemoryContext of peers. */
    MemoryContext nextChild;                    /* The next MemoryContext of peers. */
} MemoryContextData;


/* Create MemoryContext.
 * Thist abstract function not really to create MemoryContext and it just
 * make up the relation of MemoryContext.
 * */
MemoryContext MemoryContextCreate(MemoryContext node, MemoryContext parent, const char *name, ContextType type, MemoryContextMethodID id);

/* Delete the MemoryContext. */
void MemoryContextDelete(MemoryContext node, ContextType type);

#endif
