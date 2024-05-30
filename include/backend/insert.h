#include "data.h"

/* Make a fake InsertNode. */
InsertNode *fake_insert_node(char *table_name, ValueItemSetNode *value_item_set_node);

/* Insert for values case. */
Refer *insert_for_values(InsertNode *insert_node);

/* Execute insert statement. */
List *exec_insert_statement(InsertNode *insert_node);
