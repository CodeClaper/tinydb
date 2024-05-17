#include "data.h"

/* Get system reserved columns length. */
uint32_t sys_reserved_column_count();

/* Execute create table statement. */
void exec_create_table_statement(CreateTableNode *create_table_node, DBResult *result);
