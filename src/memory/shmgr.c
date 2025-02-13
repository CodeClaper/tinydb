/***************************** Shared Memory Mamnager Module *********************************
 * Auth:            JerryZhou 
 * Created:         2024/11/16 
 * Modify:          2024/11/16
 * Locataion:       src/memory/shdmem.c
 * Description:     This is the implement of mem for manipulating shared memory.
 *********************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shmgr.h"
#include "shmem.h"
#include "mmgr.h"
#include "utils.h"

static ShMemFreeEntry *header = NULL;
static void *BASE_LINE;

static void *dalloc_shared_in_free_list(size_t size);
static void try_shdfree(void *ptr);

/* Init mem. */
void init_mem() {
    ShMemFreeEntry entry = { 
        .size = 0, 
        .num = 0, 
        .isFree = false, 
        .lock = SPIN_UN_LOCKED_STATUS 
    };
    void *ptr = shmem_alloc(SHM_OFFSET);
    memcpy(ptr, &entry, SHM_OFFSET);
    header = ptr;
    BASE_LINE = header;
}

/* Alloc for share. */
void *shdalloc(size_t size) {
    Assert(size > 0);

    size = MAXALIGN(size);

    /* Firstly allocate from free list, if missing, allocate from share memory. */
    void *ptr = dalloc_shared_in_free_list(size);
    if (ptr == NULL) {
        void *nptr = shmem_alloc(size + SHM_OFFSET);
        ShMemFreeEntry entry = { 
            .size = size, 
            .isFree = false,
            .num = 0,
            .lock = SPIN_UN_LOCKED_STATUS
        };
        memcpy(nptr, &entry, SHM_OFFSET);
        ptr = nptr + SHM_OFFSET;
        header->num++;
    }

    /* Initialise data. */
    memset(ptr, 0, size);

    return ptr;
}

/* Free for share. */
void shdfree(void *ptr) {
    Assert(ptr);
    Assert(shmem_addr_valid(ptr));

    ShMemFreeEntry *free_entry = GET_FREE_ENTRY(ptr);

    Assert(free_entry);
    Assert(!free_entry->isFree);

    free_entry->isFree = true;
}

/* Realloc for share. */
void *shdrealloc(void *ptr, size_t size) {
    Assert(ptr);

    ShMemFreeEntry *entry = ptr - SHM_OFFSET;
    void *new_ptr = shdalloc(size);
    memcpy(new_ptr, ptr, min_size(entry->size, size));
    try_shdfree(ptr);
    return new_ptr;
}

/* Strdup for share. */
char *shdstrdup(char *str) {
    if (is_null(str))
        return NULL;
    size_t size = strlen(str) + 1;
    void *new_str = shdalloc(size);
    memcpy(new_str, str, strlen(str));
    return new_str;
}


/* Try free for share. */
static void try_shdfree(void *ptr) {
    if (shmem_addr_valid(ptr))
        shdfree(ptr);
}


/* Allocate shared memory in FreeList.*/
static void *dalloc_shared_in_free_list(size_t size) {
    void *ptr = NULL;
    
    /* Acquire lock. */
    acquire_spin_lock(&header->lock);
    
    size_t offset = SHM_OFFSET;
    uint32_t i;
    for (i = 0; i < header->num; i++) {
        ShMemFreeEntry *entry = (ShMemFreeEntry *) (((char *) BASE_LINE) + offset);
        if (entry->isFree && entry->size >= size) {
            ptr = GET_POINTER(entry);
            entry->isFree = false;
            break;
        }
        offset += (entry->size + SHM_OFFSET);
    }

    /* Release lock. */
    release_spin_lock(&header->lock);

    return ptr;
}

