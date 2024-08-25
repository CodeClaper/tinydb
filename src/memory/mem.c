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
#include <sys/types.h>
#include <time.h>
#include "mem.h"
#include "mmu.h"
#include "shmem.h"
#include "list.h"
#include "spinlock.h"
#include "asserts.h"
#include "utils.h"

static MemType type;

static ShMemFreeEntry *header = NULL;
static size_t *capcity;
static s_lock *lock;

static void create_free_list();
static void create_spin_lock();
static void append_free_list(void *ptr, size_t size, bool isFree);
static bool is_free_entry_addr(void *ptr);
static ShMemFreeEntry *find_free_entry(void *ptr);

/* Init mem. */
void init_mem() {
    type = MEM_LOCAL;
    create_free_list();
    create_spin_lock();
}

/* Swith MemType. */
inline void switch_memtype(MemType mtype) {
    type = mtype;
}

static ShMemFreeEntry *new_free_entry(void *ptr, size_t size, bool isFree, ShMemFreeEntry *next) {
    ShMemFreeEntry *entry = shmem_alloc(sizeof(ShMemFreeEntry));
    entry->ptr = ptr;
    entry->size = size;
    entry->isFree = isFree;
    entry->next = next;
    return entry;
}


/* Create shemem list. */
static void create_free_list() {
    header = new_free_entry(NULL, 0, false, NULL);
    capcity = shmem_alloc(sizeof(size_t));
    *capcity = 0;
}

static void create_spin_lock() {
    lock = shmem_alloc(sizeof(s_lock));
    init_spin_lock(lock);
}

/* Mem if avaliable. */
static inline bool mem_avaliable() {
    return !is_null(header);
}


/* Allocate shared memory in FreeList.*/
static void *dalloc_shared_in_free_list(size_t size) {

    void *ptr = NULL;
    
    if (mem_avaliable()) {
        ShMemFreeEntry *entry = header;
        while ((entry = entry->next)) {
            if (entry->isFree && entry->size >= size) {
                ptr = entry->ptr;
                entry->isFree = false;
                break;
            }
        }
    }

    return ptr;
}

static void *get_free_list_tail() {
    ShMemFreeEntry *entry = header;
    while (entry->next) {
        entry = entry->next;
    }
    return entry;
}

/* Append free list. */
static void append_free_list(void *ptr, size_t size, bool isFree) {
    Assert(ptr);
    Assert(!is_free_entry_addr(ptr));
    
    Assert(!find_free_entry(ptr));

    if (!mem_avaliable())
        return;

    ShMemFreeEntry *free_entry = new_free_entry(ptr, size, isFree, NULL);

    ShMemFreeEntry *tail = get_free_list_tail();

    tail->next = free_entry;

    (*capcity)++;
}

static bool is_free_entry_addr(void *ptr) {
    ShMemFreeEntry *entry = header;
    while ((entry = entry->next)) {
        if (entry == ptr)
            return true;
    }
    return false;
}

/* Find ShMemFreeEntry. */
static ShMemFreeEntry *find_free_entry(void *ptr) {

    ShMemFreeEntry *entry = header;
    while ((entry = entry->next)) {
        if (entry->ptr == ptr)
            return entry;
    }
    return NULL;

}


/* Allocate memory in local memory. */
static void *dalloc_local(size_t size) {
    void *ptr = malloc(size);
    memset(ptr, 0, size);
    return ptr;
}


/* Allocate memory in shared memory. */
static void *dalloc_shared(size_t size) {
    Assert(size > 0);

    void *ptr;
    ptr = dalloc_shared_in_free_list(size);
    if (is_null(ptr)) {
        ptr = shmem_alloc(size);
        append_free_list(ptr, size, false);
    }

    /* Initialise data. */
    memset(ptr, 0, size);

    return ptr;
}


/* Free memory in local memory.*/
static void dfree_local(void *ptr) {
    free(ptr);
}

/* Free memory in shared memory.*/
static void dfree_shared(void *ptr) {

    Assert(ptr);
    Assert(shmem_addr_valid(ptr));

    ShMemFreeEntry *free_entry = find_free_entry(ptr);

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
    return realloc(ptr, size);
}


/* Reallocate shared memory. */
static void *drealloc_shared(void *ptr, size_t size) {
    Assert(ptr);
    ShMemFreeEntry *free_entry = find_free_entry(ptr);
    Assert(free_entry);
    size_t bsize = free_entry->size;
    void *new_ptr = dalloc_shared(size);
    memcpy(new_ptr, ptr, size < bsize ? size : bsize);
    try_dfree_shared(ptr);
    return new_ptr;
}

/* Strdup in shared memory.  */
static char *dstrdup_shared(char *str) {
    size_t size = strlen(str) + 1;
    void *new_str = dalloc_shared(size);
    memcpy(new_str, str, strlen(str));
    try_dfree_shared(str);
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
            return dstrdup_shared(str);
        default:
            UNEXPECTED_VALUE("Unknown MemType.");
    }
}
