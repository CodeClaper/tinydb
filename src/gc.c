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
#include "log.h"
#include "free.h"
#include "trans.h"
#include "table.h"
#include "ltree.h"
#include "refer.h"
#include "select.h"
#include "asserts.h"

#define DEFAULT_GC_INTERVAL 10

/* Check if allow to GC for now. */
static bool allow_gc();

/* loop GC */
void loop_gc() {
    
    /* Loop scanning. */
    while(true) {

        sleep(DEFAULT_GC_INTERVAL); /* Sleep specified interval. */
        
        if (!allow_gc())
            continue;

        /* loop each of tables to gc. */
        TableList *table_list = get_table_list();

        int i;
        for(i = 0; i < table_list->count; i++) {
            gc_table(table_list->table_name_list[i]); 
        }

        /* Free memory. */
        free_table_list(table_list);
    }
}

/* Check if allow to GC for now. 
 * Conditions: 
 * (1) No transaction running.
 * */
static bool allow_gc() {
    /* Wait all transaction committed. */
    while(any_transaction_running()) {
        usleep(10);
    }
    return true;
}

/* Gc row*/
void gc_row(Row *row, SelectResult *select_result, Table *table, void *arg) {
    /* Only for deleted row. */
    if (!row_is_deleted(row))
        return;

    /* Cursor */
    Cursor * cursor = define_cursor(table, row->key);

    /* Delete row. */
    delete_leaf_node_cell(cursor, row->key);
}

/* Gc table */
void gc_table(char *table_name) {

#ifdef DEBUG
    db_log(DEBUG, "GC table '%s'.", table_name);
#endif

    /* Check table exist. */
    Table *table = open_table(table_name);
    assert_not_null(table, "System error, table '%s' not exist.", table_name);

    /* Query with condition, and delete satisfied condition row. */
    SelectResult *select_result = new_select_result(table_name);

    query_with_condition(NULL, select_result, gc_row, NULL);
    
    free_select_result(select_result);
}

