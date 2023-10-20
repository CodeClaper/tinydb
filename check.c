#include "check.h"
#include "data.h"
#include "table.h"
#include "log.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

//Check ident not.
static bool check_column_node(MetaTable *meta_table, ColumnNode *column_node) {
    for (uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, column_node->column_name) == 0)
            return true;
    }
    log_error_s_s("Unknown column '%s' in table '%s'", column_node->column_name, meta_table->table_name);
    return false;
}

//Check select items if exist int meta column
static bool check_select_items(SelectItemsNode *select_items_node, MetaTable *meta_table) {
    if (select_items_node->type == SELECT_FUNCTION || select_items_node->type == SELECT_ALL)
        return true;
    for (uint32_t i = 0; i < select_items_node->column_set_node->size; i++) {
        ColumnNode *column_node = *(select_items_node->column_set_node->columns + i);
        if (!check_column_node(meta_table, column_node))
            return false;
    }
    return true;
}

//Check condition node.
static bool check_condition_node(ConditionNode *condition_node, MetaTable *meta_table) {
    if (condition_node == NULL)
        return true;
    switch(condition_node->type) {
        case LOGIC_CONDITION:
            {
                return check_condition_node(condition_node->left, meta_table) && check_condition_node(condition_node->right, meta_table);
            }
        case EXEC_CONDITION:
            {
                return check_column_node(meta_table, condition_node->column);
            }
    }
}

//Check query param.
bool check_query_param(QueryParam *query_param) {
    Table *table = open_table(query_param->table_name);
    if (table == NULL)
        return false;
    return check_select_items(query_param->select_items, table->meta_table) 
             && check_condition_node(query_param->condition_node, table->meta_table);
}
