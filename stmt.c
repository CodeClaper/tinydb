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
#include "desc.h"
#include "show.h"
#include "free.h"

// Create a table
ExecuteResult statement_create_table(Statement *stmt) {
    assert(stmt->statement_type == STMT_CREATE_TABLE);
    MetaTable *meta_table = gen_meta_table(stmt->ast_node->create_table_node);
    return create_table(meta_table);
}

// execute insert statment
ExecuteResult statement_insert(Statement *stmt) {
    assert(stmt->statement_type == STMT_INSERT);
    return exec_insert_statement(stmt->ast_node->insert_node);
}

ExecuteResult statement_select(Statement *statement) {
    assert(statement->statement_type == STMT_SELECT);
    QueryParam *query_param = convert_query_param(statement->ast_node->select_node);
    if (query_param == NULL)
        return EXECUTE_FAIL;
    SelectResult *select_result = gen_select_result(query_param);
    if (select_result) {
        print_select_result_plain(select_result, query_param);
        free_select_result(select_result); 
    }
    return EXECUTE_SUCCESS;
}

ExecuteResult statement_update(Statement *statement) {
    return EXECUTE_SUCCESS;
}

ExecuteResult statement_delete(Statement *statement) {
    return EXECUTE_SUCCESS;
}

ExecuteResult statement_describe(Statement *statement) {
    assert(statement->statement_type == STMT_DESCRIBE); 
    return print_describe_info(statement->ast_node->describe_node);
}

ExecuteResult statement_show_tables(Statement *statement) {
    assert(statement->statement_type == STMT_SHOW_TABLES); 
    TableList *table_list = gen_table_list();
    if (table_list != NULL) {
        print_show_table(stdout, table_list);
    }
    return EXECUTE_SUCCESS;
}
