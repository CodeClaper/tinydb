#include <pthread.h>
#include <stdint.h>

#define BLOCK_SIZE 1 << 26 /* 16 MB as block size. */
#define MAX_ALLOCATOR_SIZE 16

typedef struct MemManager {
    volatile uint32_t size;
    struct MemAllocator **array;
} MemManager;

typedef struct MemAllocator {
    pthread_t tid;
    void *block;
    uint32_t cursor;
    struct AllocEntry *alloc_entry;
    struct FreeEntry *free_table;
} MemAllocator;

typedef struct AllocEntry {
    void *ptr;
    uint32_t size;
    struct AllocEntry *next;
} AllocEntry;

typedef struct FreeEntry {
    void *ptr;
    uint32_t size;
    struct FreeEntry *next;
} FreeEntry;


/* Mem Init. */
void init_mem();

/* Allocate memory. */
void *alloc_mem(size_t size);

/* Free memory. */
void free_mem(void *ptr);

/* Reallocate memory. */
void *realloc_mem(void *ptr, size_t size);

/* Mem strdup. */
char *strdup_mem(char *str);

