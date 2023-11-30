#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "mem.h"
#include "data.h"
#include "defs.h"
#include "y.tab.h"

/**
* Memory Manager Unit
*
* Memory Manager Unit(MMU) is designed to achieve unnified memory management.
* We use db_malloc,db_realloc, db_free to repalce native diynamic memory function 
* malloc, realloc and free. In this way, we can record every diynamic meomry usage 
* info as a MEntry. MEntry will store in a HashTable data structure which called 
* MHashTable. HashTable supports more effective insertion and query operation.
* MMU provides this following capabities:
* 1.Accurate memory usage data
* 2.No memory leaking, no double free
* 3.Robust against allocation failures
* 4.Memory usage limit
*/

/* =========================== HashTable Data structure ========================
 * MHashTable is a array of MEntry, and the index is defined by hash of pointer
 * in MEntry. When hash collision, the MEntry will transform to chain list. The
 * new MEntry will insert at tail. If the number of MEntry exceed the treshold
 * (treshold = capacity * DEFAULT_LOAD_FACTOR), MTable will automatically expand,
 * In the same way, MTable will shrink when number below the treshold.
 * ============================================================================*/
#define MAXIMUM_CAPACITY 1<<31
#define MININUM_CAPACITY 1<<10
#define DEFAULT_LOAD_FACTOR 0.75

static MHashTable *mtable;
static uint32_t max_value;
static pthread_mutex_t mutex;

static uint32_t hash_code(void *ptr) {
    int a = (uintptr_t)ptr & 0xFFFFFFF;
    /*return a ^ (a >> 16);*/
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

uint32_t table_size_for(uint32_t cap) {
        uint32_t n = cap - 1;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        return (n < 0) ? 1 : (n >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : n + 1;
}

/* Get the index of ptr by hash code. */
static uint32_t get_index(void *ptr, uint32_t capacity) {
    return hash_code(ptr) % capacity;
}

/* Initialise mem */
void init_mem() {
    /* Initialise table. */
    mtable = sys_malloc(sizeof(MHashTable));
    mtable->capacity = MININUM_CAPACITY; 
    mtable->num = 0;
    mtable->entry_list = sys_malloc(sizeof(void *) * mtable->capacity);
    /* Initialise tmux. */
    pthread_mutex_init(&mutex, NULL);
}

/* Expand capacity of HashTable. */
void expand_capacity() {
    uint32_t new_cap, old_cap, i;
    old_cap = mtable->capacity;
    /* Already max capacity, not allow to expand. */
    if (old_cap >= MAXIMUM_CAPACITY)
        return; 
    new_cap = mtable->capacity << 1;
    new_cap = new_cap < MAXIMUM_CAPACITY ? new_cap : MAXIMUM_CAPACITY; /* Avoid to exceed the max 32_bit integer. */
    MEntry **old_list = mtable->entry_list;
    MEntry **new_list = sys_malloc(sizeof(void *) * new_cap);
    for (i = 0; i < old_cap; i++) {
        MEntry *current = old_list[i];
        if (current) {
            old_list[i] = NULL; 
            /* Check if the entry if evolved into list */
            if (current->next == NULL) // only itself
                new_list[hash_code(current->ptr) & (new_cap - 1)] = current;
            else {
                /* Being a list. */
                MEntry *loHead = NULL, *loTail = NULL;
                MEntry *hiHead = NULL, *hiTail = NULL;
                MEntry *next;
                do {
                    next = current->next;
                    if ((hash_code(current->ptr) & old_cap) == 0) {
                        if (loTail == NULL)
                            loHead = current;
                        else
                            loTail->next = current;
                        loTail = current;
                    }
                    else {
                        if (hiTail == NULL)
                            hiHead = current;
                        else
                            hiTail->next = current;
                        hiTail = current;
                    }
                } while ((current = next) != NULL);
                if (loTail != NULL) {
                    loTail->next = NULL;
                    new_list[i] = loHead;
                }
                if (hiTail != NULL) {
                    hiTail->next = NULL;
                    new_list[i + old_cap] = hiHead;
                }
            }
        } 
    }
    mtable->entry_list = new_list;
    mtable->capacity = new_cap;
    free(old_list);
}

/* Shrink capacity of HashTable. */
void shrink_capacity() {
    uint32_t new_cap, old_cap, i;
    old_cap = mtable->capacity;
    if (old_cap <= MININUM_CAPACITY)
        return; // already min capacity, not allow to shrink.
    new_cap = mtable->capacity >> 1;
    new_cap = new_cap < MININUM_CAPACITY ? MININUM_CAPACITY : new_cap;
    MEntry **old_list = mtable->entry_list;
    MEntry **new_list = sys_malloc(sizeof(void *) * (new_cap));
    for (i = 0; i < mtable->capacity; i++) {
        MEntry *current = old_list[i];
        if (current) {
            old_list[i] = NULL;
            if (current) {
                uint32_t index = hash_code(current->ptr) & (new_cap - 1);
                MEntry *entry = new_list[index];
                if (entry == NULL)
                    new_list[index] = current;
                else {
                    while(entry->next) {
                        entry = entry->next;
                    }
                    entry->next = current;
                }
            }
        }
    }
    mtable->entry_list = new_list;
    mtable->capacity = new_cap;
    free(old_list);
}

/* Insert new entry */
void insert_entry(void *ptr, MEntry *entry) {
    /* Lock */
    pthread_mutex_lock(&mutex);
    uint32_t index, treshold;
    index = get_index(ptr, mtable->capacity);
    MEntry *current = mtable->entry_list[index];
    if (current == NULL)
        mtable->entry_list[index] = entry; // first entry
    else {
        while(current->next) {
            current = current->next;
        }
        current->next = entry;
    }
    mtable->num++;
    treshold = mtable->capacity * DEFAULT_LOAD_FACTOR;
    if (mtable->num > treshold)
        expand_capacity();
    /* Unlock */
    pthread_mutex_unlock(&mutex);
}

/* free entry */
static void free_entry(MEntry *entry, bool alread_free_ptr) {
    if (entry) {
        if (!alread_free_ptr)
            free(entry->ptr);
        free(entry);
    }
}

/* remove entry */
void remove_entry(void *ptr, bool alread_free_ptr) {
    /* Lock */
    pthread_mutex_lock(&mutex);
    uint32_t index, treshold;
    MEntry *first, *prev, *current;
    index = get_index(ptr, mtable->capacity);
    first = mtable->entry_list[index];
    prev = first;
    current = first;
    if (current != NULL) {
        if (first->ptr == ptr) {
            mtable->entry_list[index] = first->next;
            free_entry(current, alread_free_ptr);
            mtable->num--;
        } 
        else {
            while((current = current->next)) {
                if (current->ptr == ptr) {
                    prev->next = current->next;
                    free_entry(current, alread_free_ptr);
                    mtable->num--;
                    break;
                }
                prev = current;
            }
        }
    }
    treshold = (mtable->capacity >> 1) * DEFAULT_LOAD_FACTOR;
    if (mtable->num < treshold)
        shrink_capacity();
    /* UnLock */
    pthread_mutex_unlock(&mutex);
}

/* search entry. */
MEntry *search_entry(void *ptr) {
    uint32_t index = get_index(ptr, mtable->capacity);
    MEntry *current = mtable->entry_list[index];
    if (current != NULL) {
        do {
            if (current->ptr == ptr) 
                return current;
        } while ((current = current->next));
    }
    return NULL;
}

/* register a MEntry */
static void register_entry(void *ptr, size_t size, const char *data_type_name) {
    MEntry *entry = sys_malloc(sizeof(MEntry));
    entry->ptr = ptr;
    entry->size = size;
    strcpy(entry->data_type_name, data_type_name == NULL ? "Unknown" : data_type_name);
    insert_entry(ptr, entry);
}

// change MEntry`s size
static void change_entry(void *old_ptr, void* new_ptr ,size_t resize) {
    if (old_ptr == new_ptr) {
        MEntry *entry = search_entry(old_ptr);
        assert(entry);
        entry->ptr = new_ptr;
        entry->size = resize;
    } else {
        remove_entry(old_ptr, true);
        register_entry(new_ptr, resize, NULL);
    }
}

/* Free MEntry
 * First check if exist, only exists then free, avoid to double free.
 **/
static void unregister_entry(void *ptr) {
     remove_entry(ptr, false);
}

/* system level mallocate. */
void *sys_malloc(size_t size) {
    void *ret = malloc(size);
    if (ret == NULL) {
        fprintf(stderr, "Not enough to allocate.");
        exit(EXIT_FAILURE);
    }
    memset(ret, 0, size);
    return ret;
}


/* system level reallocate. */
void *sys_realloc(void *ptr, size_t size) {
    void *ret = realloc(ptr, size);
    if (ret == NULL) {
        fprintf(stderr, "Not enough to rallocate.");
        exit(EXIT_FAILURE);
    }
    return ret;
}

/* database level mallocate. */
void *db_malloc(size_t size) {
    void *ret = malloc(size);
    if (ret == NULL) {
        fprintf(stderr, "Not enough to allocate.");
        exit(EXIT_FAILURE);
    }
    memset(ret, 0, size);
    register_entry(ret, size, NULL);
    return ret;
}

/* database level mallocate, inputing data type name is for trace purposes. */
void *db_malloc2(size_t size, char *data_type_name) {
    void *ret = malloc(size);
    if (ret == NULL) {
        fprintf(stderr, "Not enough to allocate.");
        exit(EXIT_FAILURE);
    }
    memset(ret, 0, size);
    register_entry(ret, size, data_type_name);
    return ret;
}

/* database level reallocate. */
void *db_realloc(void *ptr, size_t size) {
    void *ret = realloc(ptr, size);
    if (ret == NULL) {
        fprintf(stderr, "Not enough to rallocate.");
        exit(EXIT_FAILURE);
    }
    change_entry(ptr, ret, size);
    return ret;
}

/* database level mememory free. */
void db_free(void *ptr) {
    if (ptr)
        unregister_entry(ptr);
}

/* databese level mememory size. */
size_t db_memesize() {
    size_t total = 0;
    for (uint32_t i = 0; i < mtable->capacity; i++) {
        MEntry *entry = *(mtable->entry_list + i);
        while(entry) {
            printf("%s\t", entry->data_type_name);
            total += entry->size;
            entry = entry->next;
        }
    }
    printf("\nTotal %d pointer and %ld byte memory not release, the mhashtabe capacity is %d entry number is %d.\n", mtable->num, total, mtable->capacity, mtable->num);
    return total;
}
