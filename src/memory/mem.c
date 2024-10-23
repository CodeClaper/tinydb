/****************************** The memory manager ***************************
 * Auth:        JerryZhou
 * Created:     2024/08/14
 * Modify:      2024/08/14
 * Locataion:   src/memory/mem.c
 * Description: The memory manager supports local memory and share memory manager.
******************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include "mem.h"
#include "shmem.h"
#include "lomem.h"
#include "list.h"
#include "spinlock.h"
#include "asserts.h"
#include "utils.h"

static MemType type = MEM_LOCAL;

static ShMemFreeEntry *header = NULL;
static void *BASE_LINE;

/* Init mem. */
void init_mem() {
    ShMemFreeEntry entry = { .size = 0, .num = 0, .isFree = false, .lock = SPIN_UN_LOCKED_STATUS };
    void *ptr = shmem_alloc(SHM_OFFSET);
    memcpy(ptr, &entry, SHM_OFFSET);
    header = ptr;
    BASE_LINE = header;
}

/* Swith Shared Memory. */
inline void switch_shared() {
    type = MEM_SHARED;
}

/* Switch Local Memory. */
inline void switch_local() {
    type = MEM_LOCAL;
}


/* Allocate shared memory in FreeList.*/
static void *dalloc_shared_in_free_list(size_t size) {

    void *ptr = NULL;

    acquire_spin_lock(&header->lock);
    
    size_t offset = SHM_OFFSET;

    uint32_t i;
    for (i = 0; i < header->num; i++) {
        ShMemFreeEntry *entry = BASE_LINE + offset;
        if (entry->isFree && entry->size >= size) {
            ptr = (void *) ((char *) entry + SHM_OFFSET);
            entry->isFree = false;
            break;
        }

        offset += (entry->size + SHM_OFFSET);
    }

    release_spin_lock(&header->lock);

    return ptr;
}


/* Allocate memory in local memory. */
static void *dalloc_local(size_t size) {

    void *ptr = NULL;

    if (lomem_available()) {
        LoMemEntry entry;
        void *npt = lomem_alloc(size + LMENTRY_OFFSET );
        entry.size = size;
        entry.isFree = false;
        memcpy(npt, &entry, LMENTRY_OFFSET);
        ptr = npt + LMENTRY_OFFSET;
    } else
        ptr = malloc(size);

    Assert(ptr);
    
    /* Initialise. */
    memset(ptr, 0, size);

    return ptr;
}


/* Allocate memory in shared memory. */
static void *dalloc_shared(size_t size) {
    Assert(size > 0);

    size = MAXALIGN(size);

    /* Firstly allocate from free list, if missing, shmem alloc. */
    void *ptr = dalloc_shared_in_free_list(size);

    if (is_null(ptr)) {

        void *nptr = shmem_alloc(size + SHM_OFFSET);

        ShMemFreeEntry entry = { .size = size, .isFree = false };

        memcpy(nptr, &entry, SHM_OFFSET);

        ptr = nptr + SHM_OFFSET;

        header->num++;
    }

    /* Initialise data. */
    memset(ptr, 0, size);

    return ptr;
}

/* Free memory in local memory.*/
static void dfree_local(void *ptr) {
    
    if (lomem_available()) {
        LoMemEntry *entry = ptr - LMENTRY_OFFSET;
        entry->isFree = true;
    } else
        free(ptr);
}

/* Free memory in shared memory.*/
static void dfree_shared(void *ptr) {

    Assert(ptr);
    Assert(shmem_addr_valid(ptr));

    ShMemFreeEntry *free_entry = ptr - SHM_OFFSET;

    Assert(free_entry);
    Assert(!free_entry->isFree);

    free_entry->isFree = true;
}

/* Try dfree_shared. */
static void try_dfree_shared(void *ptr) {
    if (shmem_addr_valid(ptr))
        dfree_shared(ptr);
}

/* Reallocate local memory. */
static void *drealloc_local(void *ptr, size_t size) {

    if (lomem_available()) {
        LoMemEntry *entry = ptr - LMENTRY_OFFSET;
        void *npt = dalloc_local(size);
        memcpy(npt, ptr, min_size(entry->size, size));
        dfree_local(ptr);
        return npt;
    } else
        return realloc(ptr, size);
}


/* Reallocate shared memory. */
static void *drealloc_shared(void *ptr, size_t size) {

    Assert(ptr);

    ShMemFreeEntry *entry = ptr - SHM_OFFSET;

    void *new_ptr = dalloc_shared(size);

    memcpy(new_ptr, ptr, min_size(entry->size, size));

    try_dfree_shared(ptr);

    return new_ptr;
}


/* Strdup in local memory. */
static char *dstrdup_local(char *str) {
    if (lomem_available()) {
        char *nstr = dalloc_local(strlen(str) + 1);
        memcpy(nstr, str, strlen(str));
        return nstr;
    } else
        return strdup(str);
}

/* Strdup in shared memory.  */
static char *dstrdup_shared(char *str) {
    size_t size = strlen(str) + 1;
    void *new_str = dalloc_shared(size);
    memcpy(new_str, str, strlen(str));
    return new_str;
}


/* Allocate memory. */
void *dalloc(size_t size) {
    switch (type) {
        case MEM_LOCAL:
            return dalloc_local(size);
        case MEM_SHARED:
            return dalloc_shared(size);
        default:
            UNEXPECTED_VALUE("Unknown MemType.");
    }
}

/* Free memory. */
void dfree(void *ptr) {
    switch (type) {
        case MEM_LOCAL:
            dfree_local(ptr);
            break;
        case MEM_SHARED:
            dfree_shared(ptr);
            break;
        default:
            UNEXPECTED_VALUE("Unknown MemType.");
    }
}

/* Reallocate memory. */
void *drealloc(void *ptr, size_t size) {
    switch (type) {
        case MEM_LOCAL:
            return drealloc_local(ptr, size);
        case MEM_SHARED:
            return drealloc_shared(ptr, size);
        default:
            UNEXPECTED_VALUE("Unknown MemType.");
    }
}

/* Strdup. */
char *dstrdup(char *str) {
    if (is_null(str))
        return NULL;

    switch (type) {
        case MEM_LOCAL:
            return dstrdup_local(str);
        case MEM_SHARED:
            return dstrdup_shared(str);
        default:
            UNEXPECTED_VALUE("Unknown MemType.");
    }
}
