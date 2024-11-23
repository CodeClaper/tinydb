#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "buffer.h"
#include "data.h"
#include "cache.h"
#include "mem.h"
#include "log.h"
#include "copy.h"
#include "free.h"
#include "trans.h"
#include "utils.h"
#include "asserts.h"
#include "fdesc.h"
#include "pager.h"
#include "defs.h"
#include "mctx.h"
#include "tablereg.h"

/* Table Buffer. */
static List *buffer_list;

/* Initialise table buffer. */
void init_table_buffer() {
    buffer_list = create_list(NODE_TABLE_BUFFER_ENTRY);
}

/* Generate new TableBufferEntry. */
static void *new_table_buffer_entry(Table *table, int64_t xid) {
    TableBufferEntry *entry = instance(TableBufferEntry);
    entry->table = table;
    entry->xid = xid;
    return entry;
}


/* Save table buffer. */
static Table *save_table_buffer(Table *table) {
    Assert(table);

    /* Try to get current transaction. */
    TransEntry *trans = find_transaction();
    if (is_null(trans)) 
        return NULL;;
    
    table->pager->file_descriptor = get_file_desc(table->meta_table->table_name);

    MemoryContext old_context = CURRENT_MEMORY_CONTEXT;
    MemoryContextSwitchTo(CACHE_MEMORY_CONTEXT);

    Table *dup_table = copy_table(table);
    
    /* Generate TableBufferEntry. */
    TableBufferEntry *entry = new_table_buffer_entry(dup_table, trans->xid);
    
    /* Append to buffer. */
    append_list(buffer_list, entry);

    /* Regist TableReg. */
    try_register_table_reg(table->meta_table->table_name);

    MemoryContextSwitchTo(old_context);

    return dup_table;
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

    return cache_table != NULL
        ? save_table_buffer(cache_table)
        : NULL;
}


/* Loop remove TableBufferEntry. */
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

    MemoryContext old_context = CURRENT_MEMORY_CONTEXT;
    MemoryContextSwitchTo(CACHE_MEMORY_CONTEXT);

    loop_clear_table_buffer(trans);

    /* Destroy TableReg also. */
    destroy_table_reg();

    MemoryContextSwitchTo(old_context);

    return true;
}

/* Remove table buffer. */
void remove_table_buffer(char *table_name) {

    MemoryContext old_context = CURRENT_MEMORY_CONTEXT;
    MemoryContextSwitchTo(CACHE_MEMORY_CONTEXT);

    uint32_t i;
    for (i = 0; i < len_list(buffer_list); i++) {
        TableBufferEntry *entry = lfirst(list_nth_cell(buffer_list, i));
        if (streq(table_name, entry->table->meta_table->table_name)) {
            free_table_buffer_entry(entry);
            list_delete(buffer_list, entry);
            i = 0; // Restart over.
        }  
    }

    MemoryContextSwitchTo(old_context);
}
