#include "delete.h"
#include "data.h"
#include "table.h"
#include "copy.h"
#include "cond.h"
#include "select.h"
#include "output.h"
#include "node.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


// adapt to select items node.
static SelectItemsNode *adapt_select_items_node() {
    SelectItemsNode *select_items_node = malloc(sizeof(SelectItemsNode));
    memset(select_items_node, 0, sizeof(SelectItemsNode));
    select_items_node->type = SELECT_ALL;
    return select_items_node;
}

// adapt to query param.
static QueryParam *adapt_query_param(DeleteNode *delete_node, Table *table) {
    QueryParam *query_param = malloc(sizeof(QueryParam));
    memset(query_param, 0, sizeof(QueryParam));
    query_param->table_name = strdup(delete_node->table_name);
    query_param->select_items = adapt_select_items_node();
    ConditionNode *condition_node_copy = copy_condition_node(delete_node->condition_node);
    query_param->condition_node = tree(condition_node_copy);
    return query_param;
}

// delete rows.
static void delete_rows(SelectResult *select_result, Table *table) {
    for (uint32_t i = 0; i < select_result->row_size; i++) {
        Row *current_row = *(select_result->row + i);
        Cursor *cursor = define_cursor(table, current_row->key);
        clean_up_obsolute_cell(cursor);
    }
}

//Execute delete statment.
ExecuteResult exec_delete_statement(DeleteNode *delete_node,  Output *out) { 
    Table *table = open_table(delete_node->table_name);
    if (table == NULL)
        return EXECUTE_TABLE_OPEN_FAIL;
    QueryParam *query_param = adapt_query_param(delete_node, table);
    SelectResult *select_result = query_with_condition(query_param);
    delete_rows(select_result, table);
    print_data_d(out, "Successfully deleted %d row data.", select_result->row_size);
    return EXECUTE_SUCCESS;
}

