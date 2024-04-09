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

#define MAX_TABLE_CACHE_SIZE 100

static TableCache *cache = NULL;

static volatile s_lock slock =  SPIN_UN_LOCKED_STATUS;

/* Initialise table cache. */
void init_table_cache() {
    if (cache == NULL) {
        cache = db_malloc(sizeof(TableCache), SDT_TABLE_CACHE);
        cache->table_list = db_malloc(0, SDT_POINTER);
        cache->size = 0;
    }
}

/* Save or update table cache. */
void save_or_update_table_cache(Table *table) {
    uint32_t i;
    for (i = 0; i < cache->size; i++) {
        Table *current = cache->table_list[i] ;
        if (streq(current->meta_table->table_name, table->meta_table->table_name)) {
            /* Replace and free old table. */
            cache->table_list[i] = table; 
            /* Notice: maybe table not change, only changed, need to free old. */
            if (current != table)
                free_table(current);
            return;
        }
    }
    /* Insert new table cache. */
    cache->size++;
    cache->table_list = db_realloc(cache->table_list, sizeof(Table *) * cache->size);
    cache->table_list[i] = table; 
}

/* Find cache table by name, return null if not exist. */
Table *find_table_cache(char *table_name) {
    uint32_t i;
    for (i = 0; i < cache->size; i++) {
        Table *current = *(cache->table_list + i);
        if (streq(current->meta_table->table_name, table_name))
            return copy_table(current);
    }
    return NULL;
}

/* Remove table cache. */
void *remove_table_cache(char *table_name) {
    int i, j;
    for(i = 0; i < cache->size; i++) {
        Table *current = cache->table_list[i];
        if (strcmp(current->meta_table->table_name, table_name) == 0) {
            /* Right moves to cover. */
            for (j = i; j < cache->size - 1; j++) {
                memcpy(cache->table_list + j, cache->table_list + j + 1, sizeof(Table *));
            }
            memset(cache->table_list + cache->size - 1, 0, sizeof(Table *));
            cache->size--;
            cache->table_list = db_realloc(cache->table_list, sizeof(Table *) * cache->size);
            free_table(current);     
            break;
        }
    }
}

/* Synchronous page data. */
bool sync_page(char *table_name, uint32_t page_num, void *page) {

    spin_lock_acquire(&slock);

    uint32_t i;
    for (i = 0; i < cache->size; i++) {
        Table *cur_table = *(cache->table_list + i);
        if (streq(cur_table->meta_table->table_name, table_name)) {
            void *old_page = cur_table->pager->pages[page_num];
            /* Notice: must copy the page, because the page will be freed at <remove_table_buffer>*/
            cur_table->pager->pages[page_num] = copy_block(page, PAGE_SIZE);
            if (old_page != page)
                free_block(old_page);

            spin_lock_release(&slock);
            return true;
        }
    }
    
    spin_lock_release(&slock);
    return false;
}

/* Synchronous page size. */
bool sync_page_size(char *table_name, uint32_t page_size) {

    spin_lock_acquire(&slock);

    int i;
    for (i = 0; i < cache->size; i++) {
        Table *cur_table = *(cache->table_list + i);
        if (strcmp(cur_table->meta_table->table_name, table_name) == 0) {
            cur_table->pager->size = page_size;

            spin_lock_release(&slock);
            return true;
        }
    }

    spin_lock_release(&slock);
    return false;
}
