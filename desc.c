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
    return describe_node->from_item_node->table->name;
}

// print into describe node.
ExecuteResult print_describe_info(DescribeNode *describe_node, Output *out) {
    uint32_t i;
    uint32_t buffer_size;
    char *table_name = get_table_name(describe_node); 
    Table *table = open_table(table_name);
    buffer_size = BUFF_SIZE;
    if (table == NULL)
        return EXECUTE_TABLE_OPEN_FAIL;
    MetaTable *meta_table = table->meta_table;
    print_out(out, "[", &buffer_size);
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        print_out(out, "{", &buffer_size);
        print_out(out, get_key_value_pair_str("field", meta_column->column_name, T_STRING), &buffer_size);
        print_out(out, get_key_value_pair_str("type", data_type_name(meta_column->column_type), T_STRING), &buffer_size);
        print_out(out, get_key_value_pair_str("key", &meta_column->is_primary, T_BOOL), &buffer_size);
        print_out(out, get_key_value_pair_str("size", &meta_column->column_name, T_INT), &buffer_size);
        print_out(out, "} ", &buffer_size);
    }
    fprintf(stdout, "]\n");
}
