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
#include "utils.h"
#include "common.h"
#include "ltree.h"
#include "asserts.h"
#include "pager.h"

#define DEFAULT_STRING_LENGTH       48
#define DEFAULT_DATE_LENGTH         20
#define DEFAULT_TIMESTAMP_LENGTH    20
#define DEFAULT_REFERENCE_LENGTH    48

#define SYMBOL_LENGTH 11
#define MAX_BOOL_STR_LENGTH 10
#define MAX_INT_STR_LENGTH 20
#define MAX_LONG_STR_LENGTH 30
#define MAX_FLOAT_STR_LENGTH 50
#define MAX_DOUBLE_STR_LENGTH 100
#define MAX_DATE_STR_LENGTH 30
#define MAX_TIMESTAMP_STR_LENGTH 30


/* Column type length */
uint32_t default_data_len(DataType column_type) {
    switch (column_type) {
        case T_BOOL:
            return 2;
        case T_CHAR:
            return sizeof(char);
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

/* Get key value pair string. */
char *get_key_value_pair_str(char *key, void *value, DataType data_type) {
    switch(data_type) {
        case T_BOOL: {
            uint32_t len = strlen(key) + MAX_BOOL_STR_LENGTH; /*len = key len + symbol len + value len.*/
            char *s = db_malloc(len, "string");
            sprintf(s, "\"%s\": %s", key, value && (*(bool *)value) ? "true" : "false");
            return s;
        }
        case T_INT: {
            uint32_t len = strlen(key) + MAX_INT_STR_LENGTH; /*len = key len + symbol len + value len.*/
            char *s = db_malloc(len, "string");
            sprintf(s, "\"%s\": %d", key, value ? *(int32_t *)value : 0);
            return s;
        }
        case T_LONG: {
            uint32_t len = strlen(key) + MAX_LONG_STR_LENGTH; /*len = key len + symbol len + value len.*/
            char *s = db_malloc(len, "string");
            sprintf(s, "\"%s\": %" PRIu64, key, value ? *(int64_t *)value : 0);
            return s;
        }
        case T_CHAR: {
            uint32_t len = strlen(key) + SYMBOL_LENGTH; /*len = key len + symbol len + value len.*/ 
            char *s = db_malloc(len, "string");
            sprintf(s, "\"%s\": \"%s\"", key, value ? (char *)value: "null");
            return s;
        }
        case T_STRING: {
            if (value) {
                uint32_t len = strlen(key) + SYMBOL_LENGTH + strlen(value); /*len = key len + symbol len + value len.*/
                char *s = db_malloc(len, "string");
                sprintf(s, "\"%s\": \"%s\"", key, (char *)value);
                return s;
            } else {
                uint32_t len = strlen(key) + SYMBOL_LENGTH ; /*len = key len + symbol len + value len.*/
                char *s = db_malloc(len, "string");
                sprintf(s, "\"%s\": \"%s\"", key, "null");
                return s;
            }
        }
        case T_FLOAT: {
            uint32_t len = strlen(key) + MAX_FLOAT_STR_LENGTH; /*len = key len + symbol len + value len.*/
            char *s = db_malloc(len, "string");
            sprintf(s, "\"%s\": %f", key, value ? *(float *)value : 0);
            return s;
        }
        case T_DOUBLE: {
            uint32_t len = strlen(key) + MAX_DOUBLE_STR_LENGTH; /*len = key len + symbol len + value len.*/
            char *s = db_malloc(len, "string");
            sprintf(s, "\"%s\": %lf", key, value ? *(double *)value : 0);
            return s;
        }
        case T_TIMESTAMP: {
            char temp[90];
            uint32_t len = strlen(key) + MAX_TIMESTAMP_STR_LENGTH; /*len = key len + symbol len + value len.*/
            char *s = db_malloc(len, "string");
            if (value) {
                time_t t = *(time_t *)value;
                struct tm *tmp_time = localtime(&t);
                strftime(temp, sizeof(temp), "%Y-%m-%d %H:%M:%S", tmp_time);
                sprintf(s, "\"%s\": \"%s\"", key, temp);
            } else {
                sprintf(s, "\"%s\": \"%s\"", key, "null");
            }
            return s;
        }
        case T_DATE: {
            char temp[90];
            uint32_t len = strlen(key) + MAX_TIMESTAMP_STR_LENGTH; /*len =key len + symbol len + value len*/
            char *s = db_malloc(len, "string");
            if (value) {
                time_t t = *(time_t *)value;
                struct tm *tmp_time = localtime(&t);
                strftime(temp, sizeof(temp), "%Y-%m-%d", tmp_time);
                sprintf(s, "\"%s\": \"%s\"", key, temp);
            } else {
                sprintf(s, "\"%s\": \"%s\"", key, "null");
            }
            return s;
        }
        default:
            db_log(PANIC, "Not support data type at <get_key_value_pair_str>");
    }
    return NULL;
}

/* Calculate the length of table row. */
uint32_t calc_table_row_length(Table *table) {
    uint32_t len = 0;
    for (int i = 0; i < table->meta_table->all_column_size; i++) {
      MetaColumn *meta_col = (table->meta_table->meta_column[i]);
      len += meta_col->column_length;
    }
    return len;
}

/* Calculate primary key lenght. if not exist primary key , return -1; */
uint32_t calc_primary_key_length(Table *table) {
    for (int i = 0; i < table->meta_table->column_size; i++) {
       MetaColumn *meta_column = (table->meta_table->meta_column[i]);
       if (meta_column->is_primary)
           return meta_column->column_length;
     }
     db_log(PANIC, "Not found primary key.");
     return -1;
}

/* Get index column meta info */
MetaColumn *get_meta_column_by_index(void *root_node, uint32_t index) {
    uint32_t column_size = get_column_size(root_node);
    if (index >= column_size) {
       fprintf(stderr, "Exceed the maxinum column size: [%d]", column_size);   
       exit(1);
    }
    void *destination = get_meta_column_pointer(root_node, index);
    return deserialize_meta_column(destination);
}

/* Get meta column info by column name. */
MetaColumn *get_meta_column_by_name(MetaTable *meta_table, char *name) {
    for (uint32_t i = 0; i < meta_table->column_size; i++) {
      MetaColumn *meta_column = meta_table->meta_column[i];
      if (streq(meta_column->column_name, name))
        return meta_column;
    }
    return NULL;
}


/* Get all meta column info by column name including system reserved column. */
MetaColumn *get_all_meta_column_by_name(MetaTable *meta_table, char *name) {
    for (uint32_t i = 0; i < meta_table->all_column_size; i++) {
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

    for (int i = 0; i < column_size; i++) {
        MetaColumn *current = get_meta_column_by_index(root_node, i);
        meta_table->meta_column[i] = instance(MetaColumn);
        memcpy(meta_table->meta_column[i], current, sizeof(MetaColumn));

        /* Skip to system reserved column. */
        if (!current->sys_reserved)
            meta_table->column_size++;

        meta_table->all_column_size++;
    }

    assert_true(meta_table->all_column_size == column_size, "System Logic Error in <get_meta_table>");

    return meta_table;
}
