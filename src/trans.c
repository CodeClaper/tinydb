/*
 *============================================================ Transaction Manager =============================================================================================
 * If you are unfamiliar with transaction and MVCC, this article (https://levelup.gitconnected.com/implementing-your-own-transactions-with-mvcc-bba11cab8e70) will help a lot.
 * Simply put, the implement of MVCC depends on two system reserved columns, created_xid and expired_xid.
 * System reserved means it is only visible for system, not accessible for user and are always at the end of row.
 * [created_xid] stores the id of transaction which create the inserted row.
 * [expired_xid] stores the id of transaction which delete the row. [expired_xid] always is zero until deleted.
 *
 * Before talking about how to implement MVCC, we need to know what is visible row and what is locked row.
 * Visible row is the row who is accessible for current transaction. 
 * Visible row must satisfy any of the follows conditions:
 * (1) the current transaction create the row, and the row is not deleted.
 * (2) other transaction creates the row, and transaction is committed and the row is not deleted.
 * (3) the row is deleted by another uncommitted transaction (which not creates the row)  
 * What is locked row. Firstly locked row is visible for at least row transaction.
 * When the first transaction manipulating the row, other transaction will block until the first transaction committed.
 *
 * There are four transaction operation types: TR_INSERT, TR_SELECT, TR_DELETE, TR_UPDATE;
 * For insert operation, created_xid of new row stores the current transaction id and expired_xid stores zore;
 * For select operation, the current transaction will only accesses visible rows.
 * For delete operation, expired_xid of deleted row stores the current transaction id.
 * For update, there is no need to manipulate deletion separately. We can simply treat update operations as delete operations 
 * and add operations.
 * Transaction isolation levels are a measure of the extent to which transaction isolation succeeds. 
 * In particular, transaction isolation levels are defined by the presence or absence of the following phenomena:
 * (1)  Dirty Reads: A dirty read occurs when a transaction reads data that has not yet been committed. 
 *      For example, suppose transaction 1 updates a row. Transaction 2 reads the updated row before transaction 1 commits the update. 
 *      If transaction 1 rolls back the change, transaction 2 will have read data that is considered never to have existed.
 * (2)  Nonrepeatable Reads: A nonrepeatable read occurs when a transaction reads the same row twice but gets different data each time. 
 *      For example, suppose transaction 1 reads a row. Transaction 2 updates or deletes that row and commits the update or delete. 
 *      If transaction 1 rereads the row, it retrieves different row values or discovers that the row has been deleted.
 * (3)  Phantoms: A phantom is a row that matches the search criteria but is not initially seen. 
 *      For example, suppose transaction 1 reads a set of rows that satisfy some search criteria. 
 *      Transaction 2 generates a new row (through either an update or an insert) that matches the search criteria for transaction 1. 
 *      If transaction 1 reexecutes the statement that reads the rows, it gets a different set of rows.
 * The four transaction isolation levels (as defined by SQL-92) are defined in terms of these phenomena. 
 * In the following table, an "X" marks each phenomenon that can occur.
 * -----------------------------------------------------------------------------------------------
 * - Transaction isolation level        Dirty reads         Nonrepeatable reads         Phantoms -
 * -----------------------------------------------------------------------------------------------
 * - Read uncommitted                   X                   X                           X        -
 * -----------------------------------------------------------------------------------------------
 * - Read committed                     --                  X                           X        -
 * -----------------------------------------------------------------------------------------------
 * - Read uncommitted                   --                  --                          X        -
 * -----------------------------------------------------------------------------------------------
 * - Read uncommitted                   --                  --                          --       -
 * -----------------------------------------------------------------------------------------------
 *===================================================================================================================================================================================
 */
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "trans.h"
#include "session.h"
#include "mmu.h"
#include "log.h"
#include "copy.h"
#include "free.h"
#include "timer.h"
#include "refer.h"
#include "asserts.h"
#include "utils.h"
#include "ret.h"
#include "xlog.h"


static pthread_mutex_t mutex;

static TransactionTable *xtable; /* Store activ transactions. */

/* Generate next xid. 
 * return next xid, if return -1, there is an error. */
static int64_t next_xid() {
    return get_current_sys_time(NANOSECOND);
}

/* Initialise transaction. */
void init_transaction() {
    xtable = instance(TransactionTable);
    xtable->head = NULL;
    xtable->tail = NULL;
    xtable->size = 0;

    pthread_mutex_init(&mutex, NULL);
}

/* Any running transaction. */
bool any_transaction_running() {
    return xtable->size > 0;
}

/* Register transaction. */
static void register_transaction(TransactionHandle *trans_handle) {

    pthread_mutex_lock(&mutex);

    /* First registration. */
    if (xtable->size == 0) {
        xtable->head = trans_handle;
        xtable->tail = trans_handle;
        xtable->size++;
    } else {
        xtable->tail->next = trans_handle;
        xtable->tail = trans_handle;
        xtable->size++;
    }

    pthread_mutex_unlock(&mutex);
}

/* Destroy transaction. */
static bool destroy_transaction(TransactionHandle *trans_handle) {
    pthread_mutex_lock(&mutex);

    /* Maybe is the head. */
    if (xtable->head == trans_handle) {
        xtable->head = trans_handle->next;
        if (xtable->size == 1)
            xtable->tail = xtable->head;
        trans_handle->next = NULL;
        free_transaction_handle(trans_handle);
        xtable->size--;
        pthread_mutex_unlock(&mutex);
        return true;
    }

    /* Loop for find. */
    TransactionHandle *curr, *prev;
    prev = xtable->head;
    for (curr = xtable->head; curr != NULL; prev = curr, curr = curr->next) {
        if (curr == trans_handle) {
            if (xtable->tail == trans_handle)
                xtable->tail = prev;
            /* Skip current. */
            prev->next = curr->next;
            trans_handle->next = NULL;
            free_transaction_handle(trans_handle);
            xtable->size--;
            pthread_mutex_unlock(&mutex);
            return true;
        }        
    }

    pthread_mutex_unlock(&mutex);
    return false;
}

/* Check if a transaction active(uncommitted). */
static bool is_active(int64_t xid) {
    TransactionHandle *current;
    for(current = xtable->head; current != NULL; current = current->next) {
        if (current->xid == xid) 
            return true;
    }
    return false;
}

/* Find transaction handle by thread id. 
 * If not found, return NULL. */
TransactionHandle *find_transaction() {

    /* Current thread id. */
    int64_t tid = pthread_self();

    TransactionHandle *current;
    for(current = xtable->head; current != NULL; current = current->next) {
        if (current->tid == tid) 
            return current;
    }
    return NULL;
}

/* New transaction which will be committed automatically. */
void auto_begin_transaction() {

    TransactionHandle *trans_handle;

    trans_handle = find_transaction();

    /* Already exists transaction, no need to auto begin transaction. */
    if (trans_handle) 
        return;

    /* Generate new transaction. */
    trans_handle = instance(TransactionHandle);
    trans_handle->xid = next_xid();
    trans_handle->tid = pthread_self();
    trans_handle->auto_commit = true;

    db_log(INFO, "Auto begin transaction xid: %"PRId64" and tid: %"PRId64".", trans_handle->xid, trans_handle->tid);

    /* Register the transaction. */
    register_transaction(trans_handle);

}

/* Begin a new transaction which need be committed manually. */
void begin_transaction(DBResult *result) {

    TransactionHandle *trans_handle;

    trans_handle = find_transaction();
    if (trans_handle) {
        db_log(WARN, "Already begin transaction, not allow to repeat.");
        return;
    }

    /* Generate new transaction. */
    trans_handle = instance(TransactionHandle);
    trans_handle->xid = next_xid();
    trans_handle->tid = pthread_self();
    trans_handle->auto_commit = false;

    db_log(INFO, "Begin transaction xid: %"PRId64" and tid: %"PRId64".", trans_handle->xid, trans_handle->tid);

    /* Register the transaction. */
    register_transaction(trans_handle);

    result->success = true;
    result->message = format("Begin transaction xid: %"PRId64" and tid: %"PRId64".", trans_handle->xid, trans_handle->tid);

    /* Send message. */
    db_log(SUCCESS, "Begin new transaction successfully.");
}

/* Commit transaction manually. */
void commit_transaction(DBResult *result) {

    TransactionHandle *trans_handle = find_transaction();
    if (trans_handle == NULL) {
        db_log(ERROR, "Not found any transaction to be committed.");
        return;
    }

    if (trans_handle->auto_commit) {
        db_log(ERROR, "System Logic error, transaction is auto committed but found in manual commit funciton.");
        return;
    }
    
    /* Commit Xlog. */
    commit_xlog();

    /* Destroy transaction. */
    assert_true(destroy_transaction(trans_handle), "Destroy transaction error, xid is %"PRId64" and thread tid %ld.", trans_handle->xid, trans_handle->tid);
    
    db_log(INFO, "Commit the transaction xid: %"PRId64" successfully.", trans_handle->xid);
    
    result->success = true;
    result->message = format("Commit the transaction xid: %"PRId64" successfully.", trans_handle->xid);

    db_log(SUCCESS, "Commit the transaction successfully");
}

/* Commit transaction automatically. */
void auto_commit_transaction() {
    TransactionHandle *trans_handle = find_transaction();

    /* Only deal with auto-commit transaction. */
    if (trans_handle && trans_handle->auto_commit) {
        int64_t xid = trans_handle->xid; 

        /* Destroy transaction. */
        assert_true(destroy_transaction(trans_handle), "Destroy transaction handle error, xid is %"PRId64" and tid is %ld.", trans_handle->xid, trans_handle->tid);

        db_log(INFO, "Auto commit the transaction xid: %"PRId64" successfully.", xid);
    }
}

/* Tranasction rollback. */
void rollback_transaction(DBResult *result) {
    TransactionHandle *trans_handle = find_transaction();
    if (trans_handle && !trans_handle->auto_commit) {
        execute_roll_back();
        commit_transaction(result);
        result->success = true;
        result->message = format("Transaction xid: %"PRId64" rollbacked and commited successfully.", trans_handle->xid);
        db_log(SUCCESS, "Transaction xid: %"PRId64" rollbacked and commited successfully.", trans_handle->xid);
    } 
    else 
        db_log(ERROR, "Not found transaction to rollback.");
}

/* 
 * Check if row is visible for current transaction. 
 *
 * Visible row must satisfy any of the follows conditions:
 * (1) the current transaction create the row, and the row is not deleted.
 * (2) other transaction creates the row, and transaction is committed and the row is not deleted.
 * (3) the row is deleted by another uncommitted transaction (which not creates the row)
 * */
bool row_is_visible(Row *row) {

    /* Get current transaction. */
    TransactionHandle *trans_handle = find_transaction();

    /* Get row created_xid and expired_xid. */
    int64_t row_created_xid = *(int64_t *)row->data[row->column_len - 2]->value;
    int64_t row_expired_xid = *(int64_t *)row->data[row->column_len - 1]->value;

    /* Three satisfied conditions. */
    if (row_created_xid == trans_handle->xid && row_expired_xid == 0)
        return true;
    if (row_created_xid != trans_handle->xid && !is_active(row_created_xid) && row_expired_xid == 0)
        return true;
    if (row_expired_xid != 0 && row_expired_xid != trans_handle->xid && is_active(row_expired_xid) && row_created_xid != row_expired_xid)
        return true;
    
    return false;
}

/* Check if a row has been deleted. */
bool row_is_deleted(Row *row) {
    int64_t row_expired_xid = *(int64_t *)row->data[row->column_len - 1]->value;
    return row_expired_xid != 0;
}

/* Transaction operation for insert row. */
static void transaction_insert_row(Row *row) {

    /* Get current transaction. */
    TransactionHandle *current_trans = find_transaction();

    if (current_trans == NULL) {
        db_log(ERROR, "Not found transaction.");
        return;
    }

    /* For created_xid */
    KeyValue *created_xid_col = instance(KeyValue);
    created_xid_col->key = db_strdup(CREATED_XID_COLUMN_NAME);
    created_xid_col->value = copy_value(&current_trans->xid, T_LONG);
    created_xid_col->data_type = T_LONG;
    row->data[row->column_len - 2] = created_xid_col;

    /* For expired_xid */
    int64_t zero = 0;
    KeyValue *expired_xid_col = instance(KeyValue);
    expired_xid_col->key = db_strdup(EXPIRED_XID_COLUMN_NAME);
    expired_xid_col->value = copy_value(&zero, T_LONG);
    expired_xid_col->data_type = T_LONG;
    row->data[row->column_len - 1] = expired_xid_col;
}

/* Tranasction operation for delete row. */
static void transaction_delete_row(Row *row) {
    
    /* Get current transaction. */
    TransactionHandle *current_trans = find_transaction();

    /* Asssign current transaction id to expired_xid. */
    *(int64_t *)row->data[row->column_len - 1]->value = current_trans->xid;
}

/* Update transaction state. */
void update_transaction_state(Row *row, TransOpType trans_op_type) {
    switch(trans_op_type) {
        case TR_SELECT:
            break;
        case TR_INSERT:
            transaction_insert_row(row);  
            break;
        case TR_DELETE:
            transaction_delete_row(row);
            break;
        case TR_UPDATE:
            break;
    }
}
