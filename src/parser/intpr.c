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

/* Make a AtomNode. */
AtomNode *make_atom_node() {
    AtomNode *atom_node = instance(AtomNode);
    return atom_node;
}

/* make a value item node. */
ValueItemNode *make_value_item_node() {
    ValueItemNode *value_item_node = instance(ValueItemNode);
    return value_item_node;
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

/* make a column def node. */
ColumnDefNode *make_column_def_node() {
    ColumnDefNode *column_def_node = instance(ColumnDefNode);
    return column_def_node;
}

/* Make ColumnDefOptNode. */
ColumnDefOptNode *make_column_def_opt_node() {
    ColumnDefOptNode *column_def_opt = instance(ColumnDefOptNode);
    return column_def_opt;
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

