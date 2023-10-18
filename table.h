#include "data.h"
#include "defs.h"
//Create a new table
ExecuteResult create_table(MetaTable *meta_table);
//Open a table file
Table *open_table(char *table_name);
//Define cursor
Cursor *define_cursor(Table *table, void *key);
//Delete an existed table
ExecuteResult drop_table(char *table_name);
