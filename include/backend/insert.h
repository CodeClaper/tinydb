#include "data.h"


/* Make a fake InsertNode. */
InsertNode *fake_insert_node(char *table_name, List *value_item_set_node);


/* Insert for values case. 
 * Return list of Refer.
 * */
List *insert_for_values(InsertNode *insert_node);


/* Execute insert statement. 
 * Return list of Refer.
 * */
List *exec_insert_statement(InsertNode *insert_node);
