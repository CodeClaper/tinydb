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
#include "utils.h"
#include "session.h"
#include "log.h"
#include "free.h"

/*Create table Statement*/
static ExecuteResult statement_create_table(Statement *stmt) {
    assert(stmt->statement_type == STMT_CREATE_TABLE);
    return exec_create_table_statement(stmt->ast_node->create_table_node);
}

/*Insert Statment*/
static ExecuteResult statement_insert(Statement *stmt) {
    assert(stmt->statement_type == STMT_INSERT);
    return exec_insert_statement(stmt->ast_node->insert_node);
}

/*Select Statement*/
static ExecuteResult statement_select(Statement *statement) {
    assert(statement->statement_type == STMT_SELECT);
    return exec_select_statement(statement->ast_node->select_node); 
}

/*Update statemetn*/
static ExecuteResult statement_update(Statement *statement) {
    assert(statement->statement_type == STMT_UPDATE);
    return exec_update_statment(statement->ast_node->update_node);
}

/*Delete Statement*/
static ExecuteResult statement_delete(Statement *statement) {
    assert(statement->statement_type == STMT_DELETE);
    return exec_delete_statement(statement->ast_node->delete_node);
}

/*Describe Statement*/
static ExecuteResult statement_describe(Statement *statement) {
    assert(statement->statement_type == STMT_DESCRIBE); 
    return exec_describe_statement(statement->ast_node->describe_node);
}

/*Show tables Statment*/
static ExecuteResult statement_show(Statement *statement) {
    assert(statement->statement_type == STMT_SHOW); 
    return exec_show_statement(statement->ast_node->show_node);
}

/*Execute statement
 * Now supported statments:
 * (1) SELECT
 * (2) UPDATE
 * (3) Insert
 * (4) DELETE
 * (5) CREATE TABLE
 * (6) SHOW TABLES AND SHOW MEMORY
 * (7) DESCRIBE TABLE
 * */
ExecuteResult statement(char *sql) {
    clock_t start, end;
    ExecuteResult result;
    start = clock();
    if (is_empty(sql))
        return EXECUTE_SQL_ERROR;
    Statement *statement = parse(sql);
    if (statement == NULL)
        return EXECUTE_SQL_ERROR;
    switch(statement->statement_type) {
        case STMT_CREATE_TABLE:
            result = statement_create_table(statement);
            break;
        case STMT_INSERT:
            result = statement_insert(statement); 
            break; 
        case STMT_SELECT:
            result = statement_select(statement); 
            break; 
        case STMT_UPDATE:
            result = statement_update(statement); 
            break; 
        case STMT_DELETE:
            result = statement_delete(statement); 
            break; 
        case STMT_DESCRIBE:
            result = statement_describe(statement);
            break;
        case STMT_SHOW:
            result = statement_show(statement);
            break;
    }
    free_statment(statement);
    end = clock();
    /*char buff[1024];*/
    /*sprintf(buff, "Duration: %lfs\n", (double)(end - start) / CLOCKS_PER_SEC);*/
    /*db_send(buff);*/
    return result;
}
