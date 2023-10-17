#include "check.h"
#include "data.h"
#include "table.h"
#include "log.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

//Check ident not.
static bool check_ident_node(MetaTable *meta_table, IdentNode *ident_node) {
    for (uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, ident_node->name) == 0)
            return true;
    }
    log_error_s_s("Unknown column '%s' in table '%s'", ident_node->name, meta_table->table_name);
    return false;
}

//Check select items
static bool check_select_items(SelectItemsNode *select_items_node, MetaTable *meta_table) {
    if (select_items_node->is_function_node || select_items_node->ident_set_node->all_column)
        return true;
    for (uint32_t i = 0; i < select_items_node->ident_set_node->num; i++) {
        IdentNode *ident_node = *(select_items_node->ident_set_node->ident_node + i);
        if (!check_ident_node(meta_table, ident_node))
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
                return check_ident_node(meta_table, condition_node->column);
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
