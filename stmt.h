#include "data.h"

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

// execute descrbe statement
ExecuteResult statement_describe(Statement *stmt);

// execute show table statement
ExecuteResult statement_show_tables(Statement *stmt);
