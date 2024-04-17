#include "data.h"

/* Generate new db result. */
DBResult *new_db_result();

/* Generate new db result set. */
DBResultSet *new_db_result_set();

/* Add db result to set. */
void add_db_result(DBResultSet *result_set, DBResult *result);

/* Send out db execution result. */
void db_send_result(DBResult *result);

/* Send out db execution result set. */
void db_send_result_set(DBResultSet *result_set);
