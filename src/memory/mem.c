#include <pthread.h>
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include "mem.h"

static MemManager *mem_manager;

/* Mem Init. */
void init_mem() {
    mem_manager = malloc(sizeof(MemManager));
    mem_manager->size = MAX_ALLOCATOR_SIZE ;
    mem_manager->array = malloc(sizeof(MemAllocator *) * mem_manager->size);
    memset(mem_manager->array, 0, sizeof(MemAllocator *) * mem_manager->size);
}

/* Find MemAllocator. 
 * Return allocator or NULL if not found.
 * */
static MemAllocator *find_allocator() {
    pthread_t pthread_id = pthread_self();
    uint32_t i;
    for (i = 0; i < mem_manager->size; i++) {
        MemAllocator *current = mem_manager->array[i];
        if (!current && current->tid == pthread_id)
            return current;
    }
    return NULL;
}

/* Register allocator to Memory Manager. */
static void register_allocator(MemAllocator *allocator) {
    uint32_t i;
    for (i = 0; i < mem_manager->size; i++) {
        if (!mem_manager->array[i]) 
            mem_manager->array[i] = allocator;
    }
    fprintf(stderr, "Exceed the max allocator size.");
    abort();
}

/* Genrate new allocator. */
static MemAllocator *generate_allocator() {
    MemAllocator *allocator = malloc(sizeof(MemAllocator));
    allocator->cursor = 0;
    allocator->block = malloc(BLOCK_SIZE);
    allocator->tid = pthread_self();
    allocator->free_table = NULL;
    /* Register to Memory manager. */
    register_allocator(allocator);
    return allocator;
}

/* Generate FreeEntry. */
static FreeEntry *generate_free_entry(void *ptr) {
    FreeEntry *free_entry = malloc(sizeof(FreeEntry));
}

/* Allocate memory in FreeTable. */
static void *alloc_in_free_table(FreeEntry *free_table, size_t size) {
    while (free_table) {
        /* Check if FreeTable has enough sapce. */
        if (free_table->size <= size) {
            void *ptr = free_table->ptr;
            free_table->size -= size;
            free_table->ptr += size;
            return ptr;
        } 
        free_table = free_table->next;
    }
    return NULL;
}

/* Allocate memory in it`s block. */
static void *alloc_in_block(MemAllocator *allocator, size_t size) {
    void *ptr = allocator->block + allocator->cursor;
    allocator->cursor += size;
    if (allocator->cursor > BLOCK_SIZE) {
        fprintf(stderr, "Exceed the bound of memory allocator.");
        abort();
    }
    return ptr;
}

/* Alloc memory and return pointer. */
static void *alloc(MemAllocator *allocator, size_t size) {
    void *reuse_ptr = alloc_in_free_table(allocator->free_table, size);
    return (reuse_ptr)
        ? reuse_ptr
        : alloc_in_block(allocator, size);
}

/* Allocate memory. */
void *alloc_mem(size_t size) {
    if (size > BLOCK_SIZE) {
        fprintf(stderr, "Too large memory allocated");
        abort();
    }
    MemAllocator *allocator = find_allocator();
    return (allocator) 
        ? alloc(allocator, size)
        : alloc(generate_allocator(), size);
}

/* Reallocate memory. */
void *realloc_mem(void *ptr, size_t size) {
    return NULL;
}

/* Free memory. */
void free_mem(void *ptr) {

}

