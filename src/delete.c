#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "delete.h"
#include "mmu.h"
#include "data.h"
#include "table.h"
#include "copy.h"
#include "cond.h"
#include "select.h"
#include "refer.h"
#include "node.h"
#include "check.h"
#include "trans.h"
#include "session.h"

/* Adapt to select items node data type. */
static SelectItemsNode *adapt_select_items_node() {
    SelectItemsNode *select_items_node = db_malloc(sizeof(SelectItemsNode));
    select_items_node->type = SELECT_ALL;
    return select_items_node;
}

/* Adapt to query param data type. */
static QueryParam *adapt_query_param(DeleteNode *delete_node, Table *table) {
    QueryParam *query_param = db_malloc(sizeof(QueryParam));
    query_param->table_name = strdup(delete_node->table_name);
    query_param->select_items = adapt_select_items_node();
    ConditionNode *condition_node_copy = copy_condition_node(delete_node->condition_node);
    query_param->condition_node = tree(condition_node_copy);
    return query_param;
}

/* Delete row */
static void delete_row(Row *row, SelectResult *select_result, Table *table, void *arg) {
    Cursor *cursor = define_cursor(table, row->key);
    
    /* This because, the input row is a snapshot. */
    row = define_row(convert_refer(cursor));

    if (row_is_visible(row)) {
        update_transaction_state(row, TR_DELETE);
    }
    // delete_leaf_node_cell(cursor, row->key);
    select_result->row_size++;
}

/* Execute delete statment.*/
ExecuteResult exec_delete_statement(DeleteNode *delete_node) { 
    Table *table = open_table(delete_node->table_name);
    if (table == NULL)
        return EXECUTE_TABLE_OPEN_FAIL;

    /* Check out delete node. */
    if (!check_delete_node(delete_node))
        return EXECUTE_FAIL;

    /* Adapt to query param. */
    QueryParam *query_param = adapt_query_param(delete_node, table);

    /* Query with condition, and delete satisfied condition row. */
    SelectResult *select_result = new_select_result(delete_node->table_name);
    query_with_condition(query_param, select_result, delete_row, NULL);

    /* Root fall back. */
    root_fall_back_root_node(table);

    /* Send out deleted result. */
    db_send("Successfully deleted %d row data.\n", select_result->row_size);

    return EXECUTE_SUCCESS;
}

