#include "data.h"

/* Initialise transaction. */
void init_trans();

/* Any running transaction. */
bool any_transaction_running();

/* New transaction which will be committed automatically. */
void auto_begin_transaction();

/* New transaction which will be commited automatically. */
void begin_transaction();

/* Get current thread transction handle. 
 * Return current thread transaction, return NULL if not found. */
TransEntry *find_transaction();

/* Commit transaction manually. */
void commit_transaction();

/* Commit transaction automatically. */
void auto_commit_transaction();

/* Rollback transaction. */
void rollback_transaction();

/* Check if row is visible for current transaction. */
bool row_is_visible(Row *row);

/* Check if a row has been deleted. */
bool row_is_deleted(Row *row);

/* Update transaction state. */
void update_transaction_state(Row *row, TransOpType trans_op_type);
