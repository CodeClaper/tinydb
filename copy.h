#include "data.h"

//Copy value
void *copy_value(void *value, DataType data_type); 

// Copy Key value pair
KeyValue *copy_key_value(KeyValue *key_value);

//Copy row
Row *copy_row(Row *row);

//Copy int value node.
IntValueNode *copy_int_value_node(IntValueNode *int_value_node);

//Copy string value node.
StringValueNode *copy_string_value_node(StringValueNode *string_value_node);

//Copy ident node.
IdentNode *copy_ident_node(IdentNode *ident_node);

//Copy value item node.
ValueItemNode *copy_value_item_node(ValueItemNode *value_item_node);

//Copy function value node.
FunctionValueNode *copy_function_value_node(FunctionValueNode *function_value_node);

//Copy function node.
FunctionNode *copy_function_node(FunctionNode *function_node);

//Copy opr node.
OprNode *copy_opr_node(OprNode *opr_node);

//Copy conn node.
ConnNode *copy_conn_node(ConnNode *conn_node);

//Copy condition node.
ConditionNode *copy_condition_node(ConditionNode *condition_node);

//Copy query param.
QueryParam *copy_query_param(QueryParam *query_param);