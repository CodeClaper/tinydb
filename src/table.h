#include "data.h"
#include "defs.h"

/* Check if table exists. */
bool check_table_exist(char *table_name); 

/* Create a new table. */
void create_table(MetaTable *meta_table, DBResult *result);

/* Open a table file. */
Table *open_table(char *table_name);

/* Define cursor. */
Cursor *define_cursor(Table *table, void *key);

/*Delete an existed table. */
void drop_table(char *table_name, DBResult *result);
