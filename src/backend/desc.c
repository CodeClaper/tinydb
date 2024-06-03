#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "desc.h"
#include "list.h"
#include "mmu.h"
#include "table.h"
#include "meta.h"
#include "copy.h"
#include "session.h"
#include "type.h"
#include "log.h"

/*Get table name.*/
static char *get_table_name(DescribeNode *describe_node) {
    return describe_node->table_name;
}

/* Calculate meta column length. Notice, T_STRING data has added on extra char. */
static uint32_t calc_meta_column_len(MetaColumn *meta_column) {
    switch (meta_column->column_type) {
        case T_STRING:
        case T_VARCHAR:
            return meta_column->column_length - 2;
        default:
            return meta_column->column_length - 1;
    }
}

/* Generate DescribeResult. */
static List *gen_describe_result(MetaTable *meta_table) {

    List *list = create_list(NODE_LIST);

    uint32_t i;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];

        List *child_list = create_list(NODE_KEY_VALUE);

        /* filed */
        append_list(child_list, new_key_value(db_strdup("field"), 
                                              db_strdup(meta_column->column_name), 
                                              T_STRING));

        /* type */
        append_list(child_list, new_key_value(db_strdup("data_type"), 
                                              db_strdup(data_type_name(meta_column->column_type)), 
                                              T_STRING));

        /* array dim */
        bool is_array = meta_column->array_dim > 0;
        append_list(child_list, new_key_value(db_strdup("is_array"), 
                                              copy_value(&is_array, T_BOOL), 
                                              T_BOOL));

        /* primary key */
        if (is_array) 
            append_list(child_list, new_key_value(db_strdup("is_primary_key"), 
                                                  copy_value(&meta_column->is_primary, T_BOOL), 
                                                  T_BOOL));

        /* length */
        uint32_t column_length = calc_meta_column_len(meta_column);
        append_list(child_list, new_key_value(db_strdup("data_length"), 
                                              copy_value(&column_length, T_INT), 
                                              T_INT));

        /* Default value. */
        switch (meta_column->default_value_type) {
            case DEFAULT_VALUE_NONE:
                break;
            case DEFAULT_VALUE_NULL:
                append_list(child_list, new_key_value(db_strdup("default_value"), 
                                                      copy_value(NULL, meta_column->column_type), 
                                                      meta_column->column_type));
                break;
            case DEFAULT_VALUE:
                append_list(child_list, new_key_value(db_strdup("default_value"), 
                                                      copy_value(meta_column->default_value, meta_column->column_type), 
                                                      meta_column->column_type));
                break;
                
        }

        append_list(list, child_list);
    }

    return list;
}

/* Execute describe statment. */
List *exec_describe_statement(DescribeNode *describe_node) {
    char *table_name = get_table_name(describe_node); 
    Table *table = open_table(table_name);
    if (table == NULL) {
        db_log(ERROR, "Table '%s' not exist.", table_name);
        return NULL;
    }

    return gen_describe_result(table->meta_table);
}
