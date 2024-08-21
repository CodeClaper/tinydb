#include <stdlib.h>
#include <stdbool.h>

typedef struct ShmemHeader {
    size_t total_size;
    size_t offset;
}ShmemHeader;

/* Init the shared memory. */
void init_shmem();

/* Allocate memory in Shmem. */
void *shmem_alloc(size_t size);

/* Check if addess is valid shared memory. */
bool shmem_addr_valid(void *ptr);
