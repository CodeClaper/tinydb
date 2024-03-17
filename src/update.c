#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "update.h"
#include "mmu.h"
#include "data.h"
#include "meta.h"
#include "select.h"
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
#include "ret.h"
#include "log.h"


/* Update cell */
static void update_cell(Row *row, AssignmentNode *assign_node) {
    int i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = *(row->data + i);
        if (strcmp(key_value->key, assign_node->column->column_name) == 0) {
            ValueItemNode *value = assign_node->value;
            switch(value->data_type) {
                case T_BOOL:
                    key_value->value = &value->b_value;
                    break;
                case T_INT:
                case T_LONG:
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
                    db_free(key_value->value); /* free old memory. */
                    key_value->value = db_strdup(value->s_value);
                    break;
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
    if (!row_is_visible(row)) return;

    /* For update row funciton, the arg is AssignmentSetNode data type arguement. */
    AssignmentSetNode *assignment_set_node = (AssignmentSetNode *) arg;

    uint32_t value_len = calc_table_row_length(table);
    uint32_t key_len = calc_primary_key_length(table);

    /* Handle each of assignment. */
    int i;
    for (i = 0; i < assignment_set_node->num; i++) {
        AssignmentNode *assign_node = *(assignment_set_node->assignment_node + i);
        MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, assign_node->column->column_name);
        update_cell(row, assign_node);
        if (meta_column->is_primary) { 

            /* Which means to change primary key, and may casuse space cell movement. */
            void *old_key = row->key;
            void *new_key = get_value_from_value_item_node(assign_node->value, meta_column);
            if (equal(old_key, new_key, meta_column->column_type)) 
                continue;  /* The Key value not change, nothing to do. */
            else {
                /* In the case, key value change, update = delete + re-insert. */
                /* Delete the old one. */
                Cursor *old_cursor = define_cursor(table, old_key);
                delete_leaf_node_cell(old_cursor, old_key); 
                free_value(old_key, meta_column->column_type);
                free_cursor(old_cursor);

                /* Re-insert the updated one. */
                Cursor *new_cursor = define_cursor(table, new_key);
                row->key = new_key;
                insert_leaf_node_cell(new_cursor, row); 
                free_cursor(new_cursor);

            }
        } else { 
            /* When it is non-key column, just update the cell value. */
            Cursor *cursor = define_cursor(table, row->key);
            void *leaf_node = get_page(table->meta_table->table_name, table->pager, cursor->page_num);
            assert_true(get_node_type(leaf_node) == LEAF_NODE, "System error, the node must be leaf type when update row.");
            void *destination = serialize_row_data(row, table);
            memcpy(get_leaf_node_cell_value(leaf_node, key_len, value_len, cursor->cell_num), destination, value_len);
            flush_page(table->meta_table->table_name, table->pager, cursor->page_num);
            free_cursor(cursor);
        }
    }
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

    /* Check out update node. */
    if (!check_update_node(update_node, select_result)) 
        return;

    /* Query with update row operation. */
    query_with_condition(update_node->condition_node, select_result, update_row, update_node->assignment_set_node);

    result->success = true;
    result->rows = select_result->row_size;
    result->message = db_strdup("Successfully updated %d row data.", select_result->row_size);

    db_log(SUCCESS, "Successfully updated %d row data.", select_result->row_size);

}
