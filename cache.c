#include "cache.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLE_CACHE_SIZE 100

typedef struct {
    Table **table_list;
}TableCache;

static TableCache *table_cache;

static void init() {
    if (table_cache == NULL) {
        table_cache = malloc(sizeof(TableCache));
        table_cache->table_list = malloc(sizeof(Table *) * MAX_TABLE_CACHE_SIZE);
    }
}

// check if same table
static bool same_table(Table *t1, Table *t2) {
    return strcmp(t1->meta_table->table_name, t2->meta_table->table_name) == 0;
}

// check if same table name
static bool same_table_name(Table *t1, char *table_name) {
    return strcmp(t1->meta_table->table_name, table_name) == 0;
}

// add cache table 
void add_cache_table(Table *table) {
    init();
    int i;
    for(i = 0; *(table_cache->table_list + i) != NULL; i++) {
        if (same_table(*(table_cache->table_list + i), table))
            break;
    }
    *(table_cache->table_list + i) = table; // update old table
}

//Find cache table by name, retrurn null if not exist.
Table *find_cache_table(char *table_name) {
    init();
    Table *current = NULL;
    for(int i = 0; (current = *(table_cache->table_list + i)); i++) {
        if (same_table_name(current, table_name))
            return current;
    }
    return current;
}
