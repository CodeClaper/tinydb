/*
 *============================================================ Transaction Manager ================================================================
 * If you are unfamiliar with transaction, this article (https://levelup.gitconnected.com/implementing-your-own-transactions-with-mvcc-bba11cab8e70) 
 * will help a lot.
 * Simply put, transaction works througth two system reserved columns, created_xid and expired_xid.
 * System reserved means it is only visible for system, not accessible for user.
 * [created_xid] stores the id of transaction which create the inserted row.
 * [current_xid] stores the id of current transaction. [current_xid] only works when read lock is needed.
 * [expired_xid] stores the id of transaction which delete the row. [expired_xid] always is zero until deleted.
 *
 * Before talking about how to implement transaction, we need to know what is visible row and what is locked row.
 * Visible row is the row who is accessible for current transaction. 
 * Visible row must satisfy any of the follows conditions:
 * (1) the current transaction create the row, and the row is not deleted.
 * (2) other transaction creates the row, and transaction is commited and the row is not deleted.
 * (3) the row is deleted by another uncommited transaction (which not creates the row)  
 * What is locked row. Firstly locked row is visible for at least row transaction.
 * When the first transaction manipulating the row, other transaction will block until the first transaction commited.
 *
 * There are four transaction operation types: TR_INSERT, TR_SELECT, TR_DELETE, TR_UPDATE;
 * For insert operation, created_xid of new row stores the current transaction id and expired_xid stores zore;
 * For select operation, the current transaction will only accesses visible rows.
 * For delete operation, expired_xid of deleted row stores the current transaction id.
 * For update, there is no need to manipulate deletion separately. We can simply treat update operations as delete operations 
 * and add operations, 
 *
 *=================================================================================================================================================
 */
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "trans.h"
#include "session.h"
#include "mmu.h"
#include "log.h"
#include "copy.h"
#include "asserts.h"


static TransactionTable *xtable; /* Store activ transactions. */

/* Generate next xid. 
 * return next xid, if return -1, there is an error. */
static int64_t next_xid() {
    char time_str[32];
    struct timespec tv;
    if (clock_gettime(CLOCK_REALTIME, &tv)) {
        db_error("Generate next xid error.");
        return -1;
    }
    sprintf(time_str, "%ld.%.9ld", tv.tv_sec, tv.tv_nsec);
    int64_t value = round(atof(time_str) * 1e9);
    return value;
}

/* Initialise transaction. */
void init_transaction() {
    xtable = db_malloc2(sizeof(TransactionTable), "TransactionTable");
    xtable->head = NULL;
    xtable->tail = NULL;
    xtable->size = 0;
}

/* Register transaction. */
static void register_transaction(TransactionHandle *trans_handle) {
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
}

/* Destroy transaction. */
static bool destroy_transaction(TransactionHandle *trans_handle) {
    if (xtable->head == trans_handle) {
        xtable->head = trans_handle->next;
        if (xtable->size == 1)
            xtable->tail = xtable->head;
        xtable->size--;
        return true;
    }

    TransactionHandle *curr, *prev;
    prev = xtable->head;

    for (curr = xtable->head; curr != NULL; prev = curr, curr = curr->next) {
        if (curr == trans_handle) {
            if (xtable->tail == trans_handle)
                xtable->tail = prev;
            /* Skip current. */
            prev->next = curr->next;
            xtable->size--;
            return true;
        }        
    }
    return false;
}

/* Check if a transaction active(uncommited). */
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
static TransactionHandle *find_transaction() {

    /* Current thread id. */
    int64_t t_id = pthread_self();

    TransactionHandle *current;
    for(current = xtable->head; current != NULL; current = current->next) {
        if (current->tid == t_id) 
            return current;
    }
    return NULL;
}

/* New transaction which will be commited automatically. */
static TransactionHandle *new_transaction() {

    /* Generate new transaction. */
    TransactionHandle *trans_handle = db_malloc2(sizeof(TransactionHandle), "TransactionHandle");
    trans_handle->xid = next_xid();
    trans_handle->tid = pthread_self();
    trans_handle->auto_commit = true;

    db_info("Generated transaction xid: %"PRIu64" and xid: %"PRIu64".\n", trans_handle->xid, trans_handle->tid);

    /* Register the transaction. */
    register_transaction(trans_handle);

    return trans_handle;
}

/* Begin a new transaction which need be commited manually. */
ExecuteResult begin_transaction() {

    TransactionHandle *trans_handle;

    trans_handle = find_transaction();
    if (trans_handle) {
        db_error("Already begin transaction, not allow to repeat. \n");
        return EXECUTE_FAIL;
    }

    /* Generate new transaction. */
    trans_handle = db_malloc2(sizeof(TransactionHandle), "TransactionHandle");
    trans_handle->xid = next_xid();
    trans_handle->tid = pthread_self();
    trans_handle->auto_commit = false;

    db_info("Generated transaction xid: %"PRIu64" and xid: %"PRIu64".\n", trans_handle->xid, trans_handle->tid);

    /* Register the transaction. */
    register_transaction(trans_handle);

    /* Send message. */
    db_send("Begin new transaction successfully and transactionId is [%ld].\n", trans_handle->xid);

    return EXECUTE_SUCCESS;
}

/* Get current thread transction handle. 
 * Firstly, try to find in the xtable, is not found, create new one. */
TransactionHandle *get_current_transaction() {
    TransactionHandle * trans_handle = find_transaction();
    if (trans_handle)
        return trans_handle;
    else
        return new_transaction();
}

/* Commit transaction manually. */
ExecuteResult commit_transaction() {
    TransactionHandle *trans_handle = find_transaction();
    if (trans_handle == NULL) {
        db_error("Not found any transaction to be commited.\n");
        return EXECUTE_FAIL;
    }
    assert_false(trans_handle->auto_commit, "System Logic error, transaction is auto commited but found in manual commit funciton.\n");
    assert_true(destroy_transaction(trans_handle), "Destroy transaction error, transaction id is %ld and thread id is %ld.\n", trans_handle->xid, trans_handle->tid);
    db_send("Commit the transaction successfully and transactionId is [%ld].\n", trans_handle->xid);
    return EXECUTE_SUCCESS;
}

/* Commit transaction automatically. */
void auto_commit_transaction() {
    TransactionHandle *trans_handle = find_transaction();
    /* Only deal with auto-commit transaction. */
    if (trans_handle && trans_handle->auto_commit) 
        /* Destroy transaction. */
        assert_true(destroy_transaction(trans_handle), "Destroy transaction error, transaction id is %ld and thread id is %ld.\n", trans_handle->xid, trans_handle->tid);
}

/* Check if row is visible for current transaction. 
 *
 * Visible row must satisfy any of the follows conditions:
 * (1) the current transaction create the row, and the row is not deleted.
 * (2) other transaction creates the row, and transaction is commited and the row is not deleted.
 * (3) the row is deleted by another uncommited transaction (which not creates the row)  
 * */
bool row_is_visible(Row *row) {

    TransactionHandle *trans_handle = get_current_transaction();
    assert_not_null(trans_handle, "Not found current transaction.\n");
    int64_t row_created_xid = *(int64_t *)row->data[row->column_len - 2]->value;
    int64_t row_expired_xid = *(int64_t *)row->data[row->column_len - 1]->value;

    /* Three satisfied conditions. */
    if (row_created_xid == trans_handle->xid && row_expired_xid == 0)
        return true;
    if (row_created_xid != trans_handle->xid && !is_active(row_created_xid) && row_expired_xid == 0)
        return true;
    if (row_expired_xid != 0 && is_active(row_expired_xid) && row_created_xid != row_expired_xid)
        return true;
    
    return false;
}

/* Transaction operation for insert row. */
static void transaction_insert_row(Row *row) {

    /* Get current transaction. */
    TransactionHandle *current_trans = get_current_transaction();

    /* Fro created_xid */
    KeyValue *created_xid_col = db_malloc2(sizeof(KeyValue), "KeyValue");
    created_xid_col->key = strdup("created_xid");
    created_xid_col->value = copy_value(&current_trans->xid, T_LONG, NULL);
    created_xid_col->data_type = T_LONG;
    row->data[row->column_len - 2] = created_xid_col;

    /* For expired_xid */
    int64_t zero = 0;
    KeyValue *expired_xid_col = db_malloc2(sizeof(KeyValue), "KeyValue");
    expired_xid_col->key = strdup("expired_xid");
    expired_xid_col->value = copy_value(&zero, T_LONG, NULL);
    expired_xid_col->data_type = T_LONG;
    row->data[row->column_len - 1] = expired_xid_col;
}

/* Tranasction operation for delete row. */
static void transaction_delete_row(Row *row) {
    
    /* Get current transaction. */
    TransactionHandle *current_trans = get_current_transaction();

    /* For expired_xid. */
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
