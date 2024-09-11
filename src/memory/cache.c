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
            ptr = copy_table(current);
        }
    }
    return ptr;
}


/* Find cache table by name, return null if not exist. 
 * User in inner, not return duplicate.
 * */
static Table *find_table_cache_inner(char *table_name) {

    void *ptr = NULL;

    ListCell *lc;
    foreach (lc, TableCache) {
        Table *current = lfirst(lc);
        if (streq(current->meta_table->table_name, table_name)) {
            ptr = current;
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

    Table *table = find_table_cache_inner(table_name);

    if (table) {

        switch_shared();

        ListCell *lc = list_nth_cell(table->pager->pages, page_num);
        void *old_page = lfirst(lc);

        /* Notice: must copy the page, 
         * because the page will be freed at <remove_table_buffer> */
        lfirst(lc) = copy_block(page, PAGE_SIZE);

        if (old_page != page)
            free_block(old_page);

        switch_local();

        return true;
    }
    
    return false;
}

/* Synchronous page increase. */
bool sync_page_increase(char *table_name, void *page) {

    Table *table = find_table_cache_inner(table_name);

    if (table) {

        switch_shared();

        Pager *pager = table->pager;

        append_list(pager->pages, copy_block(page, PAGE_SIZE));

        pager->size++;

        Assert(len_list(pager->pages) == pager->size);

        switch_local();
    }

    return false;
}
