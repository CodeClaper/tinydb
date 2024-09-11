#include <stdlib.h>
#include <stdbool.h>

#define INIT_LOMEM_SIZE 1024 * 1024 * 1024 // Local Memory Initial Size.

typedef struct LoMemHeader {
    size_t total_size;
    size_t offset;
} LoMemHeader;


/* Lomem if available*/
bool lomem_available();


/* Start the lomem. */
void lomem_start();

/* Alloc from Local Memory. */
void *lomem_alloc(size_t size);

/* End the lomem. */
void lomem_end();
