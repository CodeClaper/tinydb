#include "data.h"

/* Make a fake InsertNode. */
InsertNode *fake_insert_node(char *table_name, ValueItemSetNode *value_item_set_node);

/* Execute insert statement. */
Refer *exec_insert_statement(InsertNode *insert_node);
