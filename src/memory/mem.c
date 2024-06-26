#include <pthread.h>
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include "mem.h"

static AllocEntry *find_alloc_entry(MemAllocator *allocator, void *ptr);

static MemManager *mem_manager;

/* Mem Init. */
void init_mem() {
    mem_manager = malloc(sizeof(MemManager));
    mem_manager->size = MAX_ALLOCATOR_SIZE ;
    mem_manager->array = malloc(sizeof(MemAllocator *) * mem_manager->size);
    memset(mem_manager->array, 0, sizeof(MemAllocator *) * mem_manager->size);
}

/* Find Exclusive MemAllocator. 
 * Return allocator or NULL if not found.
 * */
static MemAllocator *find_allocator() {
    pthread_t pthread_id = pthread_self();
    uint32_t i;
    for (i = 0; i < mem_manager->size; i++) {
        MemAllocator *current = mem_manager->array[i];
        if (current && current->tid == pthread_id)
            return current;
    }
    return NULL;
}


/* Find AllocEntry.
 * Return AllocEntry or NULL if not found.
 * */
static AllocEntry *find_alloc_entry(MemAllocator *allocator, void *ptr) {
    AllocEntry *current;
    for (current = allocator->alloc_entry; current != NULL; current = current->next) {
        if (current->ptr == ptr)
            return current;
    }

    return NULL;
}

/* Register exclusive allocator to Memory Manager. 
 * The first position reserved for shared allocator.
 * */
static void register_allocator(MemAllocator *allocator) {
    uint32_t i;
    for (i = 0; i < mem_manager->size; i++) {
        if (!mem_manager->array[i]) {
            mem_manager->array[i] = allocator;
            return;
        }
    }
    fprintf(stderr, "Exceed the max allocator size.");
    abort();
}

/* Register AllocEntry. */
static void register_alloc_entry(MemAllocator *allocator, AllocEntry *alloc_entry) {
    if (!allocator->alloc_entry)
        allocator->alloc_entry = alloc_entry;
    else {
        AllocEntry *current;
        for (current = allocator->alloc_entry; current->next != NULL; current = current->next);
        current->next = alloc_entry;
    }
}

/* Register FreeEntry. */
static void register_free_entry(MemAllocator *allocator, FreeEntry *free_entry) {
    if (!allocator->free_table)
        allocator->free_table = free_entry;
    else {
        FreeEntry *current;
        for (current = allocator->free_table; current->next != NULL; current = current->next);
        current->next = free_entry;
    }
}

/* Genrate new allocator. */
static MemAllocator *generate_allocator() {
    MemAllocator *allocator = malloc(sizeof(MemAllocator));
    allocator->cursor = 0;
    allocator->block = malloc(BLOCK_SIZE);
    /* Because, block is big, just check if success. */
    if (allocator->block)
        memset(allocator->block, 0, BLOCK_SIZE);
    else {
        fprintf(stderr, "Not enough memory space to allocate.");
        abort();
    }
    allocator->tid = pthread_self();
    allocator->alloc_entry = NULL;
    allocator->free_table = NULL;

    return allocator;
}

/* Generate AllocEntry. */
static AllocEntry *generate_alloc_entry(void *ptr, size_t size) {
    AllocEntry *alloc_entry = malloc(sizeof(AllocEntry));
    alloc_entry->ptr = ptr;
    alloc_entry->size = size;
    alloc_entry->next = NULL;
    return alloc_entry;
}

/* Generate FreeEntry. */
static FreeEntry *generate_free_entry(void *ptr, size_t size) {
    FreeEntry *free_entry = malloc(sizeof(FreeEntry));
    free_entry->ptr = ptr;
    free_entry->size = size;
    free_entry->next = NULL;
    return free_entry;
}

/* Destroy AllocEntry. */
static void destroy_alloc_entry(MemAllocator *allocator, void *ptr) {
    AllocEntry *head = allocator->alloc_entry;
    if (head->ptr == ptr) {
        allocator->alloc_entry = head->next;
        free(head);
    } else {
        AllocEntry *current, *pres;
        for (current = head; current != NULL; pres = current, current = current->next) {
            if (current->ptr == ptr) {
                pres->next = current->next;
                free(current);
                break;
            }
        }
    }
}

static void destroy_free_entry(MemAllocator *allocator, void *ptr) {

    FreeEntry *head = allocator->free_table;
    if (head->ptr == ptr) {
        allocator->free_table = head->next;
        free(head);
    } else {
        FreeEntry *current, *pres;
        for (current = head; current != NULL; pres = current, current = current->next) {
            if (current->ptr == ptr) {
                pres->next = current->next;
                free(current);
                break;
            }
        }
    }
}

/* Allocate memory in FreeTable. */
static void *alloc_in_free_table(MemAllocator *allocator, size_t size) {

    FreeEntry *free_entry = allocator->free_table;
    while (free_entry) {
        /* If FreeEntry has enough sapce, reuse it. */
        if (free_entry->size >= size) {
            void *ptr = free_entry->ptr;
            free_entry->size -= size;
            free_entry->ptr += size;
            if (free_entry->size == 0)
                destroy_free_entry(allocator, free_entry->ptr);
            return ptr;
        } 
        free_entry = free_entry->next;
    }
    return NULL;
}

/* Allocate memory in it`s block. */
static void *alloc_in_block(MemAllocator *allocator, size_t size) {
    if (allocator->cursor + size > BLOCK_SIZE) {
        fprintf(stderr, "Exceed the bound of memory allocator.");
        abort();
    }
    void *ptr = allocator->block + allocator->cursor;
    allocator->cursor += size;
    return ptr;
}

/* Alloc memory and return pointer. 
 * For memory reuse, fistly, allocate memory in free table.
 * If free table allocating fail, allocate in block.
 * */
static void *alloc(MemAllocator *allocator, size_t size) {
    
    /* Because when size is zero, 
     * allocator maybe generate same address pointer.
     * To avoid it, size is assigned at least.
     * */
    size = size == 0 ? 1 : size;

    void *reuse_ptr = alloc_in_free_table(allocator, size);
    void *ptr = (reuse_ptr)
                ? reuse_ptr
                : alloc_in_block(allocator, size);

    /* Generate AllocEntry and register it to allocator. */
    AllocEntry *alloc_entry = generate_alloc_entry(ptr, size);
    register_alloc_entry(allocator, alloc_entry);

    return ptr;
}

/* Exclusive allocate memory. */
void *mmalloc(size_t size) {

    MemAllocator *allocator = find_allocator();

    if (!allocator)
        return malloc(size);

    if (size > BLOCK_SIZE) {
        fprintf(stderr, "Too large memory to allocate");
        abort();
    }

    return alloc(allocator, size);
}

/* Free memory. */
void mfree(void *ptr) {
    
    if (ptr == NULL) {
        fprintf(stderr, "Try to free a NULL pointer.");
        abort();
    }

    MemAllocator *allocator = find_allocator();

    if (!allocator)
        return free(ptr);

    /* It means allocate happened before start allocator.*/
    AllocEntry *alloc_entry = find_alloc_entry(allocator, ptr);
    if (!alloc_entry) 
        return free(ptr);
    
    /* Generate FreeEntry and register to FreeTable. */
    FreeEntry *free_entry = generate_free_entry(ptr, alloc_entry->size);
    register_free_entry(allocator, free_entry);

    memset(ptr, 0, alloc_entry->size);

    /* Destroy alloc entry. */
    destroy_alloc_entry(allocator, ptr);
}

/* Reallocate memory. */
void *mrealloc(void *ptr, size_t size) {

    MemAllocator *allocator = find_allocator();
    if (!allocator) 
        return realloc(ptr, size);

    if (!ptr)
        return mmalloc(size);

    AllocEntry *alloc_entry = find_alloc_entry(allocator, ptr);

    /* It means allocate happened before start allocator.*/
    if (!alloc_entry) 
        return realloc(ptr, size);

    /* Allocate new memory and copy old one. */
    void *new_ptr = alloc(allocator, size);
    
    /* Memory copy. */
    memcpy(new_ptr, ptr, alloc_entry->size);
    
    /* Free old memory. */
    mfree(ptr);

    return new_ptr;
}

/* Mem strdup. */
char *mstrdup(char *str) {

    MemAllocator *allocator = find_allocator();
    if (!allocator) 
        return strdup(str);

    size_t size = strlen(str);
    char *new_str = mmalloc(size + 1);
    memcpy(new_str, str, size);
    return new_str;
}

void start_allocator() {
    if (find_allocator() != NULL) {
        fprintf(stderr, "Repeated start allocator");
        abort();
    }

    register_allocator(generate_allocator());
}

/* Destroy exclusive allocator. */
void end_allocator() {

    pthread_t pthread_id = pthread_self();
    uint32_t i;
    for (i = 0; i < mem_manager->size; i++) {
        MemAllocator *current = mem_manager->array[i];
        if (current && current->tid == pthread_id) {
            free(current->block);
            free(current);
            mem_manager->array[i] = NULL;
        }
    }
    
}   


