#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "update.h"
#include "mem.h"
#include "data.h"
#include "meta.h"
#include "select.h"
#include "copy.h"
#include "cond.h"
#include "opr.h"
#include "table.h"
#include "pager.h"
#include "node.h"
#include "check.h"
#include "free.h"
#include "session.h"

/*Adapt to column set node data type.*/
static ColumnSetNode *adapt_column_set_node(Table *table) {
    MetaTable *meta_table = table->meta_table;
    ColumnSetNode *column_set_node = db_malloc(sizeof(ColumnSetNode));
    column_set_node->size = meta_table->column_size;
    column_set_node->columns = db_malloc(sizeof(ConditionNode *) * column_set_node->size);
    for (uint32_t i = 0; i < column_set_node->size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        ColumnNode *column_node = db_malloc(sizeof(ColumnNode));
        column_node->exist_table_name = false;
        column_node->column_name = strdup(meta_column->column_name);
        *(column_set_node->columns + i) = column_node;
    }
    return column_set_node;
}

/*Adapt to select items node data type.*/
static SelectItemsNode *adapt_select_items_node(UpdateNode *update_node, Table *table) {
    SelectItemsNode *select_items_node = db_malloc(sizeof(SelectItemsNode));
    select_items_node->type = SELECT_COLUMNS;
    select_items_node->column_set_node = adapt_column_set_node(table);
    return select_items_node;
}

/*Adapt to query param data type.*/
static QueryParam *adapt_query_param(UpdateNode *update_node, Table *table) {
    QueryParam *query_param = db_malloc(sizeof(QueryParam));
    query_param->table_name = strdup(update_node->table_name);
    query_param->select_items = adapt_select_items_node(update_node, table);
    ConditionNode *condition_node_copy = copy_condition_node(update_node->condition_node);
    query_param->condition_node = tree(condition_node_copy);
    return query_param;
}

/*Update cell*/
static void update_cell(Row *row, AssignmentNode *assign_node) {
    for (uint32_t i = 0; i < row->column_len; i++) {
        KeyValue *key_value = *(row->data + i);
        if (strcmp(key_value->key, assign_node->column->column_name) == 0) {
            ValueItemNode *value = assign_node->value;
            switch(value->data_type) {
                case T_BOOL:
                    key_value->value = &value->b_value;
                    break;
                case T_INT:
                    key_value->value = &value->i_value;
                    break;
                case T_FLOAT:
                    key_value->value = &value->f_value;
                    break;
                case T_DOUBLE:
                    key_value->value = &value->d_value;
                    break;
                case T_CHAR:
                    key_value->value = &value->c_value;
                    break;
                case T_TIMESTAMP:
                    key_value->value = &value->t_value;
                    break;
                case T_DATE:
                    key_value->value = &value->t_value;
                    break;
                case T_STRING:
                    db_free(key_value->value); // free old memory.
                    key_value->value = strdup(value->s_value);
                    break;
            }    
        }
    } 
}

/*Update row*/
static void update_row(Row *row, AssignmentSetNode *assignment_set_node, Table *table) {
    uint32_t value_len = calc_table_row_length(table);
    uint32_t key_len = calc_primary_key_length(table);
    for (uint32_t i = 0; i < assignment_set_node->num; i++) {
        AssignmentNode *assign_node = *(assignment_set_node->assignment_node + i);
        MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, assign_node->column->column_name);
        update_cell(row, assign_node);
        if (meta_column->is_primary) { 
            /*It means to change primary key, and may casuse space movement.*/
            void *old_key = row->key;
            void *new_key = get_value(assign_node->value);
            if (equal(old_key, new_key, meta_column->column_type)) {
                /*Key not change, do nothing.*/
                continue; 
            } else {
                Cursor *old_cursor = define_cursor(table, old_key);
                clean_up_obsolute_cell(old_cursor); // make right cell forwar to covert old cell.
                Cursor *new_cursor = define_cursor(table, new_key);
                free_value(old_key, meta_column->column_type);
                row->key = new_key;
                insert_leaf_node(new_cursor, row); // re-insert into leaf node with new cursor.
            }
        } else { 
            /*When it is non-key column, just update the cell value.*/
            Cursor *cursor = define_cursor(table, row->key);
            void *leaf_node = get_page(table->pager, cursor->page_num);
            assert(get_node_type(leaf_node) == LEAF_NODE);
            void *destination = serialize_row_data(row, table);
            memcpy(get_leaf_node_cell_value(leaf_node, key_len, value_len, cursor->cell_num), destination, value_len);
            flush_page(table->pager, cursor->page_num);
        }
    }
}

/*update rows*/
static void update_rows(SelectResult *select_result, AssignmentSetNode *assignment_set_node, Table *table) {
    for (uint32_t i = 0; i < select_result->row_size; i++) {
        Row *current_row = *(select_result->row + i);
        update_row(current_row, assignment_set_node, table);
    } 
}

/*Execute update statment.*/
ExecuteResult exec_update_statment(UpdateNode *update_node) {
    char buff[BUFF_SIZE];
    Table *table = open_table(update_node->table_name);
    if (table == NULL)
        return EXECUTE_TABLE_OPEN_FAIL;
    /*First, query under condition and get rows that satisfy to update*/
    QueryParam *query_param = adapt_query_param(update_node, table);
    SelectResult *select_result = query_with_condition(query_param);
    if (!check_update_node(update_node, select_result)) // check if valid
        return EXECUTE_FAIL;
    /*second, update queried rows.*/
    update_rows(select_result, update_node->assignment_set_node, table);
    sprintf(buff, "Successfully updated %d row data.\n", select_result->row_size);
    db_send(buff);
    return EXECUTE_SUCCESS;
}
