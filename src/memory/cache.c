#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "cache.h"
#include "spinlock.h"
#include "utils.h"
#include "mmu.h"
#include "copy.h"
#include "free.h"
#include "log.h"
#include "mem.h"

#define MAX_TABLE_CACHE_SIZE 100

static List *TableCache;

/* Initialise table cache. */
void init_table_cache() {
    switch_shared();
    TableCache = create_list(NODE_TABLE);
    switch_local();
}

/* Save or update table cache. */
void save_or_update_table_cache(Table *table) {

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
            ptr = copy_table(current);
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

/* Synchronous page data. */
bool sync_page(char *table_name, uint32_t page_num, void *page) {

    ListCell *lc;
    foreach (lc, TableCache) {
        Table *cur_table = lfirst(lc);
        if (streq(cur_table->meta_table->table_name, table_name)) {
            void *old_page = cur_table->pager->pages[page_num];
            switch_shared();
            /* Notice: must copy the page, 
             * because the page will be freed at <remove_table_buffer> */
            cur_table->pager->pages[page_num] = copy_block(page, PAGE_SIZE);
            if (old_page != page)
                free_block(old_page);
            switch_local();
            return true;
        }
    }
    
    return false;
}

/* Synchronous page size. */
bool sync_page_size(char *table_name, uint32_t page_size) {

    ListCell *lc;
    foreach (lc, TableCache) {
        Table *cur_table = lfirst(lc);
        if (streq(cur_table->meta_table->table_name, table_name)) {
            cur_table->pager->size = page_size;
            return true;
        }
    }

    return false;
}
