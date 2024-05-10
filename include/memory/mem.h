#include <pthread.h>
#include <sched.h>
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
void *mmalloc(size_t size);

/* Free memory. */
void mfree(void *ptr);

/* Reallocate memory. */
void *mrealloc(void *ptr, size_t size);

/* Mem strdup. */
char *mstrdup(char *str);

/* Start allocator. */
void start_allocator();

/* End allocator. */
void end_allocator();
