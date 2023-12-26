#include "data.h"

/* Initialise transaction. */
void init_transaction();

/* New transaction which will be commited automatically. */
ExecuteResult begin_transaction();

/* Get current thread transction handle. 
 * Firstly, try to find in the xtable, is not found, create new one. */
TransactionHandle *get_current_transaction();

/* Commit transaction manually. */
ExecuteResult commit_transaction();

/* Commit transaction automatically. */
void auto_commit_transaction();

/* Check if row is visible for current transaction. */
bool row_is_visible(Row *row);

/* Update transaction state. */
void update_transaction_state(Row *row, TransOpType trans_op_type);
