#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stmt.h"
#include "mmu.h"
#include "common.h"
#include "asserts.h"
#include "misc.h"
#include "parser.h"
#include "table.h"
#include "create.h"
#include "select.h"
#include "insert.h"
#include "update.h"
#include "delete.h"
#include "desc.h"
#include "show.h"
#include "trans.h"
#include "utils.h"
#include "session.h"
#include "log.h"
#include "free.h"

/* Begin tranasction statement. */
static ExecuteResult statement_begin_transaction(Statement *stmt) {
    assert_true(stmt->statement_type == BEGIN_TRANSACTION_STMT, "System error, begin tranasction statement type error.\n");
    return begin_transaction();
}

/* Commit tranasction statement. */
static ExecuteResult statement_commit_transaction(Statement *stmt) {
    assert_true(stmt->statement_type == COMMIT_TRANSACTION_STMT, "System error, commit tranasction statement type error.\n");
    return commit_transaction();
}

/*Create table Statement*/
static ExecuteResult statement_create_table(Statement *stmt) {
    assert_true(stmt->statement_type == STMT_CREATE_TABLE, "System error, create statement type error.\n");
    return exec_create_table_statement(stmt->ast_node->create_table_node);
}

/*Insert Statment*/
static ExecuteResult statement_insert(Statement *stmt) {
    assert_true(stmt->statement_type == STMT_INSERT, "System error, insert statement type error.\n");
    InsertExecuteResult *result = exec_insert_statement(stmt->ast_node->insert_node);
    return result->status;
}

/*Select Statement*/
static ExecuteResult statement_select(Statement *statement) {
    assert_true(statement->statement_type == STMT_SELECT, "System error, select statement type error.\n");
    return exec_select_statement(statement->ast_node->select_node); 
}

/*Update statemetn*/
static ExecuteResult statement_update(Statement *statement) {
    assert_true(statement->statement_type == STMT_UPDATE, "System error, update statement type error.\n");
    return exec_update_statment(statement->ast_node->update_node);
}

/*Delete Statement*/
static ExecuteResult statement_delete(Statement *statement) {
    assert_true(statement->statement_type == STMT_DELETE, "System error, delete statement type error.\n");
    return exec_delete_statement(statement->ast_node->delete_node);
}

/*Describe Statement*/
static ExecuteResult statement_describe(Statement *statement) {
    assert_true(statement->statement_type == STMT_DESCRIBE, "System error, describe statement type error.\n"); 
    return exec_describe_statement(statement->ast_node->describe_node);
}

/*Show tables Statment*/
static ExecuteResult statement_show(Statement *statement) {
    assert_true(statement->statement_type == STMT_SHOW, "System error, show statmement type error.\n"); 
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
 * (8) BEGIN TRANSACTION
 * (9) COMMIT TRANSACTION
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
        case STMT_BEGINE_TRANSACTION:
            result = statement_begin_transaction(statement);
            break;
        case STMT_COMMIT_TRANSACTION:
            result = statement_commit_transaction(statement);
            break;
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
    /* Commit transction manually. */
    auto_commit_transaction();
    free_statment(statement);
    end = clock();
    db_info("Duration: %lfs\n", (double)(end - start) / CLOCKS_PER_SEC);
    return result;
}
