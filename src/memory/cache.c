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

/*
 * Table Cache lock.
 */
static s_lock *tlock;

/* Initialise table cache. */
void init_table_cache() {
    switch_shared();
    TableCache = create_list(NODE_TABLE);
    tlock = instance(s_lock);
    init_spin_lock(tlock);
    switch_local();
}

/* Save table cache. */
void save_table_cache(Table *table) {
    acquire_spin_lock(tlock);
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
    release_spin_lock(tlock);
}


/* Find cache table by name, return null if not exist. */
Table *find_table_cache(char *table_name) {
    acquire_spin_lock(tlock);
    Table *found = NULL;
    ListCell *lc;
    foreach (lc, TableCache) {
        Table *cur_table = (Table *) lfirst(lc);
        if (streq(cur_table->meta_table->table_name, table_name)) {
            found = cur_table;
            break;
        }
    }
    release_spin_lock(tlock);
    return found;
}


/* Remove table cache. */
void remove_table_cache(char *table_name) {
    acquire_spin_lock(tlock);
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
    release_spin_lock(tlock);
}

