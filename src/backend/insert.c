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
#include "create.h"
#include "select.h"
#include "check.h"
#include "cache.h"
#include "copy.h"
#include "free.h"
#include "refer.h"
#include "trans.h"
#include "timer.h"
#include "xlog.h"
#include "log.h"
#include "utils.h"
#include "jsonwriter.h"
#include "type.h"

/* Get value in insert node to assign column at index. */
static void *get_insert_value(ValueItemSetNode *value_item_set, uint32_t index, MetaColumn *meta_column) {

    Assert(index < value_item_set->num);

    /* Get value item node at index. */
    ValueItemNode* value_item_node = value_item_set->value_item_node[index];
    return assign_value_from_value_item_node(value_item_node, meta_column);
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

/* Supplement sys_id. */
static void supple_sys_id(Row *row) {
    /* Automatically insert sys_id using current sys time. */
    int64_t sys_id = get_current_sys_time(NANOSECOND);
    KeyValue *sys_id_col = instance(KeyValue);
    sys_id_col->key = db_strdup(SYS_RESERVED_ID_COLUMN_NAME);
    sys_id_col->value = copy_value(&sys_id, T_LONG);
    sys_id_col->data_type = T_LONG;
    row->data[row->column_len - 3] = sys_id_col;

    /* If user not define primary, use sys_id as primary key. */
    if (!row->key)
        row->key = copy_value(&sys_id, T_LONG);
}

/* Generate insert row for all columns. */
static Row *generate_insert_row_for_all(InsertNode *insert_node) {

    ValueItemSetNode *value_set = insert_node->values_or_query_spec->values;

    /* Instance row. */
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
    for (i = 0; i < row->column_len; i++) {

        MetaColumn *meta_column = meta_table->meta_column[i];

        /* Ship system reserved. */
        if (meta_column->sys_reserved) 
            continue;

        KeyValue *key_value = instance(KeyValue);
        key_value->key = db_strdup(meta_column->column_name);
        key_value->data_type = meta_column->column_type;
        key_value->value = get_insert_value(value_set, i, meta_column);

        /* Check if primary key column. */
        if (meta_column->is_primary) 
            row->key = copy_value(key_value->value, key_value->data_type);

        row->data[i] = key_value;
    }
    
    /* Supplement sys_id column. */
    supple_sys_id(row);

    return row;
}

/* Generate insert row for part columns.*/
static Row *generate_insert_row_for_part(InsertNode *insert_node) {

    ColumnSetNode *column_set = insert_node->columns_set_node;
    ValueItemSetNode *value_set = insert_node->values_or_query_spec->values;

    /* Instance row. */
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
    row->column_len = column_set->size + sys_reserved_column_count();
    row->data = db_malloc(sizeof(KeyValue *) * row->column_len, "pointer");
    
    /* Row data. */
    uint32_t i;
    for (i = 0; i < column_set->size; i++) {

        ColumnNode *column = column_set->columns[i];

        MetaColumn *meta_column = get_meta_column_by_name(meta_table, column->column_name);

        if (!meta_table)
            db_log(ERROR, "Not found column '%s' in table '%s'.",
                   column->column_name,
                   meta_table->table_name);

        KeyValue *key_value = instance(KeyValue);
        key_value->key = db_strdup(meta_column->column_name);
        key_value->data_type = meta_column->column_type;
        key_value->value = get_insert_value(value_set, i, meta_column);

        /* Value of KeyValue may be null when it is Refer. */
        if (key_value->data_type == T_REFERENCE && key_value->value == NULL)
            return NULL;
        
        /* Check if primary key column. */
        if (meta_column->is_primary) 
            row->key = copy_value(key_value->value, key_value->data_type);

        row->data[i] = key_value;
    }
    
    /* Supplement sys_id column. */
    supple_sys_id(row);

    return row;
}

/* Generate insert row. */
static Row *generate_insert_row(InsertNode *insert_node) {

    /* Check only for VQ_VALUES. */
    Assert(insert_node->values_or_query_spec->type == VQ_VALUES);
    
    return insert_node->all_column 
            ? generate_insert_row_for_all(insert_node)
            : generate_insert_row_for_part(insert_node);
}

/* Convert to insert row. */
static Row *convert_insert_row(Row *row, Table *table) {

    Row *insert_row = instance(Row);

    insert_row->table_name = db_strdup(table->meta_table->table_name);
    /* Add reserved columns for sys_id, created_xid and expired_xid. */
    insert_row->column_len = row->column_len + 3;
    insert_row->data = db_malloc(sizeof(KeyValue *) * insert_row->column_len, "pointer");

    /* Copy data. */
    uint32_t i;
    for (i = 0; i < row->column_len; i++) {
        insert_row->data[i] = copy_key_value(row->data[i]);
    }

    /* Copy row key. */
    MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);
    Assert(primary_meta_column);
    insert_row->key = copy_value(row->key, primary_meta_column->column_type);

    return insert_row;
}

/* Insert one row. 
 * Return the row refer.
 * */
static Refer *insert_one_row(Table *table, Row *row) {

    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(table->meta_table);
    Assert(primary_key_meta_column);
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
    
    /* Generate insert row. */
    Row *row = generate_insert_row(insert_node);
    Assert(row);

    /* Do insert. */
    Refer *refer = insert_one_row(table, row);

    free_row(row);

    return refer;
}

/* Insert for query spec case. */
static List *insert_for_query_spec(InsertNode *insert_node) {

    /* Check if table exists. */
    Table *table = open_table(insert_node->table_name);
    if (!table) {
        db_log(ERROR, "Try to open table '%s' fail.", insert_node->table_name);
        return NULL;
    }
    
    List *list = create_list(NODE_REFER);

    ValuesOrQuerySpecNode *values_or_query_spec = insert_node->values_or_query_spec;

    /* Make select statement to get safisfied rows. */
    SelectNode *select_node = convert_select_node(values_or_query_spec->query_spec);

    /* Make a DBResult to store query result. */
    DBResult *result = new_db_result();
    result->stmt_type = SELECT_STMT;

    exec_select_statement(select_node, result);

    if (result->success) {
        SelectResult *select_result = (SelectResult *)result->data;

        /* Insert into rows. */
        ListCell *lc;
        int i = 0;
        foreach (lc, select_result->rows) {
            Row *insert_row = convert_insert_row(lfirst(lc), table);
            /* Supplement sys_id column. */
            supple_sys_id(insert_row);
            Refer *refer = insert_one_row(table, insert_row);
            append_list(list, refer);
            free_row(insert_row);
        }
    }

    free_select_node(select_node);
    free_db_result(result);

    return list;
}

/* Combine Refer list with single refer. */
List *combine_single_refer_list(Refer *refer) {
    Assert(refer);
    List *list = create_list(NODE_REFER);
    append_list(list, refer);
    return list;
}

/* Execute insert statement. 
 * Return Refer List if it excutes successfully,
 * otherwise, return NULL.
 * */
List *exec_insert_statement(InsertNode *insert_node) {

    /* Check if insert node valid. */
    if (!check_insert_node(insert_node)) 
        return NULL;

    ValuesOrQuerySpecNode *values_or_query_spec = insert_node->values_or_query_spec;

    switch (values_or_query_spec->type) {
        case VQ_VALUES: {
            Refer *refer = insert_for_values(insert_node);
            return refer 
                ? combine_single_refer_list(refer)
                : NULL;
        }
        case VQ_QUERY_SPEC: {
            /* For query spec, there is no refer. 
             * Note, maybe used in multi-values which will be supported. */
            return insert_for_query_spec(insert_node);
        }
        default: {
            db_log(ERROR, "Unknown ValuesOrQuerySpecNode type.");
            return NULL;
        }
    }
}
