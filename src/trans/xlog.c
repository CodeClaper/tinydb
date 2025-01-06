/*
 ****************************************** Transaction Log Manager************************************************************
 * Auth:        JerryZhou
 * Created:     2024/01/11
 * Modify:      2024/09/05
 * Locataion:   src/trans/xlog.c
 * Description: 
 *  TinyDb transaction log is Write-Ahead Log (WAL). Transaction Log records all transactions and the database modifications 
 *  that are made by each transaction. The transaction log is a critical component of the database and, if there`s a system failure, 
 *  the transaction log might be required to bring your database back to a consistent state.
 *  The Transaction log manager basically supports three functions:
 *  (1) Supports Transaction Roll Back.
 *  (2) Supports recovery data when server restart up.
 *  (3) Support Transaction replication in distributed cluster.
 *******************************************************************************************************************************
 * */

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "xlog.h"
#include "log.h"
#include "mmgr.h"
#include "trans.h"
#include "copy.h"
#include "free.h"
#include "ltree.h"
#include "refer.h"
#include "table.h"
#include "select.h"
#include "asserts.h"
#include "utils.h"
#include "pager.h"


/* XLogTable Buffer. */
static XLogEntry *XLHeader = NULL;

static void reverse_insert(Refer *refer, TransEntry *transaction);
static void reverse_delete(Refer *refer, TransEntry *transaction);
static void reverse_update_delete(Refer *refer, TransEntry *transaction);


/* Genrate new XLogEntry. */
static XLogEntry *new_xlog_entry(int64_t xid, Refer *refer, DDLType type) {
    XLogEntry *entry = instance(XLogEntry);
    entry->type = type;
    entry->next = NULL;
    entry->refer = copy_refer(refer);
    entry->xid = xid;
    return entry;
}


/* Record Xlog. */
void record_xlog(Refer *refer, DDLType type) {

    bool found = false;

    TransEntry *trans = find_transaction();
    Assert(trans);

    /* Switch to CACHE_MEMORY_CONTEXT. */
    MemoryContext oldcontext = CURRENT_MEMORY_CONTEXT;
    MemoryContextSwitchTo(CACHE_MEMORY_CONTEXT);

    XLogEntry *entry = new_xlog_entry(trans->xid, refer, type);
    entry->next = XLHeader;
    XLHeader = entry;
    
    /* Recover the MemoryContext. */
    MemoryContextSwitchTo(oldcontext);
}

/* Update xlog entry refer. */
void update_xlog_entry_refer(ReferUpdateEntity *refer_update_entity) {

    XLogEntry *current = XLHeader;
    if (current) {
        for (; current != NULL; current = current->next) {
            Refer *current_refer = current->refer;
            if (refer_equals(current_refer, refer_update_entity->old_refer)) {

                /* Switch to CACHE_MEMORY_CONTEXT. */
                MemoryContext oldcontext = CURRENT_MEMORY_CONTEXT;
                MemoryContextSwitchTo(CACHE_MEMORY_CONTEXT);

                current->refer = copy_refer(refer_update_entity->new_refer);
                free_refer(current_refer);

                /* Recover the MemoryContext. */
                MemoryContextSwitchTo(oldcontext);
            }
        }  
    }
}

/* Commit XLog . */
void commit_xlog() {
    /* Switch to CACHE_MEMORY_CONTEXT. */
    MemoryContext oldcontext = CURRENT_MEMORY_CONTEXT;
    MemoryContextSwitchTo(CACHE_MEMORY_CONTEXT);

    /* Free memory. */
    free_xlog_entry(XLHeader);
    XLHeader = NULL;

    /* Recover the MemoryContext. */
    MemoryContextSwitchTo(oldcontext);
}

/* Execute rollback. */
void execute_roll_back() {

    TransEntry *trans = find_transaction();
    Assert(trans);

    if (is_null(XLHeader))
        return;
    
    /* Loop to rollback. */
    for (XLogEntry *current = XLHeader; current != NULL; current = current->next) {
        switch (current->type) {
            case DDL_INSERT:
                reverse_insert(current->refer, trans);
                break;
            case DDL_DELETE:
                reverse_delete(current->refer, trans);
                break;
            case DDL_UPDATE_INSERT:
                reverse_insert(current->refer, trans);
                break;
            case DDL_UPDATE_DELETE:
                reverse_update_delete(current->refer, trans);
                break;
            default:
                db_log(PANIC, "Unknown DDLType.");
        }        
    }
}

/* Reverse insert operation. */
static void reverse_insert(Refer *refer, TransEntry *transaction) {
    Row *row = define_row(refer);

    KeyValue *created_xid_col = lfirst(second_last_cell(row->data));
    KeyValue *expired_xid_col = lfirst(last_cell(row->data));
    int64_t created_xid = *(int64_t *)created_xid_col->value;
    assert_true(created_xid == transaction->xid, "System error, row created xid not equals transaction xid");

    /* Delete the insered row. */
    *(int64_t *)expired_xid_col->value = transaction->xid;

    update_row_data(row, convert_cursor(refer));

    flush(refer->table_name);
}

/* Reverse delete operation. 
 * Notice that: when reverse delete operation, it does`t "resurrect" the row, 
 * rather than re-insert the row to keep the principle that visible row always 
 * lies in the forefront of the same key cells.
 * */
static void reverse_delete(Refer *refer, TransEntry *transaction) {
    Row *row = define_row(refer);

    assert_true(row_is_deleted(row), "System error, row not been deleted.");
    
    KeyValue *expired_xid_col = lfirst(last_cell(row->data));
    int64_t row_expired_xid = *(int64_t *)expired_xid_col->value;
    assert_true(row_expired_xid == transaction->xid, "System error, row expired xid not equals transaction xid");

    /* Make the row visible. */
    *(int64_t *)expired_xid_col->value = 0;

    Table *table = open_table(refer->table_name);
    
    /* Repositioning. */
    Cursor *new_cur = define_cursor(table, row->key);

    /* Re-insert. */
    insert_leaf_node_cell(new_cur, row);

    flush(get_table_name(table));
}

/* Reverse update delete transaction. */
static void reverse_update_delete(Refer *refer, TransEntry *transaction) {

    Row *row = define_row(refer);
    assert_true(row_is_deleted(row), "System error, row not been deleted.");

    KeyValue *expired_xid_col = lfirst(last_cell(row->data));
    int64_t row_expired_xid = *(int64_t *)expired_xid_col->value;
    Assert(row_expired_xid == transaction->xid); 

    /* Make the row visible. */
    *(int64_t *)expired_xid_col->value = 0;

    Table *table = open_table(refer->table_name);
    
    /* Repositioning. */
    Cursor *new_cur = define_cursor(table, row->key);
    Refer *new_ref = convert_refer(new_cur);

    /* Lock update refer. */
    add_refer_update_lock(new_ref);

    /* Re-insert. */
    insert_leaf_node_cell(new_cur, row);

    /* Free update refer lock. */
    free_refer_update_lock(new_ref);

    free_cursor(new_cur);
    free_refer(new_ref);

    flush(refer->table_name);
}
