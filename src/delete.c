#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "delete.h"
#include "mmu.h"
#include "data.h"
#include "table.h"
#include "copy.h"
#include "select.h"
#include "refer.h"
#include "ltree.h"
#include "check.h"
#include "trans.h"
#include "session.h"
#include "ret.h"
#include "log.h"

/* Delete row */
static void delete_row(Row *row, SelectResult *select_result, Table *table, void *arg) {

    /* Only deal with row that is visible for current transaction. */
    if (row_is_visible(row)) {
        Cursor *cursor = define_cursor(table, row->key);
        update_transaction_state(row, TR_DELETE);
        update_row_data(row, cursor);
        select_result->row_size++;
    }
}

/* Execute delete statment.*/
void exec_delete_statement(DeleteNode *delete_node, DBResult *result) { 

    /* Check table exists. */
    Table *table = open_table(delete_node->table_name);
    if (table == NULL) {
        db_log(ERROR, "Try to open table '%s' fail.", delete_node->table_name);
        return;
    }

    /* Check out delete node. */
    if (!check_delete_node(delete_node)) 
        return;

    /* Query with condition, and delete satisfied condition row. */
    SelectResult *select_result = new_select_result(delete_node->table_name);

    /* Query with condition and delete satisfied row. */
    query_with_condition(delete_node->condition_node, select_result, delete_row, NULL);

    /* Root fall back. */
    root_fall_back_root_node(table);

    /* Success Result . */
    result->success = true;
    result->rows = select_result->row_size;

    db_log(SUCCESS, "Successfully deleted %d row data.", select_result->row_size);
}

