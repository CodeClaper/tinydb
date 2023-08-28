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
#include "select.h"
#include "create.h"

// get row from insert statement
Row *get_statement_insert_row(Statement *stmt) {
    ASTNode *node = stmt->ast_node;
    if (node == NULL) {
        fatal("Sql parse error.");
    }
    assert(node->statement_type == INSERT_STMT);
    return generate_insert_row(node->insert_node);
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
    assert(stmt->statement_type == STMT_CREATE_TABLE);
    MetaTable *meta_table = gen_meta_table(stmt->ast_node->create_table_node);
    return create_table(meta_table);
}

// execute insert statment
ExecuteResult statement_insert(Statement *stmt) {
    Row *row = get_statement_insert_row(stmt);
    if (row == NULL)
        return EXIT_FAILURE;
    Table *table = open_table(row->table_name);
    void *root_node = get_page(table->pager, table->root_page_num); 
    Cursor *cursor = define_cursor(table, row->key);
    if (check_duplicate_key(cursor, row->key)) {
        fprintf(stderr, "key '%d' already exists, not allow duplicate key. \n", row->key);
        return EXECUTE_DUPLICATE_KEY;
    }
    insert_leaf_node(cursor, row);
    flush_page(cursor->table->pager, cursor->page_num); // flush into disk.
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
    assert(statement->statement_type == STMT_SELECT);
    select_print(statement->ast_node->select_node);
    return EXECUTE_SUCCESS;
}

ExecuteResult statement_update(Statement *statement) {
    return EXECUTE_SUCCESS;
}

ExecuteResult statement_delete(Statement *statement) {
    return EXECUTE_SUCCESS;
}

void free_statement(Statement *statement) {
    free(statement);
}
