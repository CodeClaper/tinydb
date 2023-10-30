#include "data.h"

//Copy value
void free_value(void *value, DataType data_type);

// free KeyValue
void free_key_value(KeyValue *key_value);

// free row.
void free_row(Row *row);

// free select result.
void free_select_result(SelectResult *select_result);

// free input buffer.
void free_input_buffer(InputBuffer *input_buffer);

//Free meta column.
void free_meta_column(MetaColumn *meta_column);

//Free meta table.
void free_meta_table(MetaTable *meta_table);

//Free table
void free_table(Table *table);

//Free cursor
void free_cursor(Cursor *cursor);

//Free value item node.
void free_value_item_node(ValueItemNode *value_item_node);

//Free function value node.
void free_function_value_node(FunctionValueNode *function_value_node);

//Free function node.
void free_function_node(FunctionNode *function_node);

//Free column def node
void free_column_def_node(ColumnDefNode *column_def_node);

//Free column def set node.
void free_column_def_set_node(ColumnDefSetNode *column_def_set_node);

//Free value item set node.
void free_value_item_set_node(ValueItemSetNode *value_item_set_node);

//Free primary key node.
void free_primary_key_node(PrimaryKeyNode *primary_key_node);

//Free select items node.
void free_select_items_node(SelectItemsNode *select_items_node);

//Free condition node.
void free_condition_node(ConditionNode *condition_node);

//Free select node.
void free_select_node(SelectNode *select_node);

//Free insert node.
void free_insert_node(InsertNode *insert_node);

//Free create table node.
void free_create_table_node(CreateTableNode *create_table_node);

//Free ASTNode.
void free_ast_node(ASTNode *node);

//Free query param.
void free_query_param(QueryParam *query_param);

// Free table list
void free_table_list(TableList *table_list);
