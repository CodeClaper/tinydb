#include "data.h"

// get row from insert statement
Row *get_statement_insert_row(Statement *stmt);
// get table from statement
Table *get_statement_table(Statement *stmt);
// Create a table
ExecuteResult statement_create_table(Statement *stmt);
// execute insert statment
ExecuteResult statement_insert(Statement *stmt);
// execute select statment
ExecuteResult statement_select(Statement *stmt);
// execute update statment
ExecuteResult statement_update(Statement *stmt);
// execute delete statment
ExecuteResult statement_delete(Statement *stmt);
// free statement
void free_statement(Statement *statement);

