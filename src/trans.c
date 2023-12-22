#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include "data.h"
#include "trans.h"
#include "session.h"
#include "mmu.h"
#include "log.h"

/*
*============================================================ Transaction Manager ================================================================
* If you are unfamiliar with transaction, this article (https://levelup.gitconnected.com/implementing-your-own-transactions-with-mvcc-bba11cab8e70) 
* will help a lot.
*=================================================================================================================================================
*/

static TransactionTable *xtable; /* Store transaction in use. */

/* Generate next xid. 
 * return next xid, if return -1, there is an error. */
static long next_xid() {
    char time_str[32];
    struct timespec tv;
    if (clock_gettime(CLOCK_REALTIME, &tv)) {
        db_error("Generate next xid error.");
        return -1;
    }
    sprintf(time_str, "%ld.%.9ld", tv.tv_sec, tv.tv_nsec);
    return round(atof(time_str) * 1e9);
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

/* Check if a transaction active(uncommited). */
static bool is_active(uint64_t xid) {
    TransactionHandle *current;
    for(current = xtable->head; current != NULL; current = current->next) {
        if (current->xid == xid) 
            return true;
    }
    return false;
}

/* Begin a new transaction. */
ExecuteResult begin_transaction() {

    /* Generate new transaction. */
    TransactionHandle *trans_handle = db_malloc2(sizeof(TransactionHandle), "TransactionHandle");
    trans_handle->xid = next_xid();
    trans_handle->tid = pthread_self();

    /* Register the transaction. */
    register_transaction(trans_handle);

    /* Send message. */
    db_send("Begin new transaction successfully and transactionId is [%ld].\n", trans_handle->xid);

    return EXECUTE_SUCCESS;
}

ExecuteResult commit_transaction() {
    db_send("Commit the transaction successfully.\n");
    return EXECUTE_SUCCESS;
}

void auto_commit_transaction() {

}
