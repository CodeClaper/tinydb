#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "buffer.h"
#include "data.h"
#include "cache.h"
#include "mmu.h"
#include "log.h"
#include "copy.h"
#include "free.h"
#include "trans.h"
#include "asserts.h"
#include "spinlock.h"

/* Save or update table buffer. */
static bool save_or_update_table_buffer(Table *table);

/* Table Buffer. */
static TableBuffer *buffer = NULL;

static volatile s_lock lock = SPIN_UN_LOCKED_STATUS;

/* Initialise table buffer. */
void init_table_buffer() {
    if (buffer == NULL) {
        buffer = db_malloc(sizeof(TableBuffer), SDT_TABLE_BUFFER);
        buffer->size = 0;
        buffer->buffer = db_malloc(0, SDT_POINTER); 
    }
}

/* Find table in table buffer. */
Table *find_table_buffer(char *table_name) {

    spin_lock_acquire(&lock);
    
    /* Try to get current transaction. */
    TransactionHandle *trans = find_transaction();

    /* Firstly, find in buffer. */
    if (trans) {
        int32_t i;
        for (i = 0; i < buffer->size; i++) {
            TableBufferEntry *entry = buffer->buffer[i];
            if (strcmp(table_name, entry->table->meta_table->table_name) == 0 
                && entry->xid == trans->xid && entry->tid == trans->tid) {
                spin_lock_release(&lock);
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

    spin_lock_release(&lock);
    return cache_table;
}

/* Save or update table buffer. */
static bool save_or_update_table_buffer(Table *table) {

    assert_not_null(table, "Input table must not be NULL.");

    /* Try to get current transaction. */
    TransactionHandle *trans = find_transaction();
    if (trans == NULL) {
        return false;
    }

    /* Generate TableBufferEntry. */
    TableBufferEntry *entry = db_malloc(sizeof(TableBufferEntry), SDT_TABLE_BUFFER_ENTRY);
    entry->table = table;
    entry->tid = trans->tid;
    entry->xid = trans->xid;
    
    /* Append to buffer. */
    buffer->buffer = db_realloc(buffer->buffer, sizeof(TableBufferEntry *) * (buffer->size + 1));
    buffer->buffer[buffer->size] = entry;
    buffer->size++;

    return true;
}

/* Remove all of whole current transaction releated TableBufferEntries. */
bool remove_table_buffer() {
    /* Try to get current transaction. */
    TransactionHandle *trans = find_transaction();
    if (trans == NULL) {
        return false;
    }

    spin_lock_acquire(&lock);

    int32_t i, j;
    for (i = 0; i < buffer->size; i++) {
        TableBufferEntry *entry = buffer->buffer[i];
        if (entry->xid == trans->xid && entry->tid == trans->tid) {

            /* Right move forwar to cover left space. */
            for (j = i; j < buffer->size - 1; j++) {
                memcpy(buffer->buffer + j, buffer->buffer + j + 1, sizeof(TableBufferEntry *));
            }
            memset(buffer->buffer + buffer->size - 1, 0, sizeof(TableBufferEntry *));
            buffer->size--;
            buffer->buffer = db_realloc(buffer->buffer, sizeof(TableBufferEntry *) * buffer->size);
            free_table_buffer_entry(entry);

            /* Restart loop check. */
            i = 0;
        }  
    }
    
    spin_lock_release(&lock);
    return true;
}
