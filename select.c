#include "select.h"
#include "table.h"
#include "pager.h"
#include "node.h"
#include "meta.h"
#include "sql/intpr.h"
#include <stdint.h>

static char* get_table_name(SelectNode *select_node) {
    return select_node->from_item_node->table->name;
}

static void select_row_print(void *destinct, MetaTable *meta_table) {
    uint off_set = 0;
    for(uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        printf("column : %s", meta_column->column_name);
        void *value = destinct + off_set;
        switch(meta_column->column_type) {
            case T_INT:
                printf("\t\tvalue : %d", *(uint32_t *) value);
                break;
            case T_STRING:
                printf("\t\tvalue: %s", (char *) value);
                break;
            default:
                break;
        }
        off_set += meta_column->column_length;
        printf("\n");
    }
}
 
// print select result.
ExecuteResult select_print(SelectNode *select_node) {
    char *table_name = get_table_name(select_node);
    Table *table = open_table(table_name);
    if (table == NULL)
        return EXECUTE_TABLE_EXIST_FAIL;
    uint32_t row_len = calc_table_row_length(table);
    uint32_t i, j;
    for(i = 0; i < table->pager->num_page; i++) {
        void *node = get_page(table->pager, i);
        uint32_t cell_num = get_leaf_node_cell_num(node);
        for(j = 0; j < cell_num; j++) {
            void *destinct = get_leaf_node_cell_value(node, row_len, j); 
            select_row_print(destinct, table->meta_table);
        }
    }
    return EXECUTE_SUCCESS;
}
