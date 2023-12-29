#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "desc.h"
#include "mmu.h"
#include "misc.h"
#include "table.h"
#include "meta.h"
#include "session.h"
#include "ret.h"

/*Get table name.*/
static char *get_table_name(DescribeNode *describe_node) {
    return describe_node->table_name;
}

/* Execute describe statment. */
void exec_describe_statement(DescribeNode *describe_node, DBResult *result) {
    uint32_t i;
    char *table_name = get_table_name(describe_node); 
    Table *table = open_table(table_name);
    if (table == NULL) {
        error_result(result, EXECUTE_TABLE_OPEN_FAIL, "Try to open table '%s' fail.", table_name);
        return;
    }
    MetaTable *meta_table = table->meta_table;
    db_send("[");
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        db_send("{");
        db_send(get_key_value_pair_str("field", meta_column->column_name, T_STRING));
        db_send(", ");
        db_send(get_key_value_pair_str("type", data_type_name(meta_column->column_type), T_STRING));
        db_send(", ");
        if (meta_column->column_type == T_REFERENCE) {
            db_send(get_key_value_pair_str("table", meta_column->table_name, T_STRING));
            db_send(", ");
        }
        db_send(get_key_value_pair_str("primary key", &meta_column->is_primary, T_BOOL));
        db_send(", ");
        db_send(get_key_value_pair_str("size", &meta_column->column_length, T_INT));
        db_send("}");
        if (i < meta_table->column_size - 1)
            db_send(", ");
    }
    db_send("]\n");
}
