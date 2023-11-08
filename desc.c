#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "desc.h"
#include "mem.h"
#include "misc.h"
#include "table.h"
#include "meta.h"
#include "send.h"



//Get table name.
static char *get_table_name(DescribeNode *describe_node) {
    return describe_node->table_name;
}

/*Execute describe statment.*/
ExecuteResult exec_describe_statement(DescribeNode *describe_node) {
    uint32_t i;
    char *table_name = get_table_name(describe_node); 
    Table *table = open_table(table_name);
    if (table == NULL) 
        return EXECUTE_TABLE_OPEN_FAIL;
    MetaTable *meta_table = table->meta_table;
    db_send("[");
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        db_send("{");
        db_send(get_key_value_pair_str("field", meta_column->column_name, T_STRING));
        db_send(", ");
        db_send(get_key_value_pair_str("type", data_type_name(meta_column->column_type), T_STRING));
        db_send(", ");
        db_send(get_key_value_pair_str("primary key", &meta_column->is_primary, T_BOOL));
        db_send(", ");
        db_send(get_key_value_pair_str("size", &meta_column->column_length, T_INT));
        db_send("}");
        if (i < meta_table->column_size - 1)
            db_send(", ");
    }
    db_send("]\n");
    return EXECUTE_SUCCESS;
}
