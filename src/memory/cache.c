#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "cache.h"
#include "spinlock.h"
#include "utils.h"
#include "mmgr.h"
#include "copy.h"
#include "free.h"
#include "log.h"

#define MAX_TABLE_CACHE_SIZE 100

static List *TableCache;

/* Initialise table cache. */
void init_table_cache() {
    switch_shared();
    TableCache = create_list(NODE_TABLE);
    switch_local();
}

/* Save table cache. */
void save_table_cache(Table *table) {

    switch_shared();

    ListCell *lc;
    foreach (lc, TableCache) {
        Table *current = lfirst(lc);
        if (streq(current->meta_table->table_name, table->meta_table->table_name)) {
            /* Delete old one, and add new. */
            list_delete(TableCache, current);
            free_table(current);
        }
    }

    /* Insert new table cache. */
    append_list(TableCache, copy_table(table));

    switch_local();
}


/* Find cache table by name, return null if not exist. */
Table *find_table_cache(char *table_name) {

    void *ptr = NULL;

    ListCell *lc;
    foreach (lc, TableCache) {
        Table *current = lfirst(lc);
        if (streq(current->meta_table->table_name, table_name)) {
            ptr = current;
            break;
        }
    }
    return ptr;
}


/* Remove table cache. */
void remove_table_cache(char *table_name) {

    ListCell *lc;
    foreach (lc, TableCache) {
        Table *current = lfirst(lc);
        if (streq(current->meta_table->table_name, table_name)) {
            switch_shared();
            list_delete(TableCache, current);
            free_table(current);
            switch_local();
        }
    }
}

