#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h>
#include <time.h>
#include "stmt.h"
#include "defs.h"
#include "mmu.h"
#include "common.h"
#include "asserts.h"
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
#include "buffer.h"
#include "log.h"
#include "free.h"
#include "json.h"
#include "xlog.h"


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

/* Rollback tranasction statement. */
static void statement_roolback_transaction(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == ROLLBACK_TRANSACTION_STMT, "System error, rollback tranasction statement type error.\n");
    rollback_transaction(result);
}

/* Create table Statement. */
static void statement_create_table(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == CREATE_TABLE_STMT, "System error, create statement type error.\n");
    exec_create_table_statement(stmt->create_table_node, result);
}

/* Drop table statement. */
static void statement_drop_table(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == DROP_TABLE_STMT, "System error, drop statement type error.\n");
    char *table_name = stmt->drop_table_node->table_name;
    if (drop_table(table_name)) {
        result->success = true;
        result->rows = 0;
        result->message = format("Table '%s' droped successfully.", table_name);
        db_log(SUCCESS, "Table '%s' droped successfully.", table_name);
    }
}

/*Insert Statment*/
static void statement_insert(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == INSERT_STMT, "System error, insert statement type error.\n");
    auto_begin_transaction();
    ReferSet *refer_set = exec_insert_statement(stmt->insert_node);
    if (refer_set) {
        result->success = true;
        result->rows = refer_set->size;
        result->message = format("Insert %d rows data to table '%s' successfully.", result->rows, stmt->insert_node->table_name);
        db_log(SUCCESS, "Insert %d row data to table '%s' successfully.", result->rows, stmt->insert_node->table_name);
        free_refer_set(refer_set);
    }
}

/*Select Statement*/
static void statement_select(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == SELECT_STMT, "System error, select statement type error.\n");
    auto_begin_transaction();
    exec_select_statement(statement->select_node, result); 
}

/*Update statemetn*/
static void statement_update(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == UPDATE_STMT, "System error, update statement type error.\n");
    auto_begin_transaction();
    exec_update_statment(statement->update_node, result);
}

/*Delete Statement*/
static void statement_delete(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == DELETE_STMT, "System error, delete statement type error.\n");
    auto_begin_transaction();
    exec_delete_statement(statement->delete_node, result);
}

/*Describe Statement*/
static void statement_describe(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == DESCRIBE_STMT, "System error, describe statement type error.\n"); 
    MapList *map_list = exec_describe_statement(statement->describe_node);
    if (map_list) {
        /* Success resule. */
        result->success = true;
        result->data = map_list;
        result->message = db_strdup("Describe executed successfully.");
        db_log(SUCCESS, "Describe executed successfully.");
    }
}

/*Show tables Statment*/
static void statement_show(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == SHOW_STMT, "System error, show statmement type error.\n"); 
    exec_show_statement(statement->show_node, result);
}

/* Execute statment. */
static void exec_statement(Statement *statement, DBResult *result) {
    /* Execute statment */
    clock_t start, end;
    start = clock();
    if (statement) {
        result->stmt_type = statement->statement_type;
        switch(statement->statement_type) {
            case BEGIN_TRANSACTION_STMT:
                statement_begin_transaction(statement, result);
                break;
            case COMMIT_TRANSACTION_STMT:
                statement_commit_transaction(statement, result);
                break;
            case ROLLBACK_TRANSACTION_STMT:
                statement_roolback_transaction(statement, result);
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

    } 

    /* Calulate duration. */
    end = clock();
    result->duration = (double)(end - start) / CLOCKS_PER_SEC;
    db_log(INFO, "Duration: %lfs", result->duration);

}


/* Execute SQL
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
void execute(char *sql) {

    clock_t start, end;
    start = clock();
    DBResultSet *result_set = new_db_result_set();
    /* Check empty sql. */
    if (!is_empty(sql)) {
        Statements *statements = NULL;
        /* Catch Error. */
        if (setjmp(errEnv) == 0) {
            statements = parse(sql);
            /* Execute each statement. */
            uint32_t i;
            for (i = 0; i < statements->size; i++) {
                DBResult *result = new_db_result();
                add_db_result(result_set, result);
                Statement *statement = statements->list[i];
                exec_statement(statement, result);
            }
        } else {
            /* Catch routine. */
            /* If the set is empty, which means sql syntax error, put an error result to the set. */
            if (result_set->size == 0) {

                DBResult *err_result = new_db_result();

                /* For error catch, result is false. */
                err_result->success = false;

                add_db_result(result_set, err_result);
            }

            /* If last result is error, it lack duration, make up. */
            DBResult *last_result = result_set->set[result_set->size - 1];
            if (last_result->success == false) {
                /* Calulate duration. */
                end = clock();
                last_result->duration = (double)(end - start) / CLOCKS_PER_SEC;
                db_log(INFO, "Duration: %lfs", last_result->duration);
            }
        }
        /* Free memory. */
        free_statements(statements);
    } 

    db_send_result_set(result_set);

    free_db_result_set(result_set);

    /* Free buffer. */
    remove_table_buffer();

    /* Commit transction manually. */
    auto_commit_transaction();
}
