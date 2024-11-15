#include <bits/types/struct_timeval.h>
#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "stmt.h"
#include "list.h"
#include "defs.h"
#include "mem.h"
#include "common.h"
#include "asserts.h"
#include "parser.h"
#include "table.h"
#include "create.h"
#include "select.h"
#include "insert.h"
#include "update.h"
#include "delete.h"
#include "drop.h"
#include "desc.h"
#include "show.h"
#include "alter.h"
#include "trans.h"
#include "utils.h"
#include "session.h"
#include "buffer.h"
#include "log.h"
#include "free.h"
#include "jsonwriter.h"
#include "instance.h"
#include "xlog.h"
#include "timer.h"


/* Begin tranasction statement. */
static void statement_begin_transaction(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == BEGIN_TRANSACTION_STMT,
               "System error, begin tranasction statement type error.");
    begin_transaction();
    result->success = true;
    result->message = format("Begin new transaction successfully." );
}

/* Commit tranasction statement. */
static void statement_commit_transaction(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == COMMIT_TRANSACTION_STMT, 
               "System error, commit tranasction statement type error.");
    commit_transaction();

    result->success = true;
    result->message = format("Commit the transaction successfully.");
}

/* Rollback tranasction statement. */
static void statement_roolback_transaction(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == ROLLBACK_TRANSACTION_STMT, 
                "System error, rollback tranasction statement type error.");
    rollback_transaction();

    result->success = true;
    result->message = format("Rollback and commit the transaction successfully.");
}

/* Create table Statement. */
static void statement_create_table(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == CREATE_TABLE_STMT, 
                "System error, create statement type error.");
    auto_begin_transaction();
    exec_create_table_statement(stmt->create_table_node, result);
}

/* Drop table statement. */
static void statement_drop_table(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == DROP_TABLE_STMT,
               "System error, drop statement type error.");
    char *table_name = stmt->drop_table_node->table_name;
    auto_begin_transaction();
    exec_drop_table_statement(table_name, result);
}

/* Alter table statement. */
static void statement_alter_table(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == ALTER_TABLE_STMT,
               "System error, alter table statement type error.");
    auto_begin_transaction();
    exec_alter_statement(stmt->alter_table_node, result);
}

/*Insert Statment*/
static void statement_insert(Statement *stmt, DBResult *result) {
    assert_true(stmt->statement_type == INSERT_STMT,
               "System error, insert statement type error.");
    auto_begin_transaction();
    List *list = exec_insert_statement(stmt->insert_node);
    if (list) {
        result->success = true;
        result->rows = len_list(list);
        result->message = format("Insert %d rows data to table '%s' successfully.",
                                 result->rows, stmt->insert_node->table_name);
        db_log(SUCCESS, "Insert %d row data to table '%s' successfully.",
               result->rows, stmt->insert_node->table_name);
        free_list_deep(list);
    }
}

/*Select Statement*/
static void statement_select(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == SELECT_STMT,
               "System error, select statement type error.");
    auto_begin_transaction();
    exec_select_statement(statement->select_node, result); 
}

/*Update statemetn*/
static void statement_update(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == UPDATE_STMT,
               "System error, update statement type error.");
    auto_begin_transaction();
    exec_update_statment(statement->update_node, result);
}

/*Delete Statement*/
static void statement_delete(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == DELETE_STMT,
               "System error, delete statement type error.");
    auto_begin_transaction();
    exec_delete_statement(statement->delete_node, result);
}

/*Describe Statement*/
static void statement_describe(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == DESCRIBE_STMT,
               "System error, describe statement type error."); 
    List *list = exec_describe_statement(statement->describe_node);
    if (list) {
        /* Success resule. */
        result->success = true;
        result->data = list;
        result->message = dstrdup("Describe executed successfully.");
        db_log(SUCCESS, "Describe statement is executed successfully.");
    }
}

/*Show tables Statment*/
static void statement_show(Statement *statement, DBResult *result) {
    assert_true(statement->statement_type == SHOW_STMT, 
               "System error, show statmement type error."); 
    exec_show_statement(statement->show_node, result);
}

/* Execute statment. */
static void exec_statement(Statement *statement, DBResult *result) {
    /* Execute statment */
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
            case ALTER_TABLE_STMT:
                statement_alter_table(statement, result);
                break;
            default:
                UNEXPECTED_VALUE(statement->statement_type);
                break;
        }
    } 

    /* Calulate duration. */
    result->end_time = clock();
    result->duration = (double)(result->end_time - result->start_time) / CLOCKS_PER_SEC;
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

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    List *result_list = create_list(NODE_DB_RESULT);
    List *statements = NULL;

    /* Check empty sql. */
    if (!is_empty(sql)) {
        /* Catch Error. */
        if (setjmp(errEnv) == 0) {
            statements = parse(sql);
            /* Execute each statement. */
            ListCell *lc;
            foreach (lc, statements) {
                DBResult *result = new_db_result();
                append_list(result_list, result);
                Statement *statement = lfirst(lc);
                exec_statement(statement, result);
            }
        } else {
            /* Catch routine. */
            /* If the set is empty, which means sql syntax error, put an error result to the set. */
            if (list_empty(result_list)) {
                DBResult *err_result = new_db_result();
                /* For error catch, result is false. */
                err_result->success = false;
                append_list(result_list, err_result);
            }

            /* If last result is error, it lack duration, make up. */
            DBResult *last_result = lfirst(last_cell(result_list));
            if (last_result->success == false) {
                /* Calulate duration. */
                last_result->end_time = clock();
                last_result->duration = (double)(last_result->end_time - last_result->start_time) / CLOCKS_PER_SEC;
                db_log(INFO, "Duration: %lfs", last_result->duration);
            }
        }
    } else {
        DBResult *empty_result = new_db_result();
        empty_result->success = false;
        empty_result->message = format("Input nothing");
        append_list(result_list, empty_result);
    }

    json_list(result_list);

    /* Free statements.*/
    free_list_deep(statements);

    /* Free result_set. */
    free_list_deep(result_list);

    /* Commit transction manually. */
    auto_commit_transaction();

    /* Calulate whole duration. */
    gettimeofday(&end_time, NULL);
    db_log(INFO, "Whole duration: %lfs", time_span(end_time, start_time));
}
