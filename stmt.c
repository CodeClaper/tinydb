#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "stmt.h"
#include "common.h"
#include "misc.h"
#include "token.h"
#include "pager.h"
#include "table.h"
#include "node.h"
#include "meta.h"
#include "insert.h"

// get row from insert statement
Row *get_statement_insert_row(Statement *stmt) {
    ASTNode *node = stmt->ast_node;
    if (node == NULL) {
        fatal("Sql parse error.");
    }
    assert(node->statement_type == INSERT_STMT);
    return generate_insert_row(node->insert_node);
}

// get table from statement
Table *get_statement_table(Statement *stmt) {
    Table *table = malloc(sizeof(Table));
    if (NULL == table)
        MALLOC_ERROR;
    return table;
}


// check if key already exists in db
bool check_duplicate_key(Cursor *cursor, uint32_t key) {
    void *node = get_page(cursor->table->pager, cursor->page_num);
    uint32_t row_length = calc_table_row_length(cursor->table);
    uint32_t target = get_leaf_node_cell_key(node, cursor->cell_num, row_length);
    return target == key;
}

// Create a table
ExecuteResult statement_create_table(Statement *stmt) {
    Table *table = get_statement_table(stmt);
    return EXECUTE_SUCCESS;
}

// execute insert statment
ExecuteResult statement_insert(Statement *stmt) {
    Row *row = get_statement_insert_row(stmt);
    if (row == NULL)
        return EXIT_FAILURE;
    Table *table = open_table(row->table_name);
    void *root_node = get_page(table->pager, table->root_page_num); 
    Cursor *cursor = define_cursor(table, row->id);
    if (check_duplicate_key(cursor, row->id)) {
        fprintf(stderr, "key '%d' already exists, not allow duplicate key", row->id);
        return EXECUTE_DUPLICATE_KEY;
    }
    insert_leaf_node(cursor, row);
    // free memeory
    for (uint32_t i = 0; i < row->data_len; i++) {
        if (row->data[i]) {
            free(row->data[i]);
        }
    }
    free(row);
    free(cursor);
    return EXECUTE_SUCCESS;    
}

ExecuteResult statement_select(Statement *statement) {
    return EXECUTE_SUCCESS;
}

ExecuteResult statement_update(Statement *statement) {
    return EXECUTE_SUCCESS;
}

ExecuteResult statement_delete(Statement *statement) {
    return EXECUTE_SUCCESS;
}

void free_statement(Statement *statement) {
    free_ast_node(statement->ast_node); 
    free(statement);
}
