#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#define _XOPEN_SOURCE
#define __USE_XOPEN
#include <time.h>
#include "insert.h"
#include "mem.h"
#include "common.h"
#include "misc.h"
#include "table.h"
#include "meta.h"
#include "node.h"
#include "table.h"
#include "pager.h"
#include "index.h"
#include "check.h"
#include "free.h"
#include "log.h"
#include "send.h"


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

//Get column value.
static void *get_column_value(InsertNode *insert_node, uint32_t index, MetaColumn *meta_column) {
    ValueItemNode* value_item_node = *(insert_node->value_item_set_node->value_item_node + index);
    switch(meta_column->column_type) {
        case T_CHAR:
        case T_STRING:
            return strdup((char *)value_item_node->s_value);
        case T_INT:
            return &(value_item_node->i_value);
        case T_BOOL:
            return &(value_item_node->b_value);
        case T_DOUBLE:
            {
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
            }
        case T_FLOAT: 
            {
                switch(value_item_node->data_type) {
                    case T_INT:
                        value_item_node->f_value = value_item_node->i_value;
                    case T_FLOAT:
                        value_item_node->data_type = T_FLOAT;
                        return &value_item_node->f_value;
                    default:
                        fatal("Data type error.");
                }
            }
        case T_DATE:
            {
                switch(value_item_node->data_type) {
                    case T_STRING:
                        {
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
            }
        case T_TIMESTAMP: 
            {
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
            }
    }
    return NULL;
}

//Generate insert row
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
            log_error_s("Inner error, not find meta column info by name '%s'", column_name);
            return NULL;
        }
        key_value->data_type = meta_column->column_type;
        key_value->value = get_column_value(insert_node, i, meta_column);
        if (meta_column->is_primary) {
            row->key = key_value->value;
        }
        *(row->data + i) = key_value;
    }
    return row;
}

//Execute insert statement.
ExecuteResult exec_insert_statement(InsertNode *insert_node) {
    if (!check_insert_node(insert_node))
        return EXECUTE_FAIL;
    Row *row = generate_insert_row(insert_node);
    if (row == NULL)
        return EXECUTE_FAIL;
    Table *table = open_table(row->table_name);
    if (table == NULL)
        return EXECUTE_FAIL;
    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(table->meta_table);
    void *root_node = get_page(table->pager, table->root_page_num); 
    Cursor *cursor = define_cursor(table, row->key);
    if (check_duplicate_key(cursor, row->key)) {
        log_error_s("key '%s' already exists, not allow duplicate key.", get_key_str(row->key, primary_key_meta_column->column_type));
        return EXECUTE_DUPLICATE_KEY;
    }
    insert_leaf_node(cursor, row);
    // free memeory
    free_cursor(cursor);
    free_row(row);
    db_send("Successfully insert one row data.");
    return EXECUTE_SUCCESS;    
}

