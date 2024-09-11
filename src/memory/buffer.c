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
#include "mem.h"
#include "fdesc.h"
#include "pager.h"
#include "tablereg.h"

/* Table Buffer. */
static List *buffer_list;

/* Initialise table buffer. */
void init_table_buffer() {
    buffer_list = create_list(NODE_TABLE_BUFFER_ENTRY);
}

static void *new_table_buffer_entry(Table *table, int64_t xid) {
    TableBufferEntry *entry = instance(TableBufferEntry);
    entry->table = table;
    entry->xid = xid;
    return entry;
}


/* Save table buffer. */
static bool save_table_buffer(Table *table) {

    Assert(table);

    /* Try to get current transaction. */
    TransEntry *trans = find_transaction();
    if (!trans) 
        return false;
    
    table->pager->file_descriptor = get_file_desc(table->meta_table->table_name);
    
    /* Generate TableBufferEntry. */
    TableBufferEntry *entry = new_table_buffer_entry(table, trans->xid);
    
    /* Append to buffer. */
    append_list(buffer_list, entry);

    /* Regist TableReg. */
    try_register_table_reg(table->meta_table->table_name);

    return true;
}

/* Find table in table buffer. */
Table *find_table_buffer(char *table_name) {

    /* Try to get current transaction. */
    TransEntry *trans = find_transaction();

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
        save_table_buffer(cache_table);
    } 

    return cache_table;
}


static void loop_clear_table_buffer(TransEntry *trans) {

    uint32_t i;
    for (i = 0; i < len_list(buffer_list); i++) {
        TableBufferEntry *entry = lfirst(list_nth_cell(buffer_list, i));
        if (entry->xid == trans->xid) {
            free_table_buffer_entry(entry);
            list_delete(buffer_list, entry);
            loop_clear_table_buffer(trans); // Restart over.
            break;
        }
    }
    
}

/* Clear all of TableBufferEntries releated whole current transaction. */
bool clear_table_buffer() {
    /* Try to get current transaction. */
    TransEntry *trans = find_transaction();
    if (is_null(trans))
        return false;

    loop_clear_table_buffer(trans);

    /* Destroy TableReg also. */
    destroy_table_reg();

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
