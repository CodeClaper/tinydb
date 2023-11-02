#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stmt.h"
#include "mem.h"
#include "common.h"
#include "misc.h"
#include "token.h"
#include "table.h"
#include "create.h"
#include "select.h"
#include "insert.h"
#include "update.h"
#include "delete.h"
#include "desc.h"
#include "show.h"
#include "free.h"
#include "input.h"
#include "output.h"
#include "check.h"
#include "log.h"

// Create a table
static void statement_create_table(Statement *stmt, Output *out) {
    assert(stmt->statement_type == STMT_CREATE_TABLE);
    MetaTable *meta_table = gen_meta_table(stmt->ast_node->create_table_node);
    out->result = create_table(meta_table);
    if (out->result == EXECUTE_SUCCESS) {
        print_data_s(out, "Table '%s' created successfully.", meta_table->table_name);
    }
    db_free(meta_table);
}

// execute insert statment
static void statement_insert(Statement *stmt, Output *out) {
    assert(stmt->statement_type == STMT_INSERT);
    out->result = exec_insert_statement(stmt->ast_node->insert_node);
    if (out->result == EXECUTE_SUCCESS)
        print_data(out, "Successfully insert 1 row data.");
}

static void statement_select(Statement *statement, Output *out) {
    assert(statement->statement_type == STMT_SELECT);
    QueryParam *query_param = convert_query_param(statement->ast_node->select_node);
    if (check_query_param(query_param)) {
        SelectResult *select_result = query_with_condition(query_param);
        if (select_result) {
            put_select_result(select_result, query_param, out);
            free_select_result(select_result); 
            out->result = EXECUTE_SUCCESS;
        }
    }
    free_query_param(query_param);
}

static void statement_update(Statement *statement, Output *out) {
    assert(statement->statement_type == STMT_UPDATE);
    out->result = exec_update_statment(statement->ast_node->update_node, out);
}

static void statement_delete(Statement *statement, Output *out) {
    assert(statement->statement_type == STMT_DELETE);
    out->result = exec_delete_statement(statement->ast_node->delete_node, out);
}

static void statement_describe(Statement *statement, Output *out) {
    assert(statement->statement_type == STMT_DESCRIBE); 
    out->result = print_describe_info(statement->ast_node->describe_node, out);
}

static void statement_show_tables(Statement *statement, Output *out) {
    assert(statement->statement_type == STMT_SHOW); 
    out->result = exec_show_statement(statement->ast_node->show_node, out);
}

// statement
Output *statement(char *sql) {
    clock_t start, end;
    start = clock();
    Output *out = db_malloc2(sizeof(Output), "Output");
    out->buffer_size = BUFF_SIZE;
    out->result = EXECUTE_FAIL;
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
        case STMT_SHOW:
            statement_show_tables(statement, out);
            break;
    }
    free_statment(statement);
    end = clock();
    sprintf(out->duration, "Execution duration %lfs", (double)(end - start) / CLOCKS_PER_SEC);
    return out;
}
