#include "desc.h"
#include "table.h"
#include "meta.h"
#include <stdint.h>
#include <stdio.h>

static char *get_table_name(DescribeNode *describe_node) {
    return describe_node->from_item_node->table->name;
}

// print into describe node.
ExecuteResult print_describe_info(DescribeNode *describe_node) {
    uint32_t i;
    char *table_name = get_table_name(describe_node); 
    Table *table = open_table(table_name);
    if (table == NULL)
        return EXECUTE_TABLE_OPEN_FAIL;
    MetaTable *meta_table = table->meta_table;
    fprintf(stdout, "[");
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        fprintf(stdout, "{");
        fprintf(stdout, "\"field\": %s, ", meta_column->column_name);
        fprintf(stdout, "\"type\": \"%s\", ", data_type_name(meta_column->column_type));
        fprintf(stdout, "\"key\": %d, ", meta_column->is_primary);
        fprintf(stdout, "\"size\": %d", meta_column->column_length);
        fprintf(stdout, "} ");
    }
    fprintf(stdout, "]\n");
    return EXECUTE_SUCCESS;
}
