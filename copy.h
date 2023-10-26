#include "data.h"

//Copy value
void *copy_value(void *value, DataType data_type); 

// Copy Key value pair
KeyValue *copy_key_value(KeyValue *key_value);

//Copy row
Row *copy_row(Row *row);

//Copy meta column.
MetaColumn *copy_meta_column(MetaColumn *meta_column);

//Copy column node.
ColumnNode *copy_column_node(ColumnNode *column_node);

//Copy value item node.
ValueItemNode *copy_value_item_node(ValueItemNode *value_item_node);

//Copy function value node.
FunctionValueNode *copy_function_value_node(FunctionValueNode *function_value_node);

//Copy function node.
FunctionNode *copy_function_node(FunctionNode *function_node);

//Copy condition node.
ConditionNode *copy_condition_node(ConditionNode *condition_node);

//Copy select items node.
SelectItemsNode *copy_select_items_node(SelectItemsNode *select_items_node);

//Copy query param.
QueryParam *copy_query_param(QueryParam *query_param);
