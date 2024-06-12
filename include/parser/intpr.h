#include "data.h"

#ifndef INTPR_H
#define INTPR_H

/* Make a DataTypeNode. */
DataTypeNode *make_data_type_node();

/* Make a function value node.  */
FunctionValueNode *make_function_value_node();

/* Make a functon node. */
FunctionNode *make_function_node();

/* Make a select items node. */
SelectItemsNode *make_select_items_node();

/* Make a SelectionNode. */
SelectionNode *make_selection_node();

/* Make a ScalarExpNode. */
ScalarExpNode *make_scalar_exp_node();

/* Make a TableRefNode. */
TableRefNode *make_table_ref_node();

/* Make a TableRefSetNode. */
TableRefSetNode *make_table_ref_set_node();

/* Add a TableRefNode to TableRefSetNode. */
void add_table_ref_to_set(TableRefSetNode *table_ref_set, TableRefNode *table_ref);

/* Make a FromClauseNode. */
FromClauseNode *make_from_clause_node();

/* Make a WhereClauseNode. */
WhereClauseNode *make_where_clause_node();

/* Make a TableExpNode. */
TableExpNode *make_table_exp_node();

/* Make a column node.  */
ColumnNode *make_column_node();

/* Make a CalculateNode. */
CalculateNode *make_calculate_node();

/* Make ColumnDefNode. */
ColumnDefName *make_column_def_name();

/* make a condition node. */
ConditionNode *make_condition_node();

/* Make a PredicateNode */
PredicateNode *make_predicate_node();

/* Make a ComparisonNode. */
ComparisonNode *make_comparison_node();

/* Make a LikeNode. */
LikeNode *make_like_node();

/* Make an InNode. */
InNode *make_in_node();

/* Make a LimitNode. */
LimitNode *make_limit_node();

/* make an assignment node. */
AssignmentNode *make_assignment_node();

/* make an assignment set node. */
AssignmentSetNode *make_assignment_set_node();

/* add assignment to set. */
void add_assignment_to_set(AssignmentSetNode *assignment_set_node, AssignmentNode *assignment_node);

/* make a create table node. */
CreateTableNode *make_create_table_node();

/* Make a DropTableNode. */
DropTableNode *make_drop_table_node();

/* Make a ArrayValue. */
ArrayValue *make_array_value();

/* Make a ReferValue. */
ReferValue *make_refer_value();

/* Make a AtomNode. */
AtomNode *make_atom_node();

/* make a value item node. */
ValueItemNode *make_value_item_node();

/* make a column def node. */
ColumnDefNode *make_column_def_node();

/* Make TableContraintDefNode. */
TableContraintDefNode *make_table_contraint_def_node();

/* Make BaseTableElementNode. */
BaseTableElementNode *make_base_table_element_node();

/* Make ColumnDefOptNode. */
ColumnDefOptNode *make_column_def_opt_node();

/* make a primary key node. */
PrimaryKeyNode *make_primary_key_node();

/* Make a QuerySpecNode. */
QuerySpecNode *make_query_spec_node();

/* Make a ValuesOrQuerySpecNode. */
ValuesOrQuerySpecNode *make_values_or_query_spec_node();

/* Make a select node. */
SelectNode *make_select_node();

/* make an insert node. */
InsertNode *make_insert_node();

/* make an update node. */
UpdateNode *make_update_node();

/* make an insert node. */
InsertNode *make_insert_node();

/* make an update node. */
UpdateNode *make_update_node();

/* make a delete node. */
DeleteNode *make_delete_node();

/* make a describe node. */
DescribeNode *make_describe_node();

/* make a shwo table node. */
ShowNode *make_show_node(ShowNodeType type);

/* make a statement. */
Statement *make_statement();

#endif
