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

/*Delete an existed table. */
bool drop_table(char *table_name);
