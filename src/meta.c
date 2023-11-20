#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _XOPEN_SOURCE
#define __USE_XOPEN
#include <time.h>
#include "meta.h"
#include "mem.h"
#include "common.h"
#include "misc.h"
#include "node.h"
#include "pager.h"

static char *data_type_name_list[] = {"bool",  "char",   "int",  "double",
                                      "float", "string", "date", "timestamp"};

// get data type name.
char *data_type_name(DataType data_type) {
  return data_type_name_list[data_type];
}

// column type length
uint32_t column_type_length(DataType column_type) {
  switch (column_type) {
  case T_BOOL:
    return 2;
  case T_CHAR:
    return sizeof(char);
  case T_INT:
    return sizeof(uint32_t);
  case T_DOUBLE:
    return sizeof(double);
  case T_FLOAT:
    return sizeof(float);
  case T_STRING:
    return 48;
  case T_DATE:
    return 48;
  case T_TIMESTAMP:
    return 48;
  default:
    fatal("unknow column type");
  }
}

/*Get key value pair string.*/
char *get_key_value_pair_str(char *key, void *value, DataType data_type) {
    switch(data_type) {
        case T_BOOL:
            {
                uint32_t len = strlen(key) + 4 + 100; /*len = key len + symbol len + value len.*/
                char *s = db_malloc2(len, "BOOL String value");
                sprintf(s, "\"%s\": %s", key, (*(bool *)value ? "true" : "false"));
                return s;
            }
        case T_INT: 
            {
                uint32_t len = strlen(key) + 4 + 100; /*len = key len + symbol len + value len.*/
                char *s = db_malloc2(len, "Int String value");
                sprintf(s, "\"%s\": %d", key, *(uint32_t *)value);
                return s;
            }
        case T_CHAR:
            {
                uint32_t len = strlen(key) + 6 + 1; /*len = key len + symbol len + value len.*/ 
                char *s = db_malloc2(len, "Char String value");
                sprintf(s, "\"%s\": \'%c\'", key, *(char *)value);
                return s;
            }
        case T_STRING:
            {
                uint32_t len = strlen(key) + 6 + strlen(value); /*len = key len + symbol len + value len.*/
                char *s = db_malloc2(len, "String value");
                sprintf(s, "\"%s\": \"%s\"", key, (char *)value);
                return s;
            }
        case T_FLOAT: 
            {
                uint32_t len = strlen(key) + 4 + 100; /*len = key len + symbol len + value len.*/
                char *s = db_malloc2(len, "Float String value");
                sprintf(s, "\"%s\": %f", key, *(float *)value);
                return s;
            }
        case T_DOUBLE:
            {
                uint32_t len = strlen(key) + 4 + 100; /*len = key len + symbol len + value len.*/
                char *s = db_malloc2(len, "Double String value");
                sprintf(s, "\"%s\": %lf", key, *(double *)value);
                return s;
            }
        case T_TIMESTAMP: 
            {
                char temp[90];
                uint32_t len = strlen(key) + 4 + 100; /*len = key len + symbol len + value len.*/
                char *s = db_malloc2(len, "Timestamp String value.");
                time_t t = *(time_t *)value;
                struct tm *tmp_time = localtime(&t);
                strftime(temp, sizeof(temp), "%Y-%m-%d %H:%M:%S", tmp_time);
                sprintf(s, "\"%s\": \"%s\"", key, temp);
                return s;
            }
        case T_DATE: 
            {
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

// calculate the length of table row
uint32_t calc_table_row_length(Table *table) {
  uint32_t len = 0;
  for (int i = 0; i < table->meta_table->column_size; i++) {
    MetaColumn *meta_col = (table->meta_table->meta_column[i]);
    len += meta_col->column_length;
  }
  return len;
}

//calculate primary key lenght. if not exist primary key , return -1;
uint32_t calc_primary_key_length(Table *table) {
   for (int i = 0; i < table->meta_table->column_size; i++) {
     MetaColumn *meta_column = (table->meta_table->meta_column[i]);
     if (meta_column->is_primary)
         return meta_column->column_length;
   }
   fatal("Not found primary key.");
   return -1;
}

// get index column meta info
MetaColumn *get_meta_column_by_index(void *root_node, uint32_t index) {
  uint32_t column_size = get_column_size(root_node);
  if (index >= column_size) {
     fprintf(stderr, "Exceed the maxinum column size: [%d]", column_size);   
     exit(1);
  }
  void *destination = get_meta_column_pointer(root_node, index);
  return deserialize_meta_column(destination);
}

// get meta column info by column name.
MetaColumn *get_meta_column_by_name(MetaTable *meta_table, char *name) {
  for (uint32_t i = 0; i < meta_table->column_size; i++) {
    MetaColumn *meta_column = meta_table->meta_column[i];
    if (strcmp(meta_column->column_name, name) == 0)
      return meta_column;
  }
  return NULL;
}

// get table meta info
MetaTable *get_meta_table(Table *table, char *table_name) {
  if (table_name == NULL)
    fatal("Input table name can`t be null.");
  MetaTable *meta_table = db_malloc(sizeof(MetaTable));
  void *root_node = get_page(table->pager, table->root_page_num);
  uint32_t column_size = get_column_size(root_node);
  meta_table->table_name = strdup(table_name);
  meta_table->column_size = column_size;
  size_t meta_column_size = sizeof(MetaColumn);
  for (int i = 0; i < column_size; i++) {
    meta_table->meta_column[i] = db_malloc(meta_column_size);
    memcpy(meta_table->meta_column[i], get_meta_column_by_index(root_node, i),
           meta_column_size);
  }
  return meta_table;
}
