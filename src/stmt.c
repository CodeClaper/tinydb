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
#include "ret.h"


/* Begin tranasction statement. */
static void statement_begin_transaction(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == BEGIN_TRANSACTION_STMT, "System error, begin tranasction statement type error.\n");
    begin_transaction(result);
}

/* Commit tranasction statement. */
static void statement_commit_transaction(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == COMMIT_TRANSACTION_STMT, "System error, commit tranasction statement type error.\n");
    commit_transaction(result);
}

/*Create table Statement*/
static void statement_create_table(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == STMT_CREATE_TABLE, "System error, create statement type error.\n");
    exec_create_table_statement(stmt->ast_node->create_table_node, result);
}

/*Insert Statment*/
static void statement_insert(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == STMT_INSERT, "System error, insert statement type error.\n");
    exec_insert_statement(stmt->ast_node->insert_node, result);
}

/*Select Statement*/
static void statement_select(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == STMT_SELECT, "System error, select statement type error.\n");
    exec_select_statement(statement->ast_node->select_node, result); 
}

/*Update statemetn*/
static void statement_update(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == STMT_UPDATE, "System error, update statement type error.\n");
    exec_update_statment(statement->ast_node->update_node, result);
}

/*Delete Statement*/
static void statement_delete(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == STMT_DELETE, "System error, delete statement type error.\n");
    exec_delete_statement(statement->ast_node->delete_node, result);
}

/*Describe Statement*/
static void statement_describe(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == STMT_DESCRIBE, "System error, describe statement type error.\n"); 
    exec_describe_statement(statement->ast_node->describe_node, result);
}

/*Show tables Statment*/
static void statement_show(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == STMT_SHOW, "System error, show statmement type error.\n"); 
    exec_show_statement(statement->ast_node->show_node, result);
}

/*Execute statement
 * Now supported statments:
 * (1) SELECT
 * (2) UPDATE
 * (3) INSERT
 * (4) DELETE
 * (5) CREATE TABLE
 * (6) DEROP TABLE
 * (6) SHOW TABLES AND SHOW MEMORY
 * (7) DESCRIBE TABLE
 * (8) BEGIN TRANSACTION
 * (9) COMMIT TRANSACTION
 * */
DBResult *statement(char *sql) {
    clock_t start, end;
    DBResult *result = new_db_result();
    start = clock();
    if (is_empty(sql)) {
        return result;
    }
    /* Execute statement. */
    Statement *statement = parse(sql);
    if (statement == NULL) {
        return result;
    }
    switch(statement->statement_type) {
        case STMT_BEGINE_TRANSACTION:
            result->stmt_type = STMT_BEGINE_TRANSACTION;
            statement_begin_transaction(statement, result);
            break;
        case STMT_COMMIT_TRANSACTION:
            result->stmt_type = STMT_COMMIT_TRANSACTION;
            statement_commit_transaction(statement, result);
            break;
        case STMT_CREATE_TABLE:
            result->stmt_type = STMT_CREATE_TABLE;
            statement_create_table(statement, result);
            break;
        case STMT_INSERT:
            result->stmt_type = STMT_INSERT;
            statement_insert(statement, result); 
            break; 
        case STMT_SELECT:
            result->stmt_type = STMT_SELECT;
            statement_select(statement, result); 
            break; 
        case STMT_UPDATE:
            result->stmt_type = STMT_UPDATE;
            statement_update(statement, result); 
            break; 
        case STMT_DELETE:
            result->stmt_type = STMT_DELETE;
            statement_delete(statement, result); 
            break; 
        case STMT_DESCRIBE:
            result->stmt_type = STMT_DESCRIBE;
            statement_describe(statement, result);
            break;
        case STMT_SHOW:
            result->stmt_type = STMT_SHOW;
            statement_show(statement, result);
            break;
    }
    /* Commit transction manually. */
    auto_commit_transaction(result);
    /* Free statement memory. */
    free_statment(statement);
    /* Calulate duration. */
    end = clock();
    result->duration = (double)(end - start) / CLOCKS_PER_SEC;
    db_info("Duration: %lfs", result->duration);
    /* send result. */
    db_send_result(result);
    return result;
}
