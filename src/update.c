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

/* Adapt to column set node data type. */
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

/* Adapt to select items node data type.*/
static SelectItemsNode *adapt_select_items_node(UpdateNode *update_node, Table *table) {
    SelectItemsNode *select_items_node = db_malloc(sizeof(SelectItemsNode));
    select_items_node->type = SELECT_COLUMNS;
    select_items_node->column_set_node = adapt_column_set_node(table);
    return select_items_node;
}

/* Adapt to query param data type.*/
static QueryParam *adapt_query_param(UpdateNode *update_node, Table *table) {
    QueryParam *query_param = db_malloc(sizeof(QueryParam));
    query_param->table_name = strdup(update_node->table_name);
    query_param->select_items = adapt_select_items_node(update_node, table);
    ConditionNode *condition_node_copy = copy_condition_node(update_node->condition_node);
    query_param->condition_node = tree(condition_node_copy);
    return query_param;
}

/* Update cell */
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
                case T_TIMESTAMP:
                    key_value->value = &value->t_value;
                    break;
                case T_DATE:
                    key_value->value = &value->t_value;
                    break;
                case T_CHAR:
                case T_STRING:
                    db_free(key_value->value); // free old memory.
                    key_value->value = strdup(value->s_value);
                    break;
            }    
        }
    } 
}

/* Update row */
static void update_row(Row *row, SelectResult *select_result, Table *table, void *arg) {
    /* For update row funciton, the arg is AssignmentSetNode data type arguement. */
    AssignmentSetNode *assignment_set_node = (AssignmentSetNode *) arg;

    uint32_t value_len = calc_table_row_length(table);
    uint32_t key_len = calc_primary_key_length(table);

    /* Handle each of assignment. */
    for (uint32_t i = 0; i < assignment_set_node->num; i++) {
        AssignmentNode *assign_node = *(assignment_set_node->assignment_node + i);
        MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, assign_node->column->column_name);
        update_cell(row, assign_node);
        if (meta_column->is_primary) { 

            /* Which means to change primary key, and may casuse space cell movement. */
            void *old_key = row->key;
            void *new_key = get_value_from_value_item_node(assign_node->value, meta_column->column_type);
            if (equal(old_key, new_key, meta_column->column_type)) 
                continue;  /* The Key value not change, nothing to do. */
            else 
            {
                /* In the case, key value change, update = delete + re-insert. */
                /* Delete the old one. */
                Cursor *old_cursor = define_cursor(table, old_key);
                delete_leaf_node_cell(old_cursor); 
                free_value(old_key, meta_column->column_type);

                /* Re-insert the updated one. */
                Cursor *new_cursor = define_cursor(table, new_key);
                row->key = new_key;
                insert_leaf_node_cell(new_cursor, row); 
            }
        } else { 
            /* When it is non-key column, just update the cell value. */
            Cursor *cursor = define_cursor(table, row->key);
            void *leaf_node = get_page(table->pager, cursor->page_num);
            assert(get_node_type(leaf_node) == LEAF_NODE);
            void *destination = serialize_row_data(row, table);
            memcpy(get_leaf_node_cell_value(leaf_node, key_len, value_len, cursor->cell_num), destination, value_len);
            flush_page(table->pager, cursor->page_num);
        }
    }
}

/* Execute update statment. */
ExecuteResult exec_update_statment(UpdateNode *update_node) {
    char buff[BUFF_SIZE];
    Table *table = open_table(update_node->table_name);
    if (table == NULL)
        return EXECUTE_TABLE_OPEN_FAIL;


    /* Adapt to query param. */
    QueryParam *query_param = adapt_query_param(update_node, table);

    /* Query with conditon, and update satisfied condition row. */
    SelectResult *select_result = new_select_result(update_node->table_name);

    /* Before update row, count satisfied row num which help to check. */
    query_with_condition(query_param, select_result, count_row, NULL);

    /* Check out update node. */
    if (!check_update_node(update_node, select_result))
        return EXECUTE_FAIL;

    /* Query with update row operation. */
    query_with_condition(query_param, select_result, update_row, update_node->assignment_set_node);

    /* Send out update result. */
    sprintf(buff, "Successfully updated %d row data.\n", select_result->row_size);
    db_send(buff);

    return EXECUTE_SUCCESS;
}
