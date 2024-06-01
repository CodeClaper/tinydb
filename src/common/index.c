#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "index.h"
#include "mmu.h"
#include "pager.h"
#include "ltree.h"
#include "meta.h"
#include "compare.h"
#include "common.h"
#include "log.h"


/* Check if key already exists  */
 bool check_duplicate_key(Cursor *cursor, void *key) {
    void *node = get_page(cursor->table->meta_table->table_name, cursor->table->pager, cursor->page_num);
    uint32_t value_len = calc_table_row_length(cursor->table);
    uint32_t key_len = calc_primary_key_length(cursor->table);
    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(cursor->table->meta_table);
    void *target = get_leaf_node_cell_key(node, cursor->cell_num, key_len, value_len);
    return equal(target, key, primary_key_meta_column->column_type);
}


/* Get key string value. */
char *get_key_str(void *key, DataType data_type) {
    switch(data_type) {
        case T_BOOL: 
            return *(bool *)key ? "true" : "false";
        case T_CHAR:
        case T_STRING:
        case T_VARCHAR:
            return (char *)key;
        case T_INT: {
            char *str = db_malloc(50, "string");
            sprintf(str, "%d", *(int32_t *)key);
            return str;
        }
        case T_LONG: {
            char *str = db_malloc(100, "string");
            sprintf(str, "%ld", *(int64_t *)key);
            return str;
        }
        case T_DOUBLE: {
            char *str = db_malloc(50, "string");
            sprintf(str, "%lf", *(double *)key);
            return str;
        }
        case T_FLOAT: {
            char *str = db_malloc(50, "string");
            sprintf(str, "%f", *(float *)key);
            return str;
        }
        case T_DATE: {
            char *str = db_malloc(30, "string");
            struct tm *tmp_time = localtime(key);
            strftime(str, strlen(str), "%Y-%m-%d", tmp_time);
            return str;
        }
        case T_TIMESTAMP: {
            char *str = db_malloc(40, "string");
            struct tm *tmp_time = localtime(key);
            strftime(str, strlen(str), "%Y-%m-%d %H:%M:%S", tmp_time);
            return str;
        } default: {
            db_log(ERROR, "Not allowed data type as primary key.");
            return NULL;
        }
    }
}
