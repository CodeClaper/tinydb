#include "data.h"

/* Initialise transaction. */
void init_transaction();

/* Any running transaction. */
bool any_transaction_running();

/* New transaction which will be commited automatically. */
void begin_transaction(DBResult *result);

/* Get current thread transction handle. 
 * Firstly, try to find in the xtable, is not found, create new one. */
TransactionHandle *get_current_transaction();

/* Commit transaction manually. */
void commit_transaction(DBResult *result);

/* Commit transaction automatically. */
void auto_commit_transaction(DBResult *result);

/* transaction roll back. */
void rollback();

/* Check if row is visible for current transaction. */
bool row_is_visible(Row *row);

/* Check if a row has been deleted. */
bool row_is_deleted(Row *row);

/* Update transaction state. */
void update_transaction_state(Row *row, TransOpType trans_op_type);
