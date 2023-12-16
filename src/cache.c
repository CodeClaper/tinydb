#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "cache.h"
#include "mmu.h"
#include "free.h"

#define MAX_TABLE_CACHE_SIZE 100

typedef struct {
    Table **table_list;
    uint32_t size;
}TableCache;

static TableCache *table_cache;

static void init() {
    if (table_cache == NULL) {
        table_cache = db_malloc(sizeof(TableCache));
        table_cache->table_list = db_malloc(0);
        table_cache->size = 0;
    }
}

// check if same table
static bool same_table(Table *t1, Table *t2) {
    if (t1->meta_table == NULL || t2->meta_table == NULL){
        fprintf(stderr, "Table lack of meta table info.\n");
        exit(EXECUTE_FAIL);
        return false;
    }
    return strcmp(t1->meta_table->table_name, t2->meta_table->table_name) == 0;
}

// check if same table name
static bool same_table_name(Table *t1, char *table_name) {
    if (t1->meta_table == NULL || t1->meta_table->table_name == NULL) {
        fprintf(stderr, "Table lack of meta table info.\n");
        exit(EXECUTE_FAIL);
    }
    return strcmp(t1->meta_table->table_name, table_name) == 0;
}

// add cache table 
void add_cache_table(Table *table) {
    init();
    int i;
    for(i = 0; i < table_cache->size; i++) {
        Table *current = *(table_cache->table_list + i);
        if (same_table(current, table)) {
            *(table_cache->table_list + i) = table; // replace free old table.
            free_table(current);
            return;
        }
    }
    *(table_cache->table_list + i) = table; // insert new cache.
    table_cache->size++;
}

//Find cache table by name, retrurn null if not exist.
Table *find_cache_table(char *table_name) {
    init();
    for(int i = 0; i < table_cache->size; i++) {
        Table *current = *(table_cache->table_list + i);
        if (same_table_name(current, table_name))
            return current;
    }
    return NULL;
}
