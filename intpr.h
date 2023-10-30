#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"

#ifndef INTPR_H
#define INTPR_H

// make a function value node.
FunctionValueNode *make_function_value_node();

// make a functon node
FunctionNode *make_function_node();

// make a select items node.
SelectItemsNode *make_select_items_node();

// make a select node.
SelectNode *make_select_node();

// make a column node.
ColumnNode *make_column_node();

// make a column set node.
ColumnSetNode *make_column_set_node();

// add column node to set.
void add_column_to_set(ColumnSetNode *column_set_node, ColumnNode *column_node);

// make a condition node.
ConditionNode *make_cond_node();

// make an assignment node.
AssignmentNode *make_assignment_node();

// make an assignment set node.
AssignmentSetNode *make_assignment_set_node();

// add assignment to set.
void add_assignment_to_set(AssignmentSetNode *assignment_set_node, AssignmentNode *assignment_node);

// make a create table node.
CreateTableNode *make_create_table_node();

// make a value item node.
ValueItemNode *make_value_item_node();

// make a value item set node.
ValueItemSetNode *make_value_item_set_node();

// add value item into set.
void add_value_item(ValueItemSetNode *node, ValueItemNode *value_item_node);

// make a column def node.
ColumnDefNode *make_column_def_node();

// make a column def set node.
ColumnDefSetNode *make_column_def_set_node();

// add column def node to set.
void add_column_def_to_set(ColumnDefSetNode *columns_def_set_node, ColumnDefNode *column_def_node);

// make a primary key node.
PrimaryKeyNode *make_primary_key_node();

// make an insert node.
InsertNode *make_insert_node();

// make an update node.
UpdateNode *make_update_node();

// make an insert node.
InsertNode *make_insert_node();

// make an update node.
UpdateNode *make_update_node();

// make a delete node.
DeleteNode *make_delete_node();

// make a describe node.
DescribeNode *make_describe_node();

// make a shwo table node.
ShowTablesNode *make_show_tables_node();

// make an ast node.
ASTNode *make_ast_node();
#endif
