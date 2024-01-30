#include <stdbool.h>
#include "intpr.h"
#include "data.h"
#include "mmu.h"
#include "free.h"


/* make a function value node. */
FunctionValueNode *make_function_value_node() {
    FunctionValueNode *function_value_node = db_malloc(sizeof(FunctionValueNode), SDT_FUNCTION_VALUE_NODE);
    return function_value_node;
}

/* make a functon node. */
FunctionNode *make_function_node() {
    FunctionNode *function_node = db_malloc(sizeof(FunctionNode), SDT_FUNCTION_NODE);
    return function_node;
}

/* make a select items node. */
SelectItemsNode *make_select_items_node() {
    SelectItemsNode *select_items_node = db_malloc(sizeof(SelectItemsNode), SDT_SELECT_ITEMS_NODE);
    return select_items_node;
}

/* make a column node. */
ColumnNode *make_column_node() {
    ColumnNode *column_node = db_malloc(sizeof(ColumnNode), SDT_COLUMN_NODE);
    return column_node;
}

/* make a column set node. */
ColumnSetNode *make_column_set_node() {
    ColumnSetNode *column_set_node = db_malloc(sizeof(ColumnSetNode), SDT_COLUMN_SET_NODE);
    column_set_node->size = 0;
    column_set_node->columns = db_malloc(0, SDT_POINTER);
    return column_set_node;
}

/* add column node to set. */
void add_column_to_set(ColumnSetNode *column_set_node, ColumnNode *column_node) {
    column_set_node->columns = db_realloc(column_set_node->columns, sizeof(ColumnNode *) * (column_set_node->size + 1));
    *(column_set_node->columns + column_set_node->size) = column_node;
    column_set_node->size++;
}

/* Make a ReferValue. */
ReferValue *make_refer_value() {
    ReferValue *refer_value = db_malloc(sizeof(ReferValue), SDT_REFER_VALUE);
    return refer_value;
}

/* make a value item node. */
ValueItemNode *make_value_item_node() {
    ValueItemNode *value_item_node = db_malloc(sizeof(ValueItemNode), SDT_VALUE_ITEM_NODE);
    return value_item_node;
}

ValueItemSetNode *make_value_item_set_node() {
    ValueItemSetNode *node = db_malloc(sizeof(ValueItemSetNode), SDT_VALUE_ITEM_SET_NODE);
    node->value_item_node = db_malloc(0, SDT_POINTER);
    node->num = 0;
    return node;
}

/* add value item into set. */
void add_value_item(ValueItemSetNode *node, ValueItemNode *value_item_node) {
    node->value_item_node = db_realloc(node->value_item_node, sizeof(ValueItemNode *) * (node->num + 1));
    *(node->value_item_node + node->num) = value_item_node;
    node->num++;
}

/* Make a condition node. */
ConditionNode *make_condition_node() {
    ConditionNode *cond_node = db_malloc(sizeof(ConditionNode), SDT_CONDITION_NODE);
    return cond_node;
}

/* Make a PredicateNode */
PredicateNode *make_predicate_node() {
    PredicateNode *predicate = db_malloc(sizeof(PredicateNode), SDT_PREDICATE_NODE);
    return predicate;
}

/* Make a ComparisonNode. */
ComparisonNode *make_comparison_node() {
    ComparisonNode *comparison_node = db_malloc(sizeof(ComparisonNode), SDT_COMPARISON_NODE);
    return comparison_node;
}

/* Make a LikeNode. */
LikeNode *make_like_node() {
    LikeNode *like_node = db_malloc(sizeof(LikeNode), SDT_LIKE_NODE);
    return like_node;
}

/* Make an InNode. */
InNode *make_in_node() {
    InNode *in_node = db_malloc(sizeof(InNode), SDT_IN_NODE);
    return in_node;
}

/* Make a LimitNode. */
LimitNode *make_limit_node() {
    LimitNode *limit_node = db_malloc(sizeof(LimitNode), SDT_LIMIT_NODE);
    return limit_node;
}

/* make an assignment node. */
AssignmentNode *make_assignment_node() {
    AssignmentNode *assignment_node = db_malloc(sizeof(AssignmentNode), SDT_ASSIGNMENT_NODE);
    return assignment_node;
}


/* make an assignment set node. */
AssignmentSetNode *make_assignment_set_node() {
    AssignmentSetNode *assignment_set_node = db_malloc(sizeof(AssignmentSetNode), SDT_ASSIGNMENT_SET_NODE);
    assignment_set_node->assignment_node = db_malloc(0, SDT_POINTER);
    assignment_set_node->num = 0;
    return assignment_set_node;
}

/* add assignment to set. */
void add_assignment_to_set(AssignmentSetNode *assignment_set_node, AssignmentNode *assignment_node) {
    assignment_set_node->assignment_node = db_realloc(assignment_set_node->assignment_node, sizeof(AssignmentNode *) * (assignment_set_node->num + 1));
    *(assignment_set_node->assignment_node + assignment_set_node->num) = assignment_node; 
    assignment_set_node->num++;
}

/* make a column def node. */
ColumnDefNode *make_column_def_node() {
    ColumnDefNode *column_def_node = db_malloc(sizeof(ColumnDefNode), SDT_COLUMN_DEF_NODE);
    return column_def_node;
}

/* make a column def set node. */
ColumnDefSetNode *make_column_def_set_node() {
    ColumnDefSetNode *column_def_set_node = db_malloc(sizeof(ColumnDefSetNode), SDT_COLUMN_DEF_SET_NODE);
    column_def_set_node->column_defs = db_malloc(0, SDT_POINTER);
    column_def_set_node->size = 0;
    return column_def_set_node;
}

/* add column def node to set. */
void add_column_def_to_set(ColumnDefSetNode *columns_def_set_node, ColumnDefNode *column_def_node) {
    columns_def_set_node->column_defs = db_realloc(columns_def_set_node->column_defs, sizeof(ColumnDefNode *) * (columns_def_set_node->size + 1));
    *(columns_def_set_node->column_defs + columns_def_set_node->size) = column_def_node;
    columns_def_set_node->size++;
}

/* make a primary key node. */
PrimaryKeyNode *make_primary_key_node() {
    PrimaryKeyNode *primary_key_node = db_malloc(sizeof(PrimaryKeyNode), SDT_PRIMARY_KEY_NODE);
    return primary_key_node;
}

/* make a select node. */
SelectNode *make_select_node() {
    SelectNode *select_node = db_malloc(sizeof(SelectNode), SDT_SELECT_NODE);
    return select_node;
}

/* make an insert node. */
InsertNode *make_insert_node() {
    InsertNode *insert_node = db_malloc(sizeof(InsertNode), SDT_INSERT_NODE);
    return insert_node;
}

/* make an update node. */
UpdateNode *make_update_node() {
    UpdateNode *update_node = db_malloc(sizeof(UpdateNode), SDT_UPDATE_NODE);
    return update_node;
}

/* make delete node. */
DeleteNode *make_delete_node() {
    DeleteNode *delete_node = db_malloc(sizeof(DeleteNode), SDT_DELETE_NODE);
    return delete_node;
}

/* make a create table node. */
CreateTableNode *make_create_table_node() {
    CreateTableNode *create_table_node = db_malloc(sizeof(CreateTableNode), SDT_CREATE_TABLE_NODE);
    return create_table_node;
}

/* Make a DropTableNode. */
DropTableNode *make_drop_table_node() {
    DropTableNode *drop_table_node = db_malloc(sizeof(DropTableNode), SDT_DROP_TABLE_NODE);
    return drop_table_node;
}

/* make a describe node. */
DescribeNode *make_describe_node() {
    DescribeNode *describe_node = db_malloc(sizeof(DescribeNode), SDT_DESCRIBE_NODE);
    return describe_node;
}

/* make a show table node. */
ShowNode *make_show_node(ShowNodeType type) {
    ShowNode *show_node = db_malloc(sizeof(ShowNode), SDT_SHOW_NODE);
    show_node->type = type;
    return show_node;
}

/* make an ast node. */
ASTNode *make_ast_node() {
    ASTNode *ast_node = db_malloc(sizeof(ASTNode), SDT_AST_NODE);
    return ast_node;
}

