#include <stdbool.h>
#include "intpr.h"
#include "data.h"
#include "mmu.h"
#include "free.h"


/* Make a DataTypeNode. */
DataTypeNode *make_data_type_node() {
    DataTypeNode *data_type_node = instance(DataTypeNode);
    return data_type_node;
}

/* make a function value node. */
FunctionValueNode *make_function_value_node() {
    FunctionValueNode *function_value_node = instance(FunctionValueNode);
    return function_value_node;
}

/* make a functon node. */
FunctionNode *make_function_node() {
    FunctionNode *function_node = instance(FunctionNode);
    return function_node;
}

/* make a select items node. */
SelectItemsNode *make_select_items_node() {
    SelectItemsNode *select_items_node = instance(SelectItemsNode);
    return select_items_node;
}

/* make a column node. */
ColumnNode *make_column_node() {
    ColumnNode *column_node = instance(ColumnNode);
    return column_node;
}

/* Make a CalculateNode. */
CalculateNode *make_calculate_node() {
    CalculateNode *calculate_node = instance(CalculateNode);
    return calculate_node;
}

/* Make ColumnDefNode. */
ColumnDefName *make_column_def_name() {
    ColumnDefName *column_def_name = instance(ColumnDefName);
    return column_def_name;
}

/* Make ColumnDefNameCommalist. */
ColumnDefNameCommalist *make_column_def_name_list() {
    ColumnDefNameCommalist *column_def_name_list = instance(ColumnDefNameCommalist);
    column_def_name_list->set = db_malloc(0, "pointer");
    column_def_name_list->size = 0;
    return column_def_name_list;
}

/* Add ColumnDefName to set. */
void add_column_def_name_to_set(ColumnDefNameCommalist *list, ColumnDefName *column_def_name) {
    list->set = db_realloc(list->set, sizeof(ColumnDefName *) * (list->size + 1));
    list->set[list->size++] = column_def_name;
}

/* make a column set node. */
ColumnSetNode *make_column_set_node() {
    ColumnSetNode *column_set_node = instance(ColumnSetNode);
    column_set_node->size = 0;
    column_set_node->columns = db_malloc(0, "pointer");
    return column_set_node;
}

/* add column node to set. */
void add_column_to_set(ColumnSetNode *column_set_node, ColumnNode *column_node) {
    column_set_node->columns = db_realloc(column_set_node->columns, sizeof(ColumnNode *) * (column_set_node->size + 1));
    *(column_set_node->columns + column_set_node->size) = column_node;
    column_set_node->size++;
}

/* Make a ArrayValue. */
ArrayValue *make_array_value() {
    ArrayValue *array_value = instance(ArrayValue);
    return array_value;
}

/* Make a ReferValue. */
ReferValue *make_refer_value() {
    ReferValue *refer_value = instance(ReferValue);
    return refer_value;
}

/* make a value item node. */
ValueItemNode *make_value_item_node() {
    ValueItemNode *value_item_node = instance(ValueItemNode);
    return value_item_node;
}

ValueItemSetNode *make_value_item_set_node() {
    ValueItemSetNode *node = instance(ValueItemSetNode);
    node->value_item_node = db_malloc(0, "pointer");
    node->num = 0;
    return node;
}

/* add value item into set. */
void add_value_item(ValueItemSetNode *node, ValueItemNode *value_item_node) {
    node->value_item_node = db_realloc(node->value_item_node, sizeof(ValueItemNode *) * (node->num + 1));
    *(node->value_item_node + node->num) = value_item_node;
    node->num++;
}

/* Make a SelectionNode. */
SelectionNode *make_selection_node() {
    SelectionNode *selection_node = instance(SelectionNode);
    return selection_node;
}

/* Make a ScalarExpNode. */
ScalarExpNode *make_scalar_exp_node() {
    ScalarExpNode *scalar_exp_node = instance(ScalarExpNode);
    return scalar_exp_node;
}

/* Mkae a ScalarExprSetNode. */
ScalarExpSetNode *make_scalar_exp_set_node() {
    ScalarExpSetNode *scalar_exp_set_node = instance(ScalarExpSetNode);
    scalar_exp_set_node->size = 0;
    scalar_exp_set_node->data = db_malloc(0, "pointer");
    return scalar_exp_set_node;
}

/* Add a ScalarExpNode to ScalarExpSetNode. */
void add_scalar_exp_node(ScalarExpSetNode *scalar_exp_set_node, ScalarExpNode *scalar_exp_node) {
    scalar_exp_set_node->data = db_realloc(scalar_exp_set_node->data, sizeof(ScalarExpNode *) * (scalar_exp_set_node->size + 1));
    scalar_exp_set_node->data[scalar_exp_set_node->size] = scalar_exp_node;
    scalar_exp_set_node->size++;
}

/* Make a condition node. */
ConditionNode *make_condition_node() {
    ConditionNode *cond_node = instance(ConditionNode);
    return cond_node;
}

/* Make a PredicateNode */
PredicateNode *make_predicate_node() {
    PredicateNode *predicate = instance(PredicateNode);
    return predicate;
}

/* Make a ComparisonNode. */
ComparisonNode *make_comparison_node() {
    ComparisonNode *comparison_node = instance(ComparisonNode);
    return comparison_node;
}

/* Make a LikeNode. */
LikeNode *make_like_node() {
    LikeNode *like_node = instance(LikeNode);
    return like_node;
}

/* Make an InNode. */
InNode *make_in_node() {
    InNode *in_node = instance(InNode);
    return in_node;
}

/* Make a LimitNode. */
LimitNode *make_limit_node() {
    LimitNode *limit_node = instance(LimitNode);
    return limit_node;
}

/* make an assignment node. */
AssignmentNode *make_assignment_node() {
    AssignmentNode *assignment_node = instance(AssignmentNode);
    return assignment_node;
}

/* make an assignment set node. */
AssignmentSetNode *make_assignment_set_node() {
    AssignmentSetNode *assignment_set_node = instance(AssignmentSetNode);
    assignment_set_node->assignment_node = db_malloc(0, "pointer");
    assignment_set_node->num = 0;
    return assignment_set_node;
}

/* add assignment to set. */
void add_assignment_to_set(AssignmentSetNode *assignment_set_node, AssignmentNode *assignment_node) {
    assignment_set_node->assignment_node = db_realloc(assignment_set_node->assignment_node, sizeof(AssignmentNode *) * (assignment_set_node->num + 1));
    *(assignment_set_node->assignment_node + assignment_set_node->num) = assignment_node; 
    assignment_set_node->num++;
}

/* Make TableContraintDefNode. */
TableContraintDefNode *make_table_contraint_def_node() {
    TableContraintDefNode *node = instance(TableContraintDefNode);
    return node;
}

/* Make BaseTableElementNode. */
BaseTableElementNode *make_base_table_element_node() {
    BaseTableElementNode *node = instance(BaseTableElementNode);
    return node;
}

/* Make BaseTableElementCommalist */
BaseTableElementCommalist *make_base_table_element_commalist() {
    BaseTableElementCommalist *base_table_element_commalist = instance(BaseTableElementCommalist);
    base_table_element_commalist->set = db_malloc(0, "pointer");
    base_table_element_commalist->size = 0;
    return base_table_element_commalist;
}

/* Add BaseTableElementNode to set. */
void add_base_table_element_to_set(BaseTableElementCommalist *list, BaseTableElementNode *node) {
    list->set = db_realloc(list->set, sizeof(BaseTableElementNode *) * (list->size + 1));
    list->set[list->size++] = node;
}

/* make a column def node. */
ColumnDefNode *make_column_def_node() {
    ColumnDefNode *column_def_node = instance(ColumnDefNode);
    return column_def_node;
}

/* make a column def set node. */
ColumnDefSetNode *make_column_def_set_node() {
    ColumnDefSetNode *column_def_set_node = instance(ColumnDefSetNode);
    column_def_set_node->column_defs = db_malloc(0, "pointer");
    column_def_set_node->size = 0;
    return column_def_set_node;
}

/* add column def node to set. */
void add_column_def_to_set(ColumnDefSetNode *columns_def_set_node, ColumnDefNode *column_def_node) {
    columns_def_set_node->column_defs = db_realloc(columns_def_set_node->column_defs, sizeof(ColumnDefNode *) * (columns_def_set_node->size + 1));
    *(columns_def_set_node->column_defs + columns_def_set_node->size) = column_def_node;
    columns_def_set_node->size++;
}

/* Make ColumnDefOptNode. */
ColumnDefOptNode *make_column_def_opt_node() {
    ColumnDefOptNode *column_def_opt = instance(ColumnDefOptNode);
    return column_def_opt;
}

/* Make ColumnDefOptNodeList */
ColumnDefOptNodeList *make_column_def_opt_list() {
    ColumnDefOptNodeList *list = instance(ColumnDefOptNodeList);
    list->size = 0;
    list->set = db_malloc(0, "pointer");
    return list;
}

/* Add ColumnDefOptNode to set. */
void add_column_def_opt_to_set(ColumnDefOptNodeList *list, ColumnDefOptNode *node) {
    list->set = db_realloc(list->set, sizeof(ColumnDefOptNode *) * (list->size + 1));
    list->set[list->size++] = node;
}

/* make a primary key node. */
PrimaryKeyNode *make_primary_key_node() {
    PrimaryKeyNode *primary_key_node = instance(PrimaryKeyNode);
    return primary_key_node;
}

/* Make a TableRefNode. */
TableRefNode *make_table_ref_node() {
    TableRefNode *table_ref_node = instance(TableRefNode);
    return table_ref_node;
}

/* Make a TableRefSetNode. */
TableRefSetNode *make_table_ref_set_node() {
    TableRefSetNode *table_ref_set = instance(TableRefSetNode);
    table_ref_set->size = 0;
    table_ref_set->set = db_malloc(0, "pointer");
    return table_ref_set;
}

/* Add a TableRefNode to TableRefSetNode. */
void add_table_ref_to_set(TableRefSetNode *table_ref_set, TableRefNode *table_ref) {
    table_ref_set->set = db_realloc(table_ref_set->set, sizeof(TableRefNode *) * (table_ref_set->size + 1));
    table_ref_set->set[table_ref_set->size++] = table_ref;
}

/* Make a FromClauseNode. */
FromClauseNode *make_from_clause_node() {
    FromClauseNode *from_clause_node = instance(FromClauseNode);
    return from_clause_node;
}

/* Make a WhereClauseNode. */
WhereClauseNode *make_where_clause_node() {
    WhereClauseNode *where_clause_node = instance(WhereClauseNode);
    return where_clause_node;
}

/* Make a TableExpNode. */
TableExpNode *make_table_exp_node() {
    TableExpNode *table_exp_node = instance(TableExpNode);
    return table_exp_node;
}

/* Make a QuerySpecNode. */
QuerySpecNode *make_query_spec_node() {
    QuerySpecNode *node = instance(QuerySpecNode);
    return node;
}

/* Make a ValuesOrQuerySpecNode. */
ValuesOrQuerySpecNode *make_values_or_query_spec_node() {
    ValuesOrQuerySpecNode *node = instance(ValuesOrQuerySpecNode);
    return node;
}

/* make a select node. */
SelectNode *make_select_node() {
    SelectNode *select_node = instance(SelectNode);
    return select_node;
}

/* make an insert node. */
InsertNode *make_insert_node() {
    InsertNode *insert_node = instance(InsertNode);
    return insert_node;
}

/* make an update node. */
UpdateNode *make_update_node() {
    UpdateNode *update_node = instance(UpdateNode);
    return update_node;
}

/* make delete node. */
DeleteNode *make_delete_node() {
    DeleteNode *delete_node = instance(DeleteNode);
    return delete_node;
}

/* make a create table node. */
CreateTableNode *make_create_table_node() {
    CreateTableNode *create_table_node = instance(CreateTableNode);
    return create_table_node;
}

/* Make a DropTableNode. */
DropTableNode *make_drop_table_node() {
    DropTableNode *drop_table_node = instance(DropTableNode);
    return drop_table_node;
}

/* make a describe node. */
DescribeNode *make_describe_node() {
    DescribeNode *describe_node = instance(DescribeNode);
    return describe_node;
}

/* make a show table node. */
ShowNode *make_show_node(ShowNodeType type) {
    ShowNode *show_node = instance(ShowNode);
    show_node->type = type;
    return show_node;
}

/* make statement. */
Statement *make_statement() {
    Statement *statement = instance(Statement);
    return statement;
}

/* make statements. */
Statements *make_statements() {
    Statements *statements = instance(Statements);
    statements->size = 0;
    statements->list = db_malloc(0, "pointer");
    return statements;
}

/* add statement to statements*/
void add_statement(Statements *statements, Statement *statement) {
    statements->list = db_realloc(statements->list, sizeof(Statement *) * (statements->size + 1));
    statements->list[statements->size++] = statement;
}
