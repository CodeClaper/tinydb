#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _XOPEN_SOURCE
#define __USE_XOPEN
#include <time.h>
#include "meta.h"
#include "mmu.h"
#include "log.h"
#include "refer.h"
#include "utils.h"
#include "common.h"
#include "ltree.h"
#include "list.h"
#include "asserts.h"
#include "pager.h"

#define DEFAULT_BOOL_LENGTH         2
#define DEFAULT_STRING_LENGTH       48
#define DEFAULT_DATE_LENGTH         20
#define DEFAULT_TIMESTAMP_LENGTH    20
#define DEFAULT_REFERENCE_LENGTH    48


/* Column type length */
uint32_t default_data_len(DataType column_type) {
    switch (column_type) {
        case T_BOOL:
            return DEFAULT_BOOL_LENGTH;
        case T_CHAR:
            return sizeof(char);
        case T_VARCHAR:
            return DEFAULT_STRING_LENGTH;
        case T_INT:
            return sizeof(int32_t);
        case T_LONG:
            return sizeof(int64_t);
        case T_DOUBLE:
            return sizeof(double);
        case T_FLOAT:
            return sizeof(float);
        case T_STRING:
            return DEFAULT_STRING_LENGTH;
        case T_DATE:
            return DEFAULT_DATE_LENGTH;
        case T_TIMESTAMP:
            return DEFAULT_TIMESTAMP_LENGTH;
        case T_REFERENCE:
            return DEFAULT_REFERENCE_LENGTH;
        default:
            db_log(PANIC, "Unknown column type");
  }
}

/* Get value from value item node. */
void *get_value_from_value_item_node(ValueItemNode *value_item_node, MetaColumn *meta_column) {
    /* For array, return value set. */
    if (value_item_node->is_array)
        return value_item_node->value_set;

    /* User can use '%s' fromat in sql to pass multiple types value including char, string, date, timestamp. 
     * So we must use meta column data type to define which data type of the value. */
    switch (meta_column->column_type) {
        case T_CHAR: {
            switch (value_item_node->data_type) {
                case T_STRING:
                case T_VARCHAR:
                    value_item_node->data_type = T_CHAR;
                    return value_item_node->value.strVal;
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_STRING:
        case T_VARCHAR:
            return value_item_node->value.strVal;
        case T_INT:
        case T_LONG:
            return &value_item_node->value.intVal;
        case T_BOOL:
            return &value_item_node->value.boolVal;
        case T_FLOAT: {
            switch (value_item_node->data_type) {
                case T_INT:
                    value_item_node->value.floatVal = value_item_node->value.intVal;
                    value_item_node->data_type = T_FLOAT;
                case T_FLOAT:
                    return &value_item_node->value.floatVal;
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_DOUBLE: {
            switch (value_item_node->data_type) {
                case T_INT:
                    value_item_node->value.doubleVal = value_item_node->value.intVal;
                    value_item_node->data_type = T_DOUBLE;
                case T_FLOAT:
                    value_item_node->value.doubleVal = value_item_node->value.floatVal;
                    value_item_node->data_type = T_DOUBLE;
                case T_DOUBLE:
                    return &value_item_node->value.doubleVal;
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_TIMESTAMP: {
            switch (value_item_node->data_type) {
                case T_STRING: 
                case T_VARCHAR: {
                    struct tm *tmp_time = instance(struct tm);
                    strptime(value_item_node->value.strVal, "%Y-%m-%d %H:%M:%S", tmp_time);
                    value_item_node->value.timeVal = mktime(tmp_time);
                    value_item_node->data_type = T_TIMESTAMP;
                    db_free(tmp_time);
                }
                case T_TIMESTAMP:
                    return &value_item_node->value.timeVal;
                default:
                    db_log(PANIC, "Data type error.");
            }
            break;
        }
        case T_DATE: {
            switch (value_item_node->data_type) {
                case T_STRING: 
                case T_VARCHAR: {
                    struct tm *tmp_time = instance(struct tm);
                    strptime(value_item_node->value.strVal, "%Y-%m-%d", tmp_time);
                    tmp_time->tm_sec = 0;
                    tmp_time->tm_min = 0;
                    tmp_time->tm_hour = 0;
                    value_item_node->value.timeVal = mktime(tmp_time);
                    value_item_node->data_type = T_DATE;
                    db_free(tmp_time);
                }
                case T_DATE:
                    return &value_item_node->value.timeVal;
                default:
                    db_log(PANIC, "Data type error.");
             }
             break;
        }
        case T_REFERENCE: {
            switch (value_item_node->value.refVal->type) {
                case DIRECTLY:
                    db_log(WARN, "Not support directly fetch refer when query.");
                    return make_null_refer();
                case INDIRECTLY: 
                    return fetch_refer(meta_column, value_item_node->value.refVal->condition);
            }
            break;
        }
        default:
            db_log(PANIC, "Not implement yet.");
    }
    return NULL;
}


/* Calculate the length of table row. */
uint32_t calc_table_row_length(Table *table) {
    uint32_t row_len = 0;
    uint32_t i;
    for (i = 0; i < table->meta_table->all_column_size; i++) {
        MetaColumn *meta_col = (table->meta_table->meta_column[i]);
        row_len+= meta_col->column_length;
    }
    return row_len;
}

/* Calculate primary key lenght. 
 * Return primary-key column length.
 * Panic if not found. */
uint32_t calc_primary_key_length(Table *table) {
    uint32_t i;
    for (i = 0; i < table->meta_table->all_column_size; i++) {
       MetaColumn *meta_column = table->meta_table->meta_column[i];
       if (meta_column->is_primary)
           return meta_column->column_length;
    }
    panic("Not found primary key.");
    return -1;
}

/* Get index column meta info */
MetaColumn *get_meta_column_by_index(void *root_node, uint32_t index) {
    void *destination = get_meta_column_pointer(root_node, index);
    return deserialize_meta_column(destination);
}

/* Get meta column info by column name. */
MetaColumn *get_meta_column_by_name(MetaTable *meta_table, char *name) {
    uint32_t i;
    for (i = 0; i < meta_table->column_size; i++) {
      MetaColumn *meta_column = meta_table->meta_column[i];
      if (streq(meta_column->column_name, name))
        return meta_column;
    }
    return NULL;
}


/* Get all meta column info by column name including system reserved column. 
 * Return NULL if not found.
 * */
MetaColumn *get_all_meta_column_by_name(MetaTable *meta_table, char *name) {
    uint32_t i;
    for (i = 0; i < meta_table->all_column_size; i++) {
      MetaColumn *meta_column = meta_table->meta_column[i];
      if (strcmp(meta_column->column_name, name) == 0)
        return meta_column;
    }
    return NULL;
}

/* Get table meta info. */
MetaTable *get_meta_table(Table *table, char *table_name) {
    /* Check valid. */
    assert_not_null(table_name, "Input table name can`t be null.");

    MetaTable *meta_table = instance(MetaTable);
    void *root_node = get_page(table_name, table->pager, table->root_page_num);
    uint32_t column_size = get_column_size(root_node);

    meta_table->table_name = db_strdup(table_name);
    meta_table->column_size = 0;
    meta_table->all_column_size = 0;
    meta_table->meta_column = db_malloc(sizeof(MetaColumn *) * column_size, "pointer");

    uint32_t i;
    for (i = 0; i < column_size; i++) {
        MetaColumn *current = get_meta_column_by_index(root_node, i);
        meta_table->meta_column[i] = current;

        /* Skip to system reserved column. */
        if (!current->sys_reserved)
            meta_table->column_size++;

        meta_table->all_column_size++;
    }

    assert_true(meta_table->all_column_size == column_size, "System Logic Error in <get_meta_table>");

    return meta_table;
}
