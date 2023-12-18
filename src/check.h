#include "data.h"

/* Check query param.*/
bool check_query_param(QueryParam *query_param);

/* Check insert node. */
bool check_insert_node(InsertNode *insert_node);

/* Check for update node. */
bool check_update_node(UpdateNode *update_node, SelectResult *select_result);

/* Check for delete node. */
bool check_delete_node(DeleteNode *delete_node);

/* Check for create table node. */
bool check_create_table_node(CreateTableNode *create_table_node);
