#include "data.h"

/* Add db result to set. */
void add_db_result(DBResultSet *result_set, DBResult *result);

/* Send out db execution result set. */
void json_result_set(DBResultSet *result_set);
