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
#include "log.h"
#include "ret.h"


/* Make a fake InsertNode. */
static InsertNode *fake_insert_node(char *table_name, ValueItemSetNode *value_item_set_node);
/* Make a fake QueryParam. */
static QueryParam *fake_query_param(char *table_name, ConditionNode *condition_node);
/* Make a fake SelectItemsNode. */
static SelectItemsNode *fake_select_all_items_node();

/* Get column number of insert statement. */
static uint32_t get_insert_column_size(InsertNode *insert_node, MetaTable *meta_table) {
    if (insert_node->all_column)
        return meta_table->column_size;
    else 
        return insert_node->columns_set_node->size;
}

/* Get value number. */
static uint32_t get_value_size(InsertNode *insert_node) {
    return insert_node->value_item_set_node->num;
}

/* Get column name. */
static char *get_column_name(InsertNode *insert_node, uint32_t index, MetaTable *meta_table) {
    if (insert_node->all_column)
        return meta_table->meta_column[index]->column_name;
    else 
        return ((ColumnNode *)(insert_node->columns_set_node->columns + index))->column_name;
}

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
static void *get_column_value(InsertNode *insert_node, uint32_t index, MetaColumn *meta_column, DBResult *result) {

    /* Get value item node at index. */
    ValueItemNode* value_item_node = insert_node->value_item_set_node->value_item_node[index];

    /* Different data type column, has diffrenet way to get value.
     * Data type CHAR, STRING, DATE, TIMESTAMP both use '%s' format to pass value.
     * And int value may be also FLOAT or DOUBLE. Column meta info helps to define the real data type. */
    switch(meta_column->column_type) {
        case T_CHAR:
        case T_STRING:
            return copy_value(value_item_node->s_value, meta_column->column_type);
        case T_INT:
        case T_LONG:
            return copy_value(&value_item_node->i_value, meta_column->column_type);
        case T_BOOL:
            return copy_value(&value_item_node->b_value, meta_column->column_type);
        case T_DOUBLE: {
            switch(value_item_node->data_type) {
                case T_INT:
                    value_item_node->d_value = (double)value_item_node->i_value;
                case T_FLOAT:
                    value_item_node->d_value = (double)value_item_node->f_value;
                case T_DOUBLE:
                    value_item_node->data_type = T_DOUBLE;
                    return copy_value(&value_item_node->d_value, meta_column->column_type);
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_FLOAT: {
            switch(value_item_node->data_type) {
                case T_INT:
                    value_item_node->f_value = (float) value_item_node->i_value;
                case T_FLOAT:
                    value_item_node->data_type = T_FLOAT;
                    return copy_value(&value_item_node->f_value, meta_column->column_type);
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_DATE: {
            switch(value_item_node->data_type) {
                case T_STRING: {
                    struct tm *tmp_time = db_malloc(sizeof(struct tm), SDT_TIME_T);
                    strptime(value_item_node->s_value, "%Y-%m-%d", tmp_time);
                    tmp_time->tm_sec = 0;
                    tmp_time->tm_min = 0;
                    tmp_time->tm_hour = 0;
                    value_item_node->data_type = T_DATE;
                    value_item_node->t_value = mktime(tmp_time);
                    db_free(tmp_time);
                }
                case T_DATE:
                    return copy_value(&value_item_node->t_value, meta_column->column_type);
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_TIMESTAMP: {
            switch(value_item_node->data_type) {
                case T_STRING: {
                    struct tm *tmp_time = db_malloc(sizeof(struct tm), SDT_TIME_T);
                    strptime(value_item_node->s_value, "%Y-%m-%d %H:%M:%S", tmp_time);
                    value_item_node->data_type = T_TIMESTAMP;
                    value_item_node->t_value = mktime(tmp_time);
                    db_free(tmp_time);
                }
                case T_TIMESTAMP:
                    return copy_value(&value_item_node->t_value, meta_column->column_type);
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_REFERENCE: {
            switch (value_item_node->r_value->type) {
                case DIRECTLY: {
                    InsertNode *insert_node = fake_insert_node(meta_column->table_name, value_item_node->r_value->nest_value_item_set);
                    Refer *refer = exec_insert_statement(insert_node, result);
                    free_insert_node(insert_node);
                    return refer;
                }
                case INDIRECTLY: {
                    return fetch_refer(meta_column, value_item_node->r_value->condition);
                }
            }
            break;
        }
    }
}

/* Make a fake InsertNode. */
static InsertNode *fake_insert_node(char *table_name, ValueItemSetNode *value_item_set_node) {
    InsertNode *insert_node = db_malloc(sizeof(InsertNode), SDT_INSERT_NODE);
    insert_node->table_name = db_strdup(table_name);
    insert_node->all_column = true;
    insert_node->value_item_set_node = copy_value_item_set_node(value_item_set_node);
    return insert_node;
}

/* Generate insert row. */
static Row *generate_insert_row(InsertNode *insert_node, DBResult *result) {

    Row *row = db_malloc(sizeof(Row), SDT_ROW);

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
    row->data = db_malloc(sizeof(KeyValue *) * row->column_len, SDT_POINTER);
    
    /* Row data. */
    uint32_t i;
    for(i = 0; i < row->column_len; i++) {

        MetaColumn *meta_column = meta_table->meta_column[i];

        /* Ship system reserved. */
        if (meta_column->sys_reserved) 
            continue;

        KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value->key = db_strdup(meta_column->column_name);
        key_value->data_type = meta_column->column_type;

        if (insert_node->all_column)
            key_value->value = get_column_value(insert_node, i, meta_column, result);
        else {
            int index = get_column_index(insert_node, key_value->key);          
            key_value->value = get_column_value(insert_node, index, meta_column, result);
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

/* Execute insert statement. 
 * If successfully, return the Refer which maybe used by other table.
 * If fail, return NULL. */
Refer *exec_insert_statement(InsertNode *insert_node, DBResult *result) {
    
    /* Check if table exists. */
    Table *table = open_table(insert_node->table_name);
    if (table == NULL) {
        db_log(ERROR, "Try to open table '%s' fail.", insert_node->table_name);
        return NULL;
    }

    /* Check if insert node valid. */
    if (!check_insert_node(insert_node)) 
        return NULL;

    Row *row = generate_insert_row(insert_node, result);
    if (row == NULL) 
        return NULL;

    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(table->meta_table);
    Cursor *cursor = define_cursor(table, row->key);
    if (check_duplicate_key(cursor, row->key) && !cursor_is_deleted(cursor)) {
        db_log(ERROR, "key '%s' in table '%s' already exists, not allow duplicate key.", 
               get_key_str(row->key, primary_key_meta_column->column_type), insert_node->table_name);

        /* Free unuesed memeory */
        free_cursor(cursor);
        free_row(row);

        return NULL;
    }

    /* Update row transaction state for insert. */
    update_transaction_state(row, TR_INSERT);

    /* Insert into leaf node. */
    insert_leaf_node_cell(cursor, row);

    /* Convert to Refer. */
    Refer *refer = convert_refer(cursor);

    /* Free useless memeory */
    free_cursor(cursor);
    free_row(row);

    return refer;    
}

