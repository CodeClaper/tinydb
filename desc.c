#include "desc.h"
#include "table.h"
#include "meta.h"
#include "output.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Get table name.
static char *get_table_name(DescribeNode *describe_node) {
    return describe_node->table_name;
}

// print into describe node.
ExecuteResult print_describe_info(DescribeNode *describe_node, Output *out) {
    uint32_t i;
    char *table_name = get_table_name(describe_node); 
    Table *table = open_table(table_name);
    if (table == NULL) 
        return EXECUTE_TABLE_OPEN_FAIL;
    MetaTable *meta_table = table->meta_table;
    print_data(out, strdup("["));
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        print_data(out, strdup("{"));
        print_data(out, get_key_value_pair_str("field", meta_column->column_name, T_STRING));
        print_data(out, strdup(", "));
        print_data(out, get_key_value_pair_str("type", data_type_name(meta_column->column_type), T_STRING));
        print_data(out, strdup(", "));
        print_data(out, get_key_value_pair_str("primary key", &meta_column->is_primary, T_BOOL));
        print_data(out, strdup(", "));
        print_data(out, get_key_value_pair_str("size", &meta_column->column_length, T_INT));
        print_data(out, strdup("}"));
        if (i < meta_table->column_size - 1)
            print_data(out, strdup(", "));
    }
    print_data(out, strdup("]"));
    return EXECUTE_SUCCESS;
}
