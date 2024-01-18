/*
 * ========================================= Transaction Log Manager============================================================
 * TinyDb transaction log is Write-Ahead Log (WAL). Transaction Log records all transactions and the database modifications 
 * that are made by each transaction. The transaction log is a critical component of the database and, if there`s a system failure, 
 * the transaction log might be required to bring your database back to a consistent state.
 * The Transaction log manager basically supports three functions:
 * (1) Supports Transaction Roll Back.
 * (2) Supports recovery data when server restart up.
 * (3) Support Transaction replication in distributed cluster.
 * ==============================================================================================================================
 * */

#include <stdint.h>
#include <string.h>
#include "xlog.h"
#include "mmu.h"
#include "trans.h"
#include "copy.h"
#include "free.h"
#include "ltree.h"
#include "refer.h"
#include "select.h"
#include "asserts.h"

/* XLogTable Buffer. */
static XLogTable *xtable;

/* Reverse insert operation. */
static void reverse_insert(Refer *refer, TransactionHandle *transaction);

/* Reverse delete operation. */
static void reverse_delete(Refer *refer, TransactionHandle *transaction);

/* Initialise XLOG. */
void init_xlog() {
    xtable = db_malloc(sizeof(XLogTable), SDT_XLOG_TABLE);
    xtable->size = 0;
    xtable->list = db_malloc(sizeof(XLogEntry *) * xtable->size, SDT_POINTER);
}

/* Genrate new XLogEntry. */
static XLogEntry *new_xlog_entry(int64_t xid, Refer *refer, DDLType type) {
    XLogEntry *entry = db_malloc(sizeof(Refer), SDT_XLOG_ENTRY);
    entry->type = type;
    entry->next = NULL;
    entry->refer = copy_refer(refer);
    entry->xid = xid;

    return entry;
}


/* Insert into XLogEntry. */
void insert_xlog_entry(Refer *refer, DDLType type) {
    TransactionHandle *handle = find_transaction();
    XLogEntry *entry = new_xlog_entry(handle->xid, refer, type);

    int i;
    for (i = 0; i < xtable->size; i++) {
        XLogEntry *head = xtable->list[i];
        if (head->xid == handle->xid) {
            entry->next = head;
            xtable->list[i] = entry;
            return;
        }
    }

    xtable->list = db_realloc(xtable->list, sizeof(XLogEntry *) * (xtable->size + 1));
    xtable->list[i] = entry;
    xtable->size++;
}

/* Commit XLog . */
void commit_xlog() {
    TransactionHandle *handle = find_transaction();

    int i, j;
    for (i = 0; i < xtable->size; i++) {
        XLogEntry *head = xtable->list[i];
        if (head->xid == handle->xid) {
            /* Right move forward. */
            for (j = 0; j < xtable->size - 1; j++) {
                memcpy(xtable->list + j, xtable->list + j + 1, sizeof(XLogEntry *));
            }
            memset(xtable->list + j, 0, sizeof(XLogEntry *));

            /* Free memory. */
            free_xlog_entry(head);

            xtable->size--;
            xtable->list = db_realloc(xtable->list, sizeof(XLogEntry *) * xtable->size);
            break;     
        }
    }
}

/* Execute rollback. */
void execute_roll_back() {
    TransactionHandle *transaction = find_transaction();

    XLogEntry *current = NULL;

    int i;
    /* Find current transaction xlog. */
    for (i = 0; i < xtable->size; i++) {
        XLogEntry *head = xtable->list[i];
        if (head->xid == transaction->xid) {
            current = head;
            break;
        }
    }

    assert_not_null(current, "Not found current transaction xlog.");
    
    /* Loop to rollback. */
    for (; current != NULL; current = current->next) {
        switch (current->type) {
            case DDL_INSERT:
                reverse_insert(current->refer, transaction);
                break;
            case DDL_DELETE:
                reverse_delete(current->refer, transaction);
                break;
            case DDL_UPDATE:
                break;
        }        
    }
}

/* Reverse insert operation. */
static void reverse_insert(Refer *refer, TransactionHandle *transaction) {
    Row *row = define_row(refer);
    int64_t row_created_xid = *(int64_t *)row->data[row->column_len - 2]->value;
    assert_true(row_created_xid == transaction->xid, "System error, row created xid not equals transaction xid");
    /* Delete the insered row. */
    *(int64_t *)row->data[row->column_len - 1]->value = transaction->xid;

    update_row_data(row, convert_cursor(refer));
}

/* Reverse delete operation. */
static void reverse_delete(Refer *refer, TransactionHandle *transaction) {
    Row *row = define_row(refer);
    assert_true(row_is_deleted(row), "System error, row not been deleted.");
    int64_t row_expired_xid = *(int64_t *)row->data[row->column_len - 1]->value;
    assert_true(row_expired_xid == transaction->xid, "System error, row expired xid not equals transaction xid");
    /* Make the row visible. */
    *(int64_t *)row->data[row->column_len - 1]->value = 0;

    update_row_data(row, convert_cursor(refer));
}
