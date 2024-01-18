#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "cache.h"
#include "mmu.h"
#include "free.h"

#define MAX_TABLE_CACHE_SIZE 100

static TableCache *t_cache;

/* Initialise table cache. */
void init_table_cache() {
    if (t_cache == NULL) {
        t_cache = db_malloc(sizeof(TableCache),SDT_TABLE_CACHE);
        t_cache->table_list = db_malloc(0, SDT_POINTER);
        t_cache->size = 0;
    }
}

/* Add table cache. */
void add_table_cache(Table *table) {
    int i;
    for(i = 0; i < t_cache->size; i++) {
        Table *current = t_cache->table_list[i] ;
        if (strcmp(current->meta_table->table_name, table->meta_table->table_name) == 0) {
            /* Replace free old table. */
            t_cache->table_list[i]  = table; 
            free_table(current);
            return;
        }
    }
    /* Insert new table cache. */
    t_cache->size++;
    t_cache->table_list = db_realloc(t_cache->table_list, sizeof(Table *) * t_cache->size);
    t_cache->table_list[i] = table; 
}

/* Find cache table by name, retrurn null if not exist. */
Table *find_table_cache(char *table_name) {
    int i;
    for(i = 0; i < t_cache->size; i++) {
        Table *current = *(t_cache->table_list + i);
        if (strcmp(current->meta_table->table_name, table_name) == 0)
            return current;
    }
    return NULL;
}

/* Remove table cache. */
void *remove_table_cache(char *table_name) {
    int i, j;
    for(i = 0; i < t_cache->size; i++) {
        Table *current = t_cache->table_list[i];
        if (strcmp(current->meta_table->table_name, table_name) == 0) {
            /* Right moves to cover. */
            for (j = i; j < t_cache->size - 1; j++) {
                memcpy(t_cache->table_list + j, t_cache->table_list + j + 1, sizeof(Table *));
            }
            memset(t_cache->table_list + t_cache->size - 1, 0, sizeof(Table *));
            /* Free memory. */
            free_table(current);     
            break;
        }
    }
    t_cache->size--;
    t_cache->table_list = db_realloc(t_cache->table_list, sizeof(Table *) * t_cache->size);
}
