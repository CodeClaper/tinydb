#include <stdlib.h>

/* Alloc for local. */
void *lodalloc(size_t size);

/* Free for local. */
void lofree(void *ptr);

/* Realloc for local. */
void *lodrealloc(void *ptr, size_t size);

/* Strdup for local. */
char *lodstrdup(char *str);
