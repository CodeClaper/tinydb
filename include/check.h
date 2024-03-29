#include <stdbool.h>
#include "data.h"

/* Check SelectNode. */
bool check_select_node(SelectNode *select_node);

/* Check insert node. */
bool check_insert_node(InsertNode *insert_node);

/* Check for update node. */
bool check_update_node(UpdateNode *update_node, SelectResult *select_result);

/* Check for delete node. */
bool check_delete_node(DeleteNode *delete_node);

/* Check for create table node. */
bool check_create_table_node(CreateTableNode *create_table_node);

/* Chech allowed to drop table. */
bool check_drop_table(char *table_name);
