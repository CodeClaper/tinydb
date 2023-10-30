#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "data.h"
#include "defs.h"

// register a MEntry
static void register_entry(void *ptr, size_t size) {
    MEntry *entry = sys_malloc(sizeof(MEntry));
    entry->ptr = ptr;
    entry->size = size;
    mtable->entry_list = sys_realloc(mtable->entry_list, sizeof(MEntry *) * (mtable->num + 1));
    *(mtable->entry_list + mtable->num) = entry;
    mtable->num++;
}

// change MEntry`s size
static void change_entry_size(void *prt, size_t resize) {
    for (uint32_t i = 0; i < mtable->num; i++) {
        MEntry *entry = *(mtable->entry_list + i);
        if (entry->ptr == prt)
            entry->size = resize;
    } 
}

// free MEntry
static void unregister_entry(void *prt) {
    for (uint32_t i = 0; i < mtable->num; i++) {
        MEntry *entry = *(mtable->entry_list + i);
        if (entry->ptr == prt) {
            for (uint32_t j = i; j < mtable->num; j++) {
                if (j != mtable->num - 1 )
                    memcpy((mtable->entry_list + j), (mtable->entry_list + j + 1), sizeof(MEntry *));
                else
                    memset(mtable->entry_list + j, 0, sizeof(MEntry *));
            }
            free(entry);
            mtable->num--;
            break;
        }
    } 
}

// system level mallocate
void *sys_malloc(size_t size) {
    void *ret = malloc(size);
    if (ret == NULL) {
        fprintf(stderr, "Not enough to allocate.");
        exit(EXIT_FAILURE);
    }
    memset(ret, 0, size);
    return ret;
}


// system level reallocate
void *sys_realloc(void *ptr, size_t size) {
    void *ret = realloc(ptr, size);
    if (ret == NULL) {
        fprintf(stderr, "Not enough to rallocate.");
        exit(EXIT_FAILURE);
    }
    return ret;
}

// database level  mallocate.
void *db_malloc(size_t size) {
    void *ret = malloc(size);
    if (ret == NULL) {
        fprintf(stderr, "Not enough to allocate.");
        exit(EXIT_FAILURE);
    }
    memset(ret, 0, size);
    register_entry(ret, size);
    return ret;
}

// database level reallocate
void *db_realloc(void *ptr, size_t size) {
    void *ret = realloc(ptr, size);
    if (ret == NULL) {
        fprintf(stderr, "Not enough to rallocate.");
        exit(EXIT_FAILURE);
    }
    change_entry_size(ptr, size);
    return ret;
}

// database level mememory free.
void db_free(void *ptr) {
    if (ptr) {
        unregister_entry(ptr);
        free(ptr);
    }
}

// databese level mememory size.
size_t db_memesize() {
    size_t total = 0;
    for (uint32_t i = 0; i < mtable->num; i++) {
        MEntry *entry = *(mtable->entry_list + i);
        assert(entry);
        total += entry->size;
    }
    return total;
}
