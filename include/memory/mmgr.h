#include <stdbool.h>
#include <stdlib.h>
#include "spinlock.h"

typedef enum MemType {
    MEM_LOCAL = 0,
    MEM_SHARED
} MemType;

typedef struct MemMethods {
    void *(*dalloc)(size_t size);
    void (*dfree)(void *ptr);
    void *(*drealloc)(void *ptr, size_t size);
    char *(*dstrdup)(char *str);
} MemMethods;

#define instance(_type_)  ((_type_ *) dalloc(sizeof(_type_)))


#define LMENTRY_OFFSET sizeof(LoMemEntry)


/* Define as the maximum alignment requirement of any C data type. */
#define MAXIMUM_ALIGNOF 8

#define TYPEALIGN(ALIGNVAL,LEN)  \
	(((uintptr_t) (LEN) + ((ALIGNVAL) - 1)) & ~((uintptr_t) ((ALIGNVAL) - 1)))

#define MAXALIGN(LEN)			TYPEALIGN(MAXIMUM_ALIGNOF, (LEN))


/* Swith Shared Memory. */
void switch_shared();

/* Switch Local Memory. */
void switch_local();

/* Allocate memory. */
void *dalloc(size_t size);

/* Free memory. */
void dfree(void *ptr);

/* Reallocate memory. */
void *drealloc(void *ptr, size_t size);

/* Strdup. */
char *dstrdup(char *str);

