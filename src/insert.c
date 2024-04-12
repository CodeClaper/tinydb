/*
 *================================== Insert Statement Module ===================================
 *   
 *==============================================================================================
 * */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#define _XOPEN_SOURCE
#define __USE_XOPEN
#include <time.h>
#include "insert.h"
#include "mmu.h"
#include "common.h"
#include "table.h"
#include "meta.h"
#include "ltree.h"
#include "table.h"
#include "pager.h"
#include "index.h"
#include "asserts.h"
#include "session.h"
#include "select.h"
#include "check.h"
#include "cache.h"
#include "copy.h"
#include "free.h"
#include "refer.h"
#include "trans.h"
#include "xlog.h"
#include "log.h"
#include "ret.h"

/* Make a fake QueryParam. */
static QueryParam *fake_query_param(char *table_name, ConditionNode *condition_node);
/* Make a fake SelectItemsNode. */
static SelectItemsNode *fake_select_all_items_node();

/* Get the index of column in the insert node. */
static int get_column_index(InsertNode *insert_node, char *column_name) {
    int i;
    for (i = 0; i <insert_node->columns_set_node->size; i++) {
        ColumnNode *column_node = insert_node->columns_set_node->columns[i];
        if (strcmp(column_node->column_name, column_name) == 0)
            return i;
    }
    return -1;
}

/* Get value in insert node to assign column at index. */
static void *get_column_value(InsertNode *insert_node, uint32_t index, MetaColumn *meta_column) {

    /* Get value item node at index. */
    ValueItemNode* value_item_node = insert_node->values_or_query_spec->values->value_item_node[index];

    /* Different data type column, has diffrenet way to get value.
     * Data type CHAR, STRING, DATE, TIMESTAMP both use '%s' format to pass value.
     * And int value may be also FLOAT or DOUBLE. Column meta info helps to define the real data type. */
    switch(meta_column->column_type) {
        case T_CHAR:
        case T_STRING:
            return copy_value(value_item_node->value.s_value, meta_column->column_type);
        case T_INT:
        case T_LONG:
            return copy_value(&value_item_node->value.i_value, meta_column->column_type);
        case T_BOOL:
            return copy_value(&value_item_node->value.b_value, meta_column->column_type);
        case T_DOUBLE: {
            switch(value_item_node->data_type) {
                case T_INT:
                    value_item_node->value.d_value = (double)value_item_node->value.i_value;
                case T_FLOAT:
                    value_item_node->value.d_value = (double)value_item_node->value.f_value;
                case T_DOUBLE:
                    value_item_node->data_type = T_DOUBLE;
                    return copy_value(&value_item_node->value.d_value, meta_column->column_type);
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_FLOAT: {
            switch(value_item_node->data_type) {
                case T_INT:
                    value_item_node->value.f_value = (float) value_item_node->value.i_value;
                case T_FLOAT:
                    value_item_node->data_type = T_FLOAT;
                    return copy_value(&value_item_node->value.f_value, meta_column->column_type);
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_DATE: {
            switch(value_item_node->data_type) {
                case T_STRING: {
                    struct tm *tmp_time = db_malloc(sizeof(struct tm), "tm");
                    strptime(value_item_node->value.s_value, "%Y-%m-%d", tmp_time);
                    tmp_time->tm_sec = 0;
                    tmp_time->tm_min = 0;
                    tmp_time->tm_hour = 0;
                    value_item_node->data_type = T_DATE;
                    value_item_node->value.t_value = mktime(tmp_time);
                    db_free(tmp_time);
                }
                case T_DATE:
                    return copy_value(&value_item_node->value.t_value, meta_column->column_type);
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_TIMESTAMP: {
            switch(value_item_node->data_type) {
                case T_STRING: {
                    struct tm *tmp_time = db_malloc(sizeof(struct tm), "tm");
                    strptime(value_item_node->value.s_value, "%Y-%m-%d %H:%M:%S", tmp_time);
                    value_item_node->data_type = T_TIMESTAMP;
                    value_item_node->value.t_value = mktime(tmp_time);
                    db_free(tmp_time);
                }
                case T_TIMESTAMP:
                    return copy_value(&value_item_node->value.t_value, meta_column->column_type);
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_REFERENCE: {
            switch (value_item_node->value.r_value->type) {
                case DIRECTLY: {
                    InsertNode *insert_node = fake_insert_node(meta_column->table_name, value_item_node->value.r_value->nest_value_item_set);
                    Refer *refer = insert_for_values(insert_node);
                    free_insert_node(insert_node);
                    return refer;
                }
                case INDIRECTLY: {
                    return fetch_refer(meta_column, value_item_node->value.r_value->condition);
                }
            }
            break;
        }
    }
}

/* Fake ValuesOrQuerySpecNode for VALUES type. */
static ValuesOrQuerySpecNode *fake_values_or_query_spec_node(ValueItemSetNode *value_item_set_node) {
    ValuesOrQuerySpecNode *values_or_query_spec = instance(ValuesOrQuerySpecNode);
    values_or_query_spec->type = VQ_VALUES;
    values_or_query_spec->values = copy_value_item_set_node(value_item_set_node);
    return values_or_query_spec;
}

/* Make a fake InsertNode. */
InsertNode *fake_insert_node(char *table_name, ValueItemSetNode *value_item_set_node) {
    InsertNode *insert_node = instance(InsertNode);
    insert_node->table_name = db_strdup(table_name);
    insert_node->all_column = true;
    insert_node->values_or_query_spec = fake_values_or_query_spec_node(value_item_set_node);
    return insert_node;
}

/* Convert QuerySpecNode to SelectionNode. */
static SelectNode *convert_select_node(QuerySpecNode *query_spec) {
    SelectNode *select_node = instance(SelectNode);
    select_node->selection = copy_selection_node(query_spec->selection);
    select_node->table_exp = copy_table_exp_node(query_spec->table_exp);
    return select_node;
}

/* Generate insert row. */
static Row *generate_insert_row(InsertNode *insert_node) {

    Row *row = instance(Row);

    /* Table and MetaTable. */
    Table *table = open_table(insert_node->table_name);
    if (table == NULL) {
        db_log(ERROR, "Try to open table '%s' fail.", insert_node->table_name);
        return NULL;
    }
    MetaTable *meta_table = table->meta_table;
    
    /* Combination */
    row->table_name = db_strdup(meta_table->table_name);
    row->column_len = meta_table->all_column_size;
    row->data = db_malloc(sizeof(KeyValue *) * row->column_len, "pointer");
    
    /* Row data. */
    uint32_t i;
    for(i = 0; i < row->column_len; i++) {

        MetaColumn *meta_column = meta_table->meta_column[i];

        /* Ship system reserved. */
        if (meta_column->sys_reserved) 
            continue;

        KeyValue *key_value = instance(KeyValue);
        key_value->key = db_strdup(meta_column->column_name);
        key_value->data_type = meta_column->column_type;

        if (insert_node->all_column)
            key_value->value = get_column_value(insert_node, i, meta_column);
        else {
            int index = get_column_index(insert_node, key_value->key);          
            key_value->value = get_column_value(insert_node, index, meta_column);
        }

        /* Value of KeyValue may be null when it is Refer. */
        if (key_value->data_type == T_REFERENCE && key_value->value == NULL)
            return NULL;

        assert_not_null(key_value->value, "System error, get key value fail.");

        /* Check if primary key column. */
        if (meta_column->is_primary) 
            row->key = db_strdup(key_value->value);
        *(row->data + i) = key_value;
    }

    return row;
}

/* Convert to insert row. */
static Row *convert_insert_row(Row *row, Table *table) {
    Row *insert_row = instance(Row);

    insert_row->table_name = db_strdup(table->meta_table->table_name);
    /* Add reserved columns for created_xid and expired_xid. */
    insert_row->column_len = row->column_len + 2;
    insert_row->data = db_malloc(sizeof(KeyValue *) * insert_row->column_len, "pointer");
    /* Copy data. */
    uint32_t i;
    for (i = 0; i < row->column_len; i++) {
        insert_row->data[i] = copy_key_value(row->data[i]);
    }
    /* Copy row key. */
    MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);
    insert_row->key = copy_value(row->key, primary_meta_column->column_type);

    return insert_row;
}

/* Insert one row. 
 * Return the row refer.
 * */
static Refer *insert_one_row(Table *table, Row *row) {

    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(table->meta_table);
    Cursor *cursor = define_cursor(table, row->key);
    if (check_duplicate_key(cursor, row->key) && !cursor_is_deleted(cursor)) {
        db_log(ERROR, "key '%s' in table '%s' already exists, not allow duplicate key.", 
               get_key_str(row->key, primary_key_meta_column->column_type), 
               table->meta_table->table_name);
        /* Free unuesed memeory */
        free_cursor(cursor);
        return NULL;
    }

    /* Update row transaction state for insert. */
    update_transaction_state(row, TR_INSERT);

    /* Insert into leaf node. */
    insert_leaf_node_cell(cursor, row);

    /* Convert to Refer. */
    Refer *refer = convert_refer(cursor);

    /* Record xlog for insert operation. */
    insert_xlog_entry(refer, DDL_INSERT);

    /* Free useless memeory */
    free_cursor(cursor);

    return refer;    
}

/* Insert for values case. */
Refer *insert_for_values(InsertNode *insert_node) {
    /* Check if table exists. */
    Table *table = open_table(insert_node->table_name);
    if (!table) {
        db_log(ERROR, "Try to open table '%s' fail.", insert_node->table_name);
        return NULL;
    }

    Row *row = generate_insert_row(insert_node);
    if (!row) 
        return NULL;

    Refer *refer = insert_one_row(table, row);

    free_row(row);

    return refer;
}

/* Insert for query spec case. */
static ReferSet *insert_for_query_spec(InsertNode *insert_node) {

    /* Check if table exists. */
    Table *table = open_table(insert_node->table_name);
    if (!table) {
        db_log(ERROR, "Try to open table '%s' fail.", insert_node->table_name);
        return NULL;
    }
    
    ReferSet *refer_set = instance(ReferSet);

    ValuesOrQuerySpecNode *values_or_query_spec = insert_node->values_or_query_spec;
    /* Make select statement to get safisfied rows. */
    SelectNode *select_node = convert_select_node(values_or_query_spec->query_spec);
    DBResult *result = new_db_result();
    result->stmt_type = SELECT_STMT;
    exec_select_statement(select_node, result);

    if (result->success) {
        SelectResult *select_result = (SelectResult *)result->data;
        refer_set->size = select_result->row_size;
        refer_set->set = db_malloc(sizeof(Refer *) * refer_set->size, "pointer");
        /* Insert into rows. */
        uint32_t i;
        for (i = 0; i < select_result->row_size; i++) {
            Row *insert_row = convert_insert_row(select_result->rows[i], table);
            Refer *refer = insert_one_row(table, insert_row);
            refer_set->set[i] = refer;
            free_row(insert_row);
        }
    }

    free_select_node(select_node);
    free_db_result(result);

    return refer_set;
}

/* Execute insert statement. 
 * Return ReferSet if it excutes successfully,
 * otherwise, return NULL.
 * */
ReferSet *exec_insert_statement(InsertNode *insert_node) {

    /* Check if insert node valid. */
    if (!check_insert_node(insert_node)) 
        return NULL;

    ValuesOrQuerySpecNode *values_or_query_spec = insert_node->values_or_query_spec;

    switch (values_or_query_spec->type) {
        case VQ_VALUES: {
            Refer *refer = insert_for_values(insert_node);
            if (!refer) return NULL;
            ReferSet *refer_set = instance(ReferSet);
            refer_set->size = 1;
            refer_set->set = db_malloc(sizeof(Refer *) * refer_set->size, "pointer");
            refer_set->set[0] = refer;
            return refer_set;
        }
        case VQ_QUERY_SPEC: {
            /* For query spec, there is no refer. 
             * Note, maybe used in multi-values which will be supported. */
            return insert_for_query_spec(insert_node);
        }
    }

}

