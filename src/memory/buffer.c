#include <stdbool.h>
#include <stdint.h>
#include "buffer.h"
#include "data.h"
#include "cache.h"
#include "mmu.h"
#include "log.h"
#include "copy.h"
#include "free.h"
#include "trans.h"
#include "utils.h"
#include "asserts.h"
#include "spinlock.h"

/* Table Buffer. */
static List *buffer_list;

/* Initialise table buffer. */
void init_table_buffer() {
    buffer_list = create_list(NODE_TABLE_BUFFER_ENTRY);
}

/* Save or update table buffer. */
static bool save_or_update_table_buffer(Table *table) {

    assert_not_null(table, "Input table must not be NULL.");

    /* Try to get current transaction. */
    TransactionHandle *trans = find_transaction();
    if (!trans) 
        return false;

    /* Generate TableBufferEntry. */
    TableBufferEntry *entry = instance(TableBufferEntry);
    entry->table = table;
    entry->xid = trans->xid;
    
    /* Append to buffer. */
    append_list(buffer_list, entry);

    return true;
}

/* Find table in table buffer. */
Table *find_table_buffer(char *table_name) {

    /* Try to get current transaction. */
    TransactionHandle *trans = find_transaction();

    /* Firstly, find in buffer. */
    if (trans) {

        ListCell *lc;
        foreach (lc, buffer_list) {
            TableBufferEntry *entry = lfirst(lc);
            if (streq(table_name, entry->table->meta_table->table_name) 
                && entry->xid == trans->xid ) {
                    return entry->table;
            }  
        }
    }
    /* If buffer missing, found in cache. */
    Table *cache_table = find_table_cache(table_name);
    
    if (trans && cache_table) {
        /* Save table buffer. */
        save_or_update_table_buffer(cache_table);
    } 

    return cache_table;
}


/* Clrear all of whole current transaction releated TableBufferEntries. */
bool clear_table_buffer() {
    /* Try to get current transaction. */
    TransactionHandle *trans = find_transaction();
    if (is_null(trans))
        return false;

    uint32_t i;
    for (i = 0; i < len_list(buffer_list); i++) {
        TableBufferEntry *entry = lfirst(list_nth_cell(buffer_list, i));
        if (entry->xid == trans->xid) {
            free_table_buffer_entry(entry);
            list_delete(buffer_list, entry);
            i = 0; // Restart over.
        }
    }
    
    return true;
}

/* Remove table buffer. */
void remove_table_buffer(char *table_name) {

    uint32_t i;
    for (i = 0; i < len_list(buffer_list); i++) {
        TableBufferEntry *entry = lfirst(list_nth_cell(buffer_list, i));
        if (streq(table_name, entry->table->meta_table->table_name)) {
            free_table_buffer_entry(entry);
            list_delete(buffer_list, entry);
            i = 0; // Restart over.
        }  
    }
}
