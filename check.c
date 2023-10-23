#include "check.h"
#include "data.h"
#include "table.h"
#include "log.h"
#include "meta.h"
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

static bool if_convert_type(DataType source, DataType target) {
    switch(source) {
        case T_BOOL:
            return target == T_BOOL;
        case T_INT:
            return target == T_INT;
        case T_FLOAT:
            return target == T_INT || target == T_FLOAT;
        case T_DOUBLE:
            return target == T_DOUBLE;
        case T_CHAR:
            return target == T_CHAR;
        case T_STRING:
            return target == T_CHAR || target == T_STRING;
        case T_TIMESTAMP:
            return target == T_TIMESTAMP;
        case T_DATE:
            return target == T_DATE;
    }
}

//Check ident not.
static bool check_value_item_node(MetaTable *meta_table, char *column_name ,ValueItemNode *value_item_node) {
    for (uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, column_name) == 0 && if_convert_type(meta_column->column_type, value_item_node->data_type)) 
            return true;
    }
    log_error_s("Column '%s' data type error.", column_name);
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

// check column set.
static bool check_column_set(ColumnSetNode *column_set_node, MetaTable *meta_table) {
    for (uint32_t i = 0; i < column_set_node->size; i++) {
        ColumnNode *column_node = *(column_set_node->columns + i);
        if (!check_column_node(meta_table, column_node))
            return false;
    } 
    return true;
}

static bool check_value_item_set(ValueItemSetNode *value_item_set_node, MetaTable *meta_table) {
    for (uint32_t i = 0; i < value_item_set_node->num; i++) {
        ValueItemNode *value_item_node = *(value_item_set_node->value_item_node + i);
        if (!check_value_item_node(meta_table, "", value_item_node))
            return false;
    } 
    return true;
}

//Check query param.
bool check_query_param(QueryParam *query_param) {
    Table *table = open_table(query_param->table_name);
    if (table == NULL)
        return false;
    return check_select_items(query_param->select_items, table->meta_table) 
             && check_condition_node(query_param->condition_node, table->meta_table);
}

//Check insert node
bool check_insert_node(InsertNode *insert_node) {
    Table *table = open_table(insert_node->table_name);
    if (table == NULL)
        return false;
    MetaTable *meta_table = table->meta_table;
    if (insert_node->all_column) {
        if (meta_table->column_size != insert_node->value_item_set_node->num) {
            log_error("Column count doesn't match value count");
            return false;
        }
        for (uint32_t i = 0; i < meta_table->column_size; i++) {
            MetaColumn *meta_column = meta_table->meta_column[i];
            ValueItemNode *value_item_node = *(insert_node->value_item_set_node->value_item_node + i);
            if (!if_convert_type(meta_column->column_type, value_item_node->data_type)) {
                log_error_s("Data type convert fail for column '%s'", meta_column->column_name);
                return false;
            }
        }
    } else {
        if (insert_node->columns_set_node->size != insert_node->value_item_set_node->num) {
            log_error("Column count doesn't match value count");
            return false;
        }
        for (uint32_t i = 0; i < insert_node->columns_set_node->size; i++) {
            ColumnNode *column_node = *(insert_node->columns_set_node->columns + i);
            ValueItemNode *value_item_node = *(insert_node->value_item_set_node->value_item_node + i);
            MetaColumn *meta_column = get_meta_column_by_name(meta_table, column_node->column_name);
            if (!if_convert_type(meta_column->column_type, value_item_node->data_type)) {
                log_error_s("Data type convert fail for column '%s'", meta_column->column_name);
                return false;
            }
        }
    }
    return true;
}
