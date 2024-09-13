/*
 *************************************************** Transaction Manager ********************************************************************************************************
 * Auth:        JerryZhou
 * Created:     2023/12/26
 * Modify:      2024/09/13
 * Locataion:   src/trans/trans.c
 * Description:
 *  If you are unfamiliar with transaction and MVCC, this article (https://levelup.gitconnected.com/implementing-your-own-transactions-with-mvcc-bba11cab8e70) will help a lot.
 *  Simply put, the implement of MVCC depends on two system reserved columns, created_xid and expired_xid.
 *  System reserved means it is only visible for system, not accessible for user and are always at the end of row.
 *  [created_xid] stores the id of transaction which create the inserted row.
 *  [expired_xid] stores the id of transaction which delete the row. [expired_xid] always is zero until deleted.
 *
 *  Before talking about how to implement MVCC, we need to know what is visible row and what is locked row.
 *  Visible row is the row who is accessible for current transaction. 
 *  Visible row must satisfy any of the follows conditions:
 *  (1) the current transaction create the row, and the row is not deleted.
 *  (2) other transaction creates the row, and transaction is committed and the row is not deleted.
 *  (3) the row is deleted by another uncommitted transaction (which not creates the row)  
 *  What is locked row. Firstly locked row is visible for at least row transaction.
 *  When the first transaction manipulating the row, other transaction will block until the first transaction committed.
 *
 *  There are four transaction operation types: TR_INSERT, TR_SELECT, TR_DELETE, TR_UPDATE;
 *  For insert operation, created_xid of new row stores the current transaction id and expired_xid stores zore;
 *  For select operation, the current transaction will only accesses visible rows.
 *  For delete operation, expired_xid of deleted row stores the current transaction id.
 *  For update, there is no need to manipulate deletion separately. We can simply treat update operations as delete operations 
 *  and add operations.
 *  Transaction isolation levels are a measure of the extent to which transaction isolation succeeds. 
 *  In particular, transaction isolation levels are defined by the presence or absence of the following phenomena:
 *  (1)  Dirty Reads: A dirty read occurs when a transaction reads data that has not yet been committed. 
 *       For example, suppose transaction 1 updates a row. Transaction 2 reads the updated row before transaction 1 commits the update. 
 *       If transaction 1 rolls back the change, transaction 2 will have read data that is considered never to have existed.
 *  (2)  Nonrepeatable Reads: A nonrepeatable read occurs when a transaction reads the same row twice but gets different data each time. 
 *       For example, suppose transaction 1 reads a row. Transaction 2 updates or deletes that row and commits the update or delete. 
 *       If transaction 1 rereads the row, it retrieves different row values or discovers that the row has been deleted.
 *  (3)  Phantoms: A phantom is a row that matches the search criteria but is not initially seen. 
 *       For example, suppose transaction 1 reads a set of rows that satisfy some search criteria. 
 *       Transaction 2 generates a new row (through either an update or an insert) that matches the search criteria for transaction 1. 
 *       If transaction 1 reexecutes the statement that reads the rows, it gets a different set of rows.
 *  The four transaction isolation levels (as defined by SQL-92) are defined in terms of these phenomena. 
 *  In the following table, an "X" marks each phenomenon that can occur.
 *  -----------------------------------------------------------------------------------------------
 *  - Transaction isolation level        Dirty reads         Nonrepeatable reads         Phantoms -
 *  -----------------------------------------------------------------------------------------------
 *  - Read uncommitted                   X                   X                           X        -
 *  -----------------------------------------------------------------------------------------------
 *  - Read committed                     --                  X                           X        -
 *  -----------------------------------------------------------------------------------------------
 *  - Read uncommitted                   --                  --                          X        -
 *  -----------------------------------------------------------------------------------------------
 *  - Read uncommitted                   --                  --                          --       -
 *  -----------------------------------------------------------------------------------------------
 *
 *******************************************************************************************************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "data.h"
#include "defs.h"
#include "trans.h"
#include "mmu.h"
#include "mem.h"
#include "log.h"
#include "copy.h"
#include "free.h"
#include "timer.h"
#include "refer.h"
#include "asserts.h"
#include "utils.h"
#include "xlog.h"
#include "type.h"
#include "buffer.h"
#include "spinlock.h"

static TransEntry *xheader; /* Store activ transactions. */
static s_lock *xlock;

static void *new_trans_entry(int64_t xid, pid_t pid, bool auto_commit, TransEntry *next);
static void create_xlock();

/* Initialise transaction. */
void init_trans() {
    xheader = new_trans_entry(0, 0, false, NULL);
    create_xlock();
}

/* Generate new TransEntry. */
static void *new_trans_entry(int64_t xid, pid_t pid, bool auto_commit, TransEntry *next) {
    switch_shared();
    TransEntry *entry = instance(TransEntry);
    entry->xid = xid;
    entry->pid = pid;
    entry->auto_commit = auto_commit;
    entry->next = next;
    switch_local();

    return entry;
}


/* Create the xlog. */
static void create_xlock() {
    switch_shared();
    xlock = instance(s_lock);
    init_spin_lock(xlock);
    switch_local();
}

/* Generate next xid. 
 * return next xid, if return -1, there is an error. */
static int64_t next_xid() {
    return get_current_sys_time(NANOSECOND);
}

/* Any running transaction. */
bool any_transaction_running() {
    return !is_null(xheader->next);
}


/* Get the tail of TransEntry list. */
static void *get_trans_tail() {
    TransEntry *entry = xheader;
    while (entry->next) {
        entry = entry->next;
    }

    return entry;
}

/* Find transaction handle by thread id. 
 * If not found, return NULL. */
TransEntry *find_transaction() {

    /* Current thread id. */
    pid_t pid = getpid();

    TransEntry *current = xheader;
    while ((current = current->next)) {
        if (current->pid == pid) 
            return current;
    }

    return NULL;
}


/* Register transaction. */
static void register_transaction(TransEntry *entry) {
    
    acquire_spin_lock(xlock);

    TransEntry *tail = get_trans_tail();
    Assert(tail);
    tail->next = entry;

    release_spin_lock(xlock);
}

/* Destroy transaction. */
static void destroy_transaction() {
    acquire_spin_lock(xlock);
    switch_shared();

    TransEntry *current = xheader;
    TransEntry *pres = xheader;
    while ((current = current->next)) {
        if (current->pid == getpid()) {
            pres->next = current->next;
            db_free(current);
        }
        else
            pres = current;
    }

    switch_local();
    release_spin_lock(xlock);
}

/* Check if a transaction active(uncommitted). */
static bool is_active(int64_t xid) {
    TransEntry *current;
    for (current = xheader; current != NULL; current = current->next) {
        if (current->xid == xid) 
            return true;
    }
    return false;
}

/* New transaction which will be committed automatically. */
void auto_begin_transaction() {

    TransEntry *entry = find_transaction();

    /* Already exists transaction, no need to auto begin transaction. */
    if (entry) 
        return;

    /* Generate new transaction. */
    entry = new_trans_entry(next_xid(), getpid(), true, NULL);
    db_log(INFO, "Auto begin transaction xid: %"PRId64" and pid: %"PRId64".", 
           entry->xid, 
           entry->pid);

    /* Register the transaction. */
    register_transaction(entry);

}

/* Begin a new transaction which need be committed manually. */
void begin_transaction() {

    TransEntry *entry = find_transaction();

    Assert(!entry);

    /* Generate new transaction. */
    entry = new_trans_entry(next_xid(), getpid(), false, NULL);

    /* Register the transaction. */
    register_transaction(entry);

    /* Send message. */
    db_log(SUCCESS, "Begin new transaction xid:%"PRId64" and pid: %"PRId64"successfully.", 
           entry->xid, entry->pid);
}

/* Commit transaction manually. */
void commit_transaction() {

    TransEntry *entry = find_transaction();

    if (is_null(entry) || entry->auto_commit)
        db_log(ERROR, "Not in any transaction, please begin a transaction");

    /* Commit Xlog. */
    commit_xlog();

    /* Destroy transaction. */
    destroy_transaction(); 
    
    db_log(INFO, "Commit the transaction xid: %"PRId64" successfully.", 
           entry->xid);

    db_log(SUCCESS, "Commit the transaction successfully");
}

/* Commit transaction automatically. */
void auto_commit_transaction() {
    TransEntry *entry = find_transaction();

    /* Only deal with auto-commit transaction. */
    if (entry && entry->auto_commit) {

        int64_t xid = entry->xid; 
        /* Destroy transaction. */
        destroy_transaction();

        db_log(SUCCESS, "Auto commit the transaction xid: %"PRId64" successfully.", xid);
    }
}

/* Tranasction rollback. */
void rollback_transaction() {
    TransEntry *entry = find_transaction();

    if (is_null(entry) || entry->auto_commit)
        db_log(ERROR, "Not in any transaction, please begin a transaction");

    execute_roll_back();
    commit_transaction();

    db_log(SUCCESS, "Transaction xid: %"PRId64" rollbacked and commited successfully.", 
           entry->xid);
}


/* Auto transaction rollback. */
void auto_rollback_transaction() {
    if (conf->auto_rollback) {
        TransEntry *entry = find_transaction();

        Assert(entry);
        Assert(!entry->auto_commit);

        execute_roll_back();
        commit_transaction();

        db_log(SUCCESS, "Transaction xid: %"PRId64" rollbacked and commited successfully.", 
               entry->xid);
    }
    
}

/* 
 * Check if row is visible for current transaction. 
 * Visible row must satisfy any of the follows conditions:
 * (1) the current transaction create the row, and the row is not deleted.
 * (2) other transaction creates the row, and transaction is committed and the row is not deleted.
 * (3) the row is deleted by another uncommitted transaction (which not creates the row)
 * */
bool row_is_visible(Row *row) {

    /* Get current transaction. */
    TransEntry *entry = find_transaction();
    
    Assert(entry);

    /* Get row created_xid and expired_xid. */
    KeyValue *created_xid_col = lfirst(second_last_cell(row->data));
    KeyValue *expired_xid_col = lfirst(last_cell(row->data));
    int64_t row_created_xid = *(int64_t *)created_xid_col->value;
    int64_t row_expired_xid = *(int64_t *)expired_xid_col->value;

    /* Three satisfied conditions. */
    if (row_created_xid == entry->xid && row_expired_xid == 0)
        return true;
    if (row_created_xid != entry->xid && !is_active(row_created_xid) && row_expired_xid == 0)
        return true;
    if (row_expired_xid != 0 && row_expired_xid != entry->xid && is_active(row_expired_xid) && row_created_xid != row_expired_xid)
        return true;
    
    return false;
}

/* Check if a row has been deleted. */
bool row_is_deleted(Row *row) {
    KeyValue *expired_xid_col = lfirst(last_cell(row->data));
    int64_t row_expired_xid = *(int64_t *)expired_xid_col->value;
    return row_expired_xid != 0;
}

/* Transaction operation for insert row. */
static void transaction_insert_row(Row *row) {

    /* Get current transaction. */
    TransEntry *entry = find_transaction();

    Assert(entry);

    /* For created_xid */
    KeyValue *created_xid_col = new_key_value(db_strdup(CREATED_XID_COLUMN_NAME), 
                                              copy_value(&entry->xid, T_LONG), 
                                              T_LONG);

    lfirst(second_last_cell(row->data)) = created_xid_col;

    /* For expired_xid */
    int64_t zero = 0;
    KeyValue *expired_xid_col = new_key_value(db_strdup(EXPIRED_XID_COLUMN_NAME),
                                              copy_value(&zero, T_LONG),
                                              T_LONG);
    lfirst(last_cell(row->data)) = expired_xid_col;
}

/* Tranasction operation for delete row. */
static void transaction_delete_row(Row *row) {
    
    /* Get current transaction. */
    TransEntry *entry = find_transaction();

    Assert(entry);

    /* Asssign current transaction id to expired_xid. */
    KeyValue *expired_xid_col = lfirst(last_cell(row->data));

    *(int64_t *)expired_xid_col->value = entry->xid;
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
