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
#include "misc.h"
#include "table.h"
#include "meta.h"
#include "node.h"
#include "table.h"
#include "pager.h"
#include "index.h"
#include "asserts.h"
#include "session.h"
#include "check.h"
#include "free.h"
#include "lock.h"
#include "refer.h"
#include "log.h"


//Get table name in select node.
static char *get_table_name(InsertNode *insert_node) {
    return insert_node->table_name;
}

//Get column number of insert statement.
static uint32_t get_insert_column_size(InsertNode *insert_node, MetaTable *meta_table) {
    if (insert_node->all_column)
        return meta_table->column_size;
    else 
        return insert_node->columns_set_node->size;
}

//Get value number
static uint32_t get_value_size(InsertNode *insert_node) {
    return insert_node->value_item_set_node->num;
}

//Get column name.
static char *get_column_name(InsertNode *insert_node, uint32_t index, MetaTable *meta_table) {
    if (insert_node->all_column)
        return meta_table->meta_column[index]->column_name;
    else 
        return ((ColumnNode *)(insert_node->columns_set_node->columns + index))->column_name;
}

/* Get value in insert node to assign column at index. */
static void *get_column_value(InsertNode *insert_node, uint32_t index, MetaColumn *meta_column) {

    /* Get value item node at index. */
    ValueItemNode* value_item_node = *(insert_node->value_item_set_node->value_item_node + index);

    /* Different data type column, has diffrenet way to get value.
     * Data type CHAR, STRING, DATE, TIMESTAMP both use '%s' format to pass value.
     * And int value may be also FLOAT or DOUBLE. Column meta info helps to define the real data type.
     * */
    switch(meta_column->column_type) {
        case T_CHAR:
        case T_STRING:
            return strdup((char *)value_item_node->s_value);
        case T_INT:
            return &(value_item_node->i_value);
        case T_BOOL:
            return &(value_item_node->b_value);
        case T_DOUBLE: {
            switch(value_item_node->data_type) {
                case T_INT:
                    value_item_node->d_value = value_item_node->i_value;
                case T_FLOAT:
                    value_item_node->d_value = value_item_node->f_value;
                case T_DOUBLE:
                    value_item_node->data_type = T_DOUBLE;
                    return &value_item_node->d_value;
                default:
                    fatal("Data type error.");
            }
            break;
        }
        case T_FLOAT: {
            switch(value_item_node->data_type) {
                case T_INT:
                    value_item_node->f_value = value_item_node->i_value;
                case T_FLOAT:
                    value_item_node->data_type = T_FLOAT;
                    return &value_item_node->f_value;
                default:
                    fatal("Data type error.");
            }
            break;
        }
        case T_DATE: {
            switch(value_item_node->data_type) {
                case T_STRING: {
                    struct tm *tmp_time = db_malloc(sizeof(struct tm));
                    strptime(value_item_node->s_value, "%Y-%m-%d", tmp_time);
                    tmp_time->tm_sec = 0;
                    tmp_time->tm_min = 0;
                    tmp_time->tm_hour = 0;
                    value_item_node->data_type = T_DATE;
                    value_item_node->t_value = mktime(tmp_time);
                    db_free(tmp_time);
                }
                case T_DATE:
                    return &value_item_node->t_value;
                default:
                    fatal("Data type error.");
            }
            break;
        }
        case T_TIMESTAMP: {
            switch(value_item_node->data_type) {
                case T_STRING:
                    {
                        struct tm *tmp_time = db_malloc(sizeof(struct tm));
                        strptime(value_item_node->s_value, "%Y-%m-%d %H:%M:%S", tmp_time);
                        value_item_node->data_type = T_TIMESTAMP;
                        value_item_node->t_value = mktime(tmp_time);
                        db_free(tmp_time);
                    }
                case T_TIMESTAMP:
                    return &value_item_node->t_value;
                default:
                    fatal("Data type error.");
            }
            break;
        }
        case T_REFERENCE: {
            InsertNode *nest_insert_node = db_malloc2(sizeof(InsertNode), "InsertNode");
            nest_insert_node->table_name = strdup(meta_column->table_name);
            nest_insert_node->all_column = true;
            nest_insert_node->value_item_set_node = value_item_node->nest_value_item_set;
            InsertExecuteResult *result = exec_insert_statement(nest_insert_node);
            return result->status == EXECUTE_SUCCESS ? result->refer : NULL;
        }
    }
    return NULL;
}

/* Generate insert row. */
static Row *generate_insert_row(InsertNode *insert_node) {
    uint32_t i, column_len;
    Row *row = db_malloc(sizeof(Row));
    row->table_name = strdup(get_table_name(insert_node));
    Table *table = open_table(row->table_name);
    if (table == NULL) 
        return NULL;
    MetaTable *meta_table = table->meta_table;
    column_len = get_insert_column_size(insert_node, meta_table);
    row->data = db_malloc(sizeof(KeyValue *) * column_len);
    row->column_len = column_len;
    for(i = 0; i < column_len; i++) {
        KeyValue *key_value = db_malloc(sizeof(KeyValue));
        char *column_name = get_column_name(insert_node, i, meta_table);
        key_value->key = strdup(column_name);
        MetaColumn *meta_column = get_meta_column_by_name(meta_table, column_name);
        if (meta_column == NULL) {
            db_error("Inner error, try to get meta column info by name '%s' fail.\n", column_name);
            return NULL;
        }
        key_value->data_type = meta_column->column_type;
        key_value->value = get_column_value(insert_node, i, meta_column);
        if (key_value->value == NULL)
            return NULL;
        if (meta_column->is_primary) {
            row->key = key_value->value;
        }
        *(row->data + i) = key_value;
    }
    return row;
}

static InsertExecuteResult *new_insert_execute_result() {
    InsertExecuteResult *result = db_malloc2(sizeof(InsertExecuteResult), "InsertExecuteResult");
    result->status = EXECUTE_SUCCESS;
    result->refer = db_malloc2(sizeof(Refer), "Refer");
    return result;
}

/* Execute insert statement. */
InsertExecuteResult *exec_insert_statement(InsertNode *insert_node) {
    
    InsertExecuteResult *result = new_insert_execute_result();

    /* Check if insert node valid. */
    if (!check_insert_node(insert_node)) {
        result->status = EXECUTE_FAIL;
        return result;
    }

    Row *row = generate_insert_row(insert_node);
    if (row == NULL) {
        result->status = EXECUTE_FAIL;
        return result;
    }
    Table *table = open_table(row->table_name);
    if (table == NULL) {
        result->status = EXECUTE_TABLE_EXIST_FAIL;
        return result;
    }
    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(table->meta_table);
    void *root_node = get_page(table->pager, table->root_page_num); 
    Cursor *cursor = define_cursor(table, row->key);
    if (check_duplicate_key(cursor, row->key)) {
        db_error("key '%s' already exists, not allow duplicate key.\n", get_key_str(row->key, primary_key_meta_column->column_type));
        result->status = EXECUTE_DUPLICATE_KEY;
        return result;
    }

    /* Set row write lock. */
    LockState *lock_state = db_row_lock(convert_refer(cursor), WR_MODE);

    /* Insert into leaf node. */
    insert_leaf_node_cell(cursor, row);

    result->refer->cell_num = cursor->cell_num;
    result->refer->page_num = cursor->page_num;
    strcpy(result->refer->table_name, insert_node->table_name);

    /* Free unuesed memeory */
    free_cursor(cursor);
    free_row(row);

    sleep(20); // for debug
    
    /* Unlock */
    db_unlock(lock_state);

    db_send("Successfully insert one row data. \n");
    return result;    
}

