#include <stdbool.h>

typedef enum MemType {
    MEM_LOCAL,
    MEM_SHARED
} MemType;

typedef struct ShMemFreeEntry {
    void *ptr;
    size_t size;
    bool isFree;
} ShMemFreeEntry;


/* Init mem. */
void init_mem();

/* Swith MemType. */
void switch_memtype(MemType mtype);

/* Allocate memory. */
void *dalloc(size_t size);

/* Free memory. */
void dfree(void *ptr);

/* Reallocate memory. */
void *drealloc(void *ptr, size_t size);

/* Strdup. */
void *dstrdup(char *str);

