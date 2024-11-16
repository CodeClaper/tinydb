#include <stdlib.h>
#include <stdbool.h>
#include "spinlock.h"

typedef struct ShMemFreeEntry {
    size_t  size;
    bool    isFree;
    size_t  num;
    s_lock  lock;
} ShMemFreeEntry;

#define SHM_OFFSET sizeof(ShMemFreeEntry)


/* Init mem. */
void init_mem();

/* Alloc for share. */
void *shdalloc(size_t size);

/* Free for share. */
void shdfree(void *ptr);

/* Realloc for share. */
void *shdrealloc(void *ptr, size_t size);

/* Strdup for share. */
char *shdstrdup(char *str);
