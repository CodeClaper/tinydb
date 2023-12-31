/**
* ================================= The Garbage Collector (GC) ===================================================
* The GC module is intended to collecte the deleted rows and clean up the unused disk.
* Usually, GC works in the deamon thread, and loop interval scanning.
* GC only starts working on the table only if there are no transactions on the table.
* When GC working on the table, it will lock the table, any transaction that trying to write the table will block.
* =================================================================================================================
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "gc.h"
#include "data.h"
#include "mmu.h"
#include "trans.h"
#include "table.h"
#include "node.h"
#include "select.h"
#include "asserts.h"
#include "log.h"

#define DEFAULT_GC_INTERVAL 30

/* loop GC */
void loop_gc() {
    
    /* Loop scanning. */
    while(true) {

        sleep(DEFAULT_GC_INTERVAL); /* Sleep specified interval. */
        
        /* Wait all transaction committed. */
        while(any_transaction_running()) {
            usleep(10);
        }

        /* loop each of tables to gc. */
        TableList *table_list = get_table_list();

        int i;
        for(i = 0; i < table_list->count; i++) {
            gc_table(table_list->table_name_list[i]); 
        }
    }
}

/* Fake QueryParam. */
static QueryParam *fake_query_param(Table *table) {
    /* query_param */
    QueryParam *query_param = db_malloc2(sizeof(QueryParam), "QueryParam");
    query_param->table_name = strdup(table->meta_table->table_name);

    /* select_items_node */
    SelectItemsNode *select_items_node = db_malloc(sizeof(SelectItemsNode));
    select_items_node->type = SELECT_ALL;
    
    query_param->select_items = select_items_node;
    query_param->condition_node = NULL;

    return query_param;
}

/* Gc row*/
void gc_row(Row *row, SelectResult *select_result, Table *table, void *arg) {
    /* Only for deleted row. */
    if (!row_is_deleted(row))
        return;

    /* Cursor */
    Cursor *cursor = define_cursor(table, row->key);

    /* delete row. */
    delete_leaf_node_cell(cursor, row->key);
}

/* Gc table */
void gc_table(char *table_name) {

    db_info("Start GC table '%s'", table_name);

    /* Check table exist. */
    Table *table = open_table(table_name);
    assert_not_null(table, "System error, table not exist.\n");

    /* fake query param. */
    QueryParam *query_param = fake_query_param(table);

    /* Query with condition, and delete satisfied condition row. */
    SelectResult *select_result = new_select_result(table_name);

    query_with_condition(query_param, select_result, gc_row, NULL);
}

