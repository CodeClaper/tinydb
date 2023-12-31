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

/* Create table Statement. */
static void statement_create_table(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == CREATE_TABLE_STMT, "System error, create statement type error.\n");
    exec_create_table_statement(stmt->ast_node->create_table_node, result);
}

/* Drop table statement. */
static void statement_drop_table(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == DROP_TABLE_STMT, "System error, drop statement type error.\n");
    drop_table(stmt->ast_node->drop_table_node->table_name, result);
}


/*Insert Statment*/
static void statement_insert(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == INSERT_STMT, "System error, insert statement type error.\n");
    exec_insert_statement(stmt->ast_node->insert_node, result);
}

/*Select Statement*/
static void statement_select(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == SELECT_STMT, "System error, select statement type error.\n");
    exec_select_statement(statement->ast_node->select_node, result); 
}

/*Update statemetn*/
static void statement_update(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == UPDATE_STMT, "System error, update statement type error.\n");
    exec_update_statment(statement->ast_node->update_node, result);
}

/*Delete Statement*/
static void statement_delete(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == DELETE_STMT, "System error, delete statement type error.\n");
    exec_delete_statement(statement->ast_node->delete_node, result);
}

/*Describe Statement*/
static void statement_describe(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == DESCRIBE_STMT, "System error, describe statement type error.\n"); 
    exec_describe_statement(statement->ast_node->describe_node, result);
}

/*Show tables Statment*/
static void statement_show(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == SHOW_STMT, "System error, show statmement type error.\n"); 
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
void statement(char *sql) {

    /* Check empty sql. */
    if (is_empty(sql)) return;

    /* Execute statement. */
    Statement *statement = parse(sql);
    if (statement == NULL) return;

    /* Execute statment */
    clock_t start, end;
    start = clock();
    DBResult *result = new_db_result();
    result->stmt_type = statement->statement_type;
    switch(statement->statement_type) {
        case BEGIN_TRANSACTION_STMT:
            statement_begin_transaction(statement, result);
            break;
        case COMMIT_TRANSACTION_STMT:
            statement_commit_transaction(statement, result);
            break;
        case CREATE_TABLE_STMT:
            statement_create_table(statement, result);
            break;
        case INSERT_STMT:
            statement_insert(statement, result); 
            break; 
        case SELECT_STMT:
            statement_select(statement, result); 
            break; 
        case UPDATE_STMT:
            statement_update(statement, result); 
            break; 
        case DELETE_STMT:
            statement_delete(statement, result); 
            break; 
        case DESCRIBE_STMT:
            statement_describe(statement, result);
            break;
        case SHOW_STMT:
            statement_show(statement, result);
            break;
        case DROP_TABLE_STMT:
            statement_drop_table(statement, result);
            break;
    }

    /* Commit transction manually. */
    auto_commit_transaction(result);

    /* Calulate duration. */
    end = clock();
    result->duration = (double)(end - start) / CLOCKS_PER_SEC;
    db_info("Duration: %lfs", result->duration);

    /* send result. */
    db_send_result(result);

    /* Free memory. */
    free_statment(statement);
    free_db_result(result);
}
