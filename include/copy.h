#include <stddef.h>
#include "data.h"

/* Copy value. */
void *copy_value(void *value, DataType data_type, MetaColumn *meta_column); 

/* Copy Key value pair. */
KeyValue *copy_key_value(KeyValue *key_value, MetaTable *meta_table);

/* Copy refer. */
Refer *copy_refer(Refer *refer);

/* Copy row. */
Row *copy_row(Row *row);

/* Copy row igonore system reserved columns. */
Row *copy_row_without_reserved(Row *row);

/* Copy meta column. */
MetaColumn *copy_meta_column(MetaColumn *meta_column);

/* Copy column node. */
ColumnNode *copy_column_node(ColumnNode *column_node);

/* Copy value item node. */
ValueItemNode *copy_value_item_node(ValueItemNode *value_item_node);

/* Copy ValueItemSetNode. */
ValueItemSetNode *copy_value_item_set_node(ValueItemSetNode *value_item_set_node);

/* Copy function value node. */
FunctionValueNode *copy_function_value_node(FunctionValueNode *function_value_node);

/* Copy function node. */
FunctionNode *copy_function_node(FunctionNode *function_node);

/* Copy condition node. */
ConditionNode *copy_condition_node(ConditionNode *condition_node);

/* Copy a ComparisonNode. */
ComparisonNode *copy_comparison_node(ComparisonNode *comparison_node);

/* Copy LimitNode. */
LimitNode *copy_limit_node(LimitNode *limit_node);

/* Copy ReferValue. */
ReferValue *copy_refer_value(ReferValue *refer_value);

/* Copy select items node. */
SelectItemsNode *copy_select_items_node(SelectItemsNode *select_items_node);

/* Copy query param. */
QueryParam *copy_query_param(QueryParam *query_param);

/* Copy a dymamic memory block */
void *copy_block(void *value, size_t size);
