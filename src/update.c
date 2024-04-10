#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "update.h"
#include "mmu.h"
#include "data.h"
#include "meta.h"
#include "select.h"
#include "delete.h"
#include "insert.h"
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
#include "utils.h"
#include "index.h"
#include "xlog.h"
#include "ret.h"
#include "log.h"

/* Update cell */
static void update_cell(Row *row, AssignmentNode *assign_node) {
    uint32_t i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        if (streq(key_value->key, assign_node->column->column_name)) {
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
                case T_REFERENCE: {
                    ReferValue *refer_value = value_item->value.r_value;
                    Table *table = open_table(row->table_name);
                    MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, key_value->key);
                    switch (refer_value->type) {
                        case DIRECTLY: {
                            InsertNode *insert_node = fake_insert_node(meta_column->table_name, refer_value->nest_value_item_set);
                            Refer *refer = exec_insert_statement(insert_node);
                            free_insert_node(insert_node);
                            key_value->value = refer;
                            break;
                        }
                        case INDIRECTLY: {
                            Refer *refer = fetch_refer(meta_column, refer_value->condition);
                            key_value->value = refer;
                            break;
                        }
                    }
                    break;
                }
            }    
        }
    } 
}

/* Delete row for update */
static void delete_row_for_update(Row *row, Table *table) {
    if (row_is_visible(row)) {
        Cursor *cursor = define_cursor(table, row->key);
        Refer *refer = convert_refer(cursor);
        update_transaction_state(row, TR_DELETE);
        update_row_data(row, cursor);
        insert_xlog_entry(refer, DDL_UPDATE_DELETE);
        free_cursor(cursor);
        free_refer(refer);
    }
}

/* Insert row for update. */
static void insert_row_for_update(Row *row, Table *table) {

    Cursor *new_cur = define_cursor(table, row->key);
    update_transaction_state(row, TR_INSERT);

    /* Insert */
    insert_leaf_node_cell(new_cur, row);

    Refer *new_ref = convert_refer(new_cur);

    /* Record xlog for insert. */
    insert_xlog_entry(new_ref, DDL_UPDATE_INSERT);

    free_cursor(new_cur);
    free_refer(new_ref);
}


/* Update row 
 * Update operation can be regarded as delete + re-insert operation. 
 * It makes transaction roll back simpler. */
static void update_row(Row *row, SelectResult *select_result, Table *table, void *arg) {

    /* Only update row that is visible for current transaction. */
    if (!row_is_visible(row)) 
        return;

    select_result->row_size++;

    /* Get old refer, and lock update refer. */
    Refer *old_refer = define_refer(row);
    add_refer_update_lock(old_refer);

    /* Delete row for update. */
    delete_row_for_update(row, table);

    /* For update row funciton, the arg is AssignmentSetNode data type arguement. */
    AssignmentSetNode *assignment_set_node = (AssignmentSetNode *) arg;

    uint32_t value_len = calc_table_row_length(table);
    uint32_t key_len = calc_primary_key_length(table);

    /* Use old primary key as default. */
    void *old_key = row->key;
    void *new_key = old_key;

    /* Handle each of assignment. */
    uint32_t i;
    for (i = 0; i < assignment_set_node->num; i++) {
        AssignmentNode *assign_node = *(assignment_set_node->assignment_node + i);
        MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, assign_node->column->column_name);
        update_cell(row, assign_node);
        if (meta_column->is_primary) { 
            /* If primary key changed, reassign new value. */
            new_key = get_value_from_value_item_node(assign_node->value, meta_column);
        }
    }
   
    MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);
    row->key = copy_value(new_key, primary_meta_column->column_type);
    
    /* Insert row for update. */
    insert_row_for_update(row, table);

    /* Recalculate Refer, because afer insert, row refer may be changed. */
    Refer *new_refer = define_refer(row);

    /* Free Update refer lock. */
    free_refer_update_lock(old_refer);
    
    ReferUpdateEntity *refer_update_entity = new_refer_update_entity(old_refer, new_refer);
    /* If Refer changed, update refer. */
    if (!refer_equals(old_refer, new_refer)) {
        Row *new_row = define_row(new_refer);
        assert_true(row_is_visible(new_row), "System error, row not visible. ");
        update_related_tables_refer(refer_update_entity);
        free_row(new_row);
    }
        
    /* Free memory. */
    free_refer_update_entity(refer_update_entity);
}

/* Get ConditionNode form WhereClause.. */
static ConditionNode *get_condition_from_where(WhereClauseNode *where_clause) {
    if (where_clause)
        return where_clause->condition;
    else
        return NULL;
}

/* Execute update statment. */
void exec_update_statment(UpdateNode *update_node, DBResult *result) {

    /* Check table exists. */
    Table *table = open_table(update_node->table_name);
    if (table == NULL) {
        db_log(ERROR, "Try to open table '%s' fail.", update_node->table_name);
        return;
    }

    /* Check out update node. */
    if (!check_update_node(update_node)) 
        return;

    /* Query with conditon, and update satisfied condition row. */
    SelectResult *select_result = new_select_result(update_node->table_name);
    ConditionNode *condition_node = get_condition_from_where(update_node->where_clause);

    /* Query with update row operation. */
    query_with_condition(condition_node, select_result, update_row, update_node->assignment_set_node);

    result->success = true;
    result->rows = select_result->row_size;
    result->message = format("Successfully updated %d row data.", result->rows);

    db_log(SUCCESS, "Successfully updated %d row data.", result->rows);
    
    select_result->row_size = 0;
    free_select_result(select_result);
}
