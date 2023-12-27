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
#include "common.h"
#include "misc.h"
#include "node.h"
#include "asserts.h"
#include "pager.h"

#define DEFAULT_STRING_LENGTH       48
#define DEFAULT_DATE_LENGTH         20
#define DEFAULT_TIMESTAMP_LENGTH    20
#define DEFAULT_REFERENCE_LENGTH    48


/* Data type name list. */
static char *data_type_name_list[] = {"bool",  "char",   "int",  "double", "float", "string", "date", "timestamp",  "reference"};

/* Get data type name. */
char *data_type_name(DataType data_type) {
  return data_type_name_list[data_type];
}

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
            fatal("Unknown column type");
  }
}

/* Get key value pair string. */
char *get_key_value_pair_str(char *key, void *value, DataType data_type) {
    switch(data_type) {
        case T_BOOL: {
            uint32_t len = strlen(key) + 4 + 100; /*len = key len + symbol len + value len.*/
            char *s = db_malloc2(len, "BOOL String value");
            sprintf(s, "\"%s\": %s", key, (*(bool *)value ? "true" : "false"));
            return s;
        }
        case T_INT: {
            uint32_t len = strlen(key) + 4 + 100; /*len = key len + symbol len + value len.*/
            char *s = db_malloc2(len, "Int String value");
            sprintf(s, "\"%s\": %d", key, *(int32_t *)value);
            return s;
        }
        case T_LONG: {
            uint32_t len = strlen(key) + 4 + 100; /*len = key len + symbol len + value len.*/
            char *s = db_malloc2(len, "Int String value");
            sprintf(s, "\"%s\": %" PRIu64, key, *(int64_t *)value);
            return s;
        }
        case T_CHAR: {
            uint32_t len = strlen(key) + 6 + 1; /*len = key len + symbol len + value len.*/ 
            char *s = db_malloc2(len, "Char String value");
            sprintf(s, "\"%s\": \'%c\'", key, *(char *)value);
            return s;
        }
        case T_STRING: {
            uint32_t len = strlen(key) + 6 + strlen(value); /*len = key len + symbol len + value len.*/
            char *s = db_malloc2(len, "String value");
            sprintf(s, "\"%s\": \"%s\"", key, (char *)value);
            return s;
        }
        case T_FLOAT: {
            uint32_t len = strlen(key) + 4 + 100; /*len = key len + symbol len + value len.*/
            char *s = db_malloc2(len, "Float String value");
            sprintf(s, "\"%s\": %f", key, *(float *)value);
            return s;
        }
        case T_DOUBLE: {
            uint32_t len = strlen(key) + 4 + 100; /*len = key len + symbol len + value len.*/
            char *s = db_malloc2(len, "Double String value");
            sprintf(s, "\"%s\": %lf", key, *(double *)value);
            return s;
        }
        case T_TIMESTAMP: {
            char temp[90];
            uint32_t len = strlen(key) + 4 + 100; /*len = key len + symbol len + value len.*/
            char *s = db_malloc2(len, "Timestamp String value.");
            time_t t = *(time_t *)value;
            struct tm *tmp_time = localtime(&t);
            strftime(temp, sizeof(temp), "%Y-%m-%d %H:%M:%S", tmp_time);
            sprintf(s, "\"%s\": \"%s\"", key, temp);
            return s;
        }
        case T_DATE: {
            char temp[90];
            uint32_t len = strlen(key) + 4 + 100; /*len =key len + symbol len + value len*/
            char *s = db_malloc2(len, "Date String value.");
            time_t t = *(time_t *)value;
            struct tm *tmp_time = localtime(&t);
            strftime(temp, sizeof(temp), "%Y-%m-%d", tmp_time);
            sprintf(s, "\"%s\": \"%s\"", key, temp);
            return s;
        }
        default:
            fatal("Not support data type");
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
     fatal("Not found primary key.");
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
      if (strcmp(meta_column->column_name, name) == 0)
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
    assert_not_null(table_name,"Input table name can`t be null.");
    MetaTable *meta_table = db_malloc2(sizeof(MetaTable), "MetaTable");
    void *root_node = get_page(table->pager, table->root_page_num);
    uint32_t column_size = get_column_size(root_node);
    meta_table->table_name = strdup(table_name);
    meta_table->column_size = 0;
    meta_table->all_column_size = 0;
    for (int i = 0; i < column_size; i++) {
        MetaColumn *current = get_meta_column_by_index(root_node, i);
        meta_table->meta_column[i] = db_malloc2(sizeof(MetaColumn), "MetaColumn");
        memcpy(meta_table->meta_column[i], current , sizeof(MetaColumn));

        /* Skip to system reserved column. */
        if (!current->sys_reserved)
            meta_table->column_size++;

        meta_table->all_column_size++;
    }
    return meta_table;
}
