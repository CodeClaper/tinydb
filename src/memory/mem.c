/****************************** The memory manager ***************************
 * Auth:        JerryZhou
 * Created:     2024/08/14
 * Modify:      2024/08/14
 * Locataion:   src/memory/mem.c
 * Description: The memory manager supports local memory and share memory manager.
******************************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "mem.h"
#include "shmem.h"
#include "list.h"
#include "spinlock.h"
#include "asserts.h"
#include "utils.h"

static MemType type;

List *shMemFreeList;

static bool hasInit;

s_lock free_lock;

static void create_free_list();
static void add_free_list(void *ptr, size_t size);

/* Init mem. */
void init_mem() {
    hasInit = false;
    type = MEM_LOCAL;
    init_spin_lock(&free_lock);
    create_free_list();
    hasInit = true;
}

/* Swith MemType. */
void switch_memtype(MemType mtype) {
    type = mtype;
}


/* Create shemem list. */
static void create_free_list() {
    switch_memtype(MEM_SHARED);
    shMemFreeList = create_list(NODE_VOID);
    switch_memtype(MEM_LOCAL);
}


/* Allocate shared memory in FreeList.*/
static void *dalloc_shared_in_free_list(size_t size) {
    void *ptr = NULL;
    // acquire_spin_lock(&free_lock);
    
    if (hasInit) {
        ListCell *lc;
        foreach (lc, shMemFreeList) {
            ShMemFreeEntry *free_entry = lfirst(lc);
            size_t left_size = free_entry->size - size;
            if (free_entry->isFree && left_size == 0) {
                ptr = free_entry->ptr;
                free_entry->isFree = false;
            } else if (free_entry->isFree && left_size > 0) {
                ptr = free_entry->ptr;
                free_entry->isFree = false;
                free_entry->size = size;
                add_free_list(ptr + size, left_size);
            }
        }
    }

    // release_spin_lock(&free_lock);

    return ptr;
}

static void add_free_list(void *ptr, size_t size) {
    Assert(ptr);

    if (!hasInit)
        return;

    switch_memtype(MEM_SHARED);
    // acquire_spin_lock(&free_lock);

    ShMemFreeEntry *free_entry = shmem_alloc(sizeof(ShMemFreeEntry));
    free_entry->ptr = ptr;
    free_entry->size = size;
    free_entry->isFree = false;

    append_list(shMemFreeList, free_entry);

    // release_spin_lock(&free_lock);
    switch_memtype(MEM_LOCAL);
}

static ShMemFreeEntry *find_free_entry(void *ptr) {
    ListCell *lc;
    foreach (lc, shMemFreeList) {
        ShMemFreeEntry *free_entry = lfirst(lc);
        if (free_entry->ptr == ptr)
            return free_entry;
    }

    return NULL;
}


/* Allocate memory in local memory. */
static void *dalloc_local(size_t size) {
    return malloc(size);
}


/* Allocate memory in shared memory. */
static void *dalloc_shared(size_t size) {
    Assert(size > 0);
    void *ptr;
    ptr = dalloc_shared_in_free_list(size);
    if (is_null(ptr)) {
        ptr = shmem_alloc(size);
        add_free_list(ptr, size);
    }
    return ptr;
}



/* Free memory in local memory.*/
static void dfree_local(void *ptr) {
    free(ptr);
}


/* Free memory in shared memory.*/
static void dfree_shared(void *ptr) {
    Assert(ptr);
    ShMemFreeEntry *free_entry = find_free_entry(ptr);
    Assert(free_entry);
    bzero(free_entry->ptr, free_entry->size);
    free_entry->isFree = true;
}

/* Reallocate local memory. */
static void *drealloc_local(void *ptr, size_t size) {
    return realloc(ptr, size);
}


/* Reallocate shared memory. */
static void *drealloc_shared(void *ptr, size_t size) {
    Assert(ptr);
    ShMemFreeEntry *free_entry = find_free_entry(ptr);
    size_t bsize = free_entry->size;
    void *new_ptr = dalloc_shared(size);
    memcpy(new_ptr, ptr, size < bsize ? size : bsize);
    dfree_shared(ptr);
    return new_ptr;
}


static char *pstrdup_shared(char *str) {
    size_t len = strlen(str) + 1;
    void *new_str = dalloc_shared(len);
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
void *dstrdup(char *str) {
    switch (type) {
        case MEM_LOCAL:
            return strdup(str);
        case MEM_SHARED:
            return pstrdup_shared(str);
        default:
            UNEXPECTED_VALUE("Unknown MemType.");
    }
}
