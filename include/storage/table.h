#include "data.h"
#include "defs.h"
#include <stdbool.h>

/* Get table list. */
List *get_table_list();

/* Check if table exists. */
bool check_table_exist(char *table_name); 

/* Open a table file. */
Table *open_table(char *table_name);

/* Create a new table. */
bool create_table(MetaTable *meta_table);

/* Add new MetaColumn to table.
 * This function is actually bottom-level routine for alter-table-add-column action.
 * */
bool add_new_meta_column(char *table_name, MetaColumn *new_meta_column, ColumnPositionDef *pos);

/*Delete an existed table. */
bool drop_table(char *table_name);
