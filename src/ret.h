#include "data.h"

/* Generate new db result. */
DBResult *new_db_result();

/* Success resule. */
void success_result(DBResult *result, char *format, ...);

/* Error result. */
void error_result(DBResult *result, ExecuteStatus status, char *format, ...);

/* Send out db execution result. */
void db_send_result(DBResult *result);
