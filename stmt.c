#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "desc.h"
#include "show.h"
#include "free.h"
#include "input.h"
#include "output.h"

// Create a table
static void statement_create_table(Statement *stmt, Output *out) {
    assert(stmt->statement_type == STMT_CREATE_TABLE);
    MetaTable *meta_table = gen_meta_table(stmt->ast_node->create_table_node);
    out->result = create_table(meta_table);
}

// execute insert statment
static void statement_insert(Statement *stmt, Output *out) {
    assert(stmt->statement_type == STMT_INSERT);
    out->result = exec_insert_statement(stmt->ast_node->insert_node);
}

static void statement_select(Statement *statement, Output *out) {
    assert(statement->statement_type == STMT_SELECT);
    QueryParam *query_param = convert_query_param(statement->ast_node->select_node);
    if (query_param == NULL) {
        out->result = EXECUTE_FAIL;
        return;
    }
    SelectResult *select_result = query_with_condition(query_param);
    free_query_param(query_param);
    if (select_result) {
        put_select_result(out, select_result, query_param);
        free_select_result(select_result); 
    }
}

static void statement_update(Statement *statement, Output *out) {
    out->result = EXECUTE_SUCCESS;
}

static void statement_delete(Statement *statement, Output *out) {
    out->result = EXECUTE_SUCCESS;
}

static void statement_describe(Statement *statement, Output *out) {
    assert(statement->statement_type == STMT_DESCRIBE); 
    out->result = EXECUTE_SUCCESS;
}

static void statement_show_tables(Statement *statement, Output *out) {
    assert(statement->statement_type == STMT_SHOW_TABLES); 
    TableList *table_list = gen_table_list();
    if (table_list != NULL) {
        print_show_table(stdout, table_list);
    }
    out->result = EXECUTE_SUCCESS;
}

// statement
Output *statement(char *sql) {
    Output *out = malloc(sizeof(Output));
    if (out == NULL)
        MALLOC_ERROR;
    memset(out, 0, sizeof(Output));
    if (is_empty(sql)) {
        out->result = EXECUTE_SQL_ERROR;
        return out;
    }
    Statement *statement = parse(sql);
    if (statement == NULL) {
        out->result = EXECUTE_SQL_ERROR;
        return out;
    }
    switch(statement->statement_type) {
        case STMT_CREATE_TABLE:
            statement_create_table(statement, out);
            break;
        case STMT_INSERT:
            statement_insert(statement, out); 
            break; 
        case STMT_SELECT:
            statement_select(statement, out); 
            break; 
        case STMT_UPDATE:
            statement_update(statement, out); 
            break; 
        case STMT_DELETE:
            statement_delete(statement, out); 
            break; 
        case STMT_DESCRIBE:
            statement_describe(statement, out);
            break;
        case STMT_SHOW_TABLES:
            statement_show_tables(statement, out);
            break;
    }
    return out;
}
