#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "update.h"
#include "mmu.h"
#include "data.h"
#include "meta.h"
#include "select.h"
#include "delete.h"
#include "copy.h"
#include "compare.h"
#include "table.h"
#include "pager.h"
#include "ltree.h"
#include "check.h"
#include "free.h"
#include "trans.h"
#include "refer.h"
#include "asserts.h"
#include "session.h"
#include "index.h"
#include "xlog.h"
#include "ret.h"
#include "log.h"


/* Update cell */
static void update_cell(Row *row, AssignmentNode *assign_node) {
    for (uint32_t i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        if (strcmp(key_value->key, assign_node->column->column_name) == 0) {
            ValueItemNode *value_item = assign_node->value;
            /* Free old value. */
            free_value(key_value->value, key_value->data_type);
            /* Assign new value. */
            switch(value_item->data_type) {
                case T_BOOL: {
                    key_value->value = db_malloc(sizeof(bool), SDT_BOOL);
                    memcpy(key_value->value, &value_item->value.b_value, sizeof(bool));
                    break;
                }
                case T_INT: {
                    key_value->value = db_malloc(sizeof(int32_t), SDT_INT);
                    memcpy(key_value->value, &value_item->value.i_value, sizeof(int32_t));
                    break;
                }
                case T_LONG: {
                    key_value->value = db_malloc(sizeof(int64_t), SDT_INT);
                    memcpy(key_value->value, &value_item->value.i_value, sizeof(int64_t));
                    break;
                }
                case T_FLOAT: {
                    key_value->value = db_malloc(sizeof(float), SDT_INT);
                    memcpy(key_value->value, &value_item->value.f_value, sizeof(float));
                    break;
                }
                case T_DOUBLE: {
                    key_value->value = db_malloc(sizeof(double), SDT_INT);
                    memcpy(key_value->value, &value_item->value.d_value, sizeof(double));
                    break;
                }
                case T_TIMESTAMP: 
                case T_DATE: {
                    key_value->value = db_malloc(sizeof(time_t), SDT_TIME_T);
                    memcpy(key_value->value, &value_item->value.t_value, sizeof(time_t));
                    break;
                }
                case T_CHAR:
                case T_STRING: {
                    key_value->value = db_strdup(value_item->value.s_value);
                    break;
                }
                case T_REFERENCE:
                    db_log(PANIC, "Not implement yet.");
                    break;
            }    
        }
    } 
}

/* Update row */
static void update_row(Row *row, SelectResult *select_result, Table *table, void *arg) {

    /* Only update row that is visible for current transaction. */
    if (!row_is_visible(row)) 
        return;

    /* Update operation can be regarded as delete + re-insert operation. 
     * It makes transaction roll back simpler. */
    delete_row(row, select_result, table, arg);

    /* For update row funciton, the arg is AssignmentSetNode data type arguement. */
    AssignmentSetNode *assignment_set_node = (AssignmentSetNode *) arg;

    uint32_t value_len = calc_table_row_length(table);
    uint32_t key_len = calc_primary_key_length(table);

    /* Use old primary key as default. */
    void *new_key = row->key;

    /* Handle each of assignment. */
    uint32_t i;
    for (i = 0; i < assignment_set_node->num; i++) {
        AssignmentNode *assign_node = *(assignment_set_node->assignment_node + i);
        MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, assign_node->column->column_name);
        update_cell(row, assign_node);
        if (meta_column->is_primary) { 
            /* If primary key changed, reassign new value. */
            void *new_key = get_value_from_value_item_node(assign_node->value, meta_column);
        }
    }
   
    /* Re-insert. */
    MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);
    row->key = copy_value(new_key, primary_meta_column->column_type);
    Cursor *new_cursor = define_cursor(table, new_key);
    update_transaction_state(row, TR_INSERT);
    insert_leaf_node_cell(new_cursor, row);

    /* Record xlog for insert. */
    Refer *refer = convert_refer(new_cursor);
    insert_xlog_entry(refer, DDL_INSERT);

    /* Free memory. */
    free_cursor(new_cursor);
}

/* Execute update statment. */
void exec_update_statment(UpdateNode *update_node, DBResult *result) {

    /* Check table exists. */
    Table *table = open_table(update_node->table_name);
    if (table == NULL) {
        db_log(ERROR, "Try to open table '%s' fail.", update_node->table_name);
        return;
    }

    /* Query with conditon, and update satisfied condition row. */
    SelectResult *select_result = new_select_result(update_node->table_name);

    /* Before update row, count satisfied row num which help to check. */
    query_with_condition(update_node->condition_node, select_result, count_row, NULL);
    uint32_t update_rows_size = select_result->row_size;

    /* Check out update node. */
    if (!check_update_node(update_node, select_result)) 
        return;

    /* Query with update row operation. */
    query_with_condition(update_node->condition_node, select_result, update_row, update_node->assignment_set_node);

    result->success = true;
    result->rows = update_rows_size;
    assgin_result_message(result, "Successfully updated %d row data.", update_rows_size);

    db_log(SUCCESS, "Successfully updated %d row data.", update_rows_size);

    free_select_result(select_result);

}
