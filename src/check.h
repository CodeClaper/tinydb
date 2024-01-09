#include "data.h"

/* Check query param.*/
bool check_query_param(QueryParam *query_param, DBResult *result);

/* Check insert node. */
bool check_insert_node(InsertNode *insert_node, DBResult *result);

/* Check for update node. */
bool check_update_node(UpdateNode *update_node, SelectResult *select_result, DBResult *result);

/* Check for delete node. */
bool check_delete_node(DeleteNode *delete_node, DBResult *result);

/* Check for create table node. */
bool check_create_table_node(CreateTableNode *create_table_node, DBResult *result);

/* Chech allowed to drop table. */
bool check_drop_table(char *table_name, DBResult *result);
