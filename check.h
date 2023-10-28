#include "data.h"


void *get_value(ValueItemNode *value_item_node);

//Check query param.
bool check_query_param(QueryParam *query_param);

//Check insert node
bool check_insert_node(InsertNode *insert_node);

// check for update node. 
bool check_update_node(UpdateNode *update_node, SelectResult *select_result);
