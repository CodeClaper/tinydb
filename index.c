#include "index.h"
#include "pager.h"
#include "node.h"
#include "meta.h"
#include "opr.h"
#include "common.h"
#include "misc.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Check if key already exists in db
 bool check_duplicate_key(Cursor *cursor, void *key) {
    void *node = get_page(cursor->table->pager, cursor->page_num);
    uint32_t value_len = calc_table_row_length(cursor->table);
    uint32_t key_len = calc_primary_key_length(cursor->table);
    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(cursor->table->meta_table);
    void *target = get_leaf_node_cell_key(node, cursor->cell_num, key_len, value_len);
    return equal(target, key, primary_key_meta_column->column_type);
}

//Get meta column of primary key.
MetaColumn *get_primary_key_meta_column(MetaTable *meta_table) {
    for(uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (meta_column->is_primary)
            return meta_column;
    }
    return NULL; //may be return system built-in primary key, but now, return null temporiarily.
}

//Get key string value.
char *get_key_str(void *key, DataType data_type) {
    switch(data_type) {
        case T_BOOL: 
            {
                return *(bool *)key ? "true" : "false";
            }
        case T_CHAR:
        case T_STRING:
            {
                return (char *)key;
            }
        case T_INT:
            {
                char *str = malloc(100);
                memset(str, 0, 100);
                sprintf(str, "%d", *(uint32_t *)key);
                return str;
            }
        case T_DOUBLE:
            {
                char *str = malloc(100);
                memset(str, 0, 100);
                sprintf(str, "%lf", *(double *)key);
                return str;
            }
        case T_FLOAT:
            {
                char *str = malloc(100);
                memset(str, 0, 100);
                sprintf(str, "%f", *(float *)key);
                return str;
            }
        case T_DATE:
        case T_TIMESTAMP:
            fatal("Not supported data type");
    }
    return NULL;
}
