/*
 * =============================================== Result Module ===============================================================
 * DBResult is the json format that db finally output, include flows:
 * [status]   The status is statement execution result.
 * [success]  Whether execution result successful or fail.
 * [message]  Output message.
 * [data]     Query data.
 * [rows]     The number of rows affected.
 * [duration] The execution time.
 * =============================================================================================================================
 * */

#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "data.h"
#include "mmu.h"
#include "ret.h"
#include "log.h"
#include "meta.h"
#include "copy.h"
#include "free.h"
#include "trans.h"
#include "select.h"
#include "asserts.h"
#include "session.h"

/* Generate new db result. */
DBResult *new_db_result() {

    /* New DbResule and initialize it. */
    DBResult *result = db_malloc(sizeof(DBResult), SDT_DB_RESULT);
    result->status = EXECUTE_FAIL;
    result->success = false;
    result->message = NULL;
    result->data = NULL;
    result->rows = 0;
    result->duration = 0;

    return result;
}

/* Success resule. */
void success_result(DBResult *result, char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char buff[BUFF_SIZE];
    vsprintf(buff, format, ap);
    result->status = EXECUTE_SUCCESS;
    result->success = true;
    result->message = db_strdup(buff);
    db_info(buff);
    va_end(ap);
}

/* Error result. */
void error_result(DBResult *result, ExecuteStatus status, char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char buff[BUFF_SIZE];
    vsprintf(buff, format, ap);
    result->status = status;
    result->success = false;
    result->message = db_strdup(buff);
    db_error("%s", buff);
    va_end(ap);
}

/* Send out row. */
static void db_send_row(Row *row) {
    db_send("{ ");
    int i = 0;
    for(i =0; i <row->column_len; i++) {

        KeyValue *key_value = *(row->data + i);
        switch (key_value->data_type) {
            case T_REFERENCE: {
                db_send("\"%s\": ", key_value->key);
                Refer *refer = (Refer *) key_value->value;
                assert_not_null(refer, "Try to get Reference type value fail.\n");
                Row *sub_row = define_row(refer);
                if (row_is_deleted(sub_row)) 
                    db_send("null");
                else {
                    Row *sim_row = copy_row_without_reserved(sub_row);
                    db_send_row(sim_row);
                    free_row(sim_row);
                }
                free_row(sub_row);
                break;
            }
            default: {
                char *key_value_pair = get_key_value_pair_str(key_value->key, key_value->value, key_value->data_type);
                db_send(key_value_pair);
                db_free(key_value_pair);
                break;
            }
        }

        /* split with ',' */
        if (i < row->column_len - 1) 
            db_send(", ");
    }
    db_send(" }");
}

/* Send out map result. */
static void db_send_map(Map *map) {
    db_send("{ ");
    int i = 0;
    for(i =0; i <map->size; i++) {
        KeyValue *key_value = *(map->body + i);

        char *key_value_pair = get_key_value_pair_str(key_value->key, key_value->value, key_value->data_type);
        db_send(key_value_pair);
        db_free(key_value_pair);

        /* split with ',' */
        if (i < map->size - 1) 
            db_send(", ");
    }
    db_send(" }");
}

/* Send out db select execution result. */
static void db_send_select_result(DBResult *result) {
    db_send("{ \"status\": %d, \"success\": %s, \"message\": \"%s\"",
            result->status, result->success ? "true" : "false", result->message);

    if (result->success) {
        db_send(", \"data\": ");
        SelectResult *select_result = result->data;
        select_result && select_result->row_size == 1 ? db_send("") : db_send("[");
        int i;
        for(i = 0; i < select_result->row_size; i++) {
            /* Send out row. */
            Row *row = select_result->rows[i];
            db_send_row(row);

            if (i < select_result->row_size - 1)
                db_send(", ");
        }
        select_result && select_result->row_size == 1 ? db_send("") : db_send("]");

        db_send(", \"rows\": %d", result->rows);
    }
    db_send(", \"duration\": %lf }\n", result->duration);
}

/* Send out db none data result. */
static void db_send_nondata_rows_result(DBResult *result) {
    db_send("{ \"status\": %d, \"success\": %s, \"message\": \"%s\", \"rows\": %d,\"duration\": %lf }\n", 
            result->status, result->success ? "true" : "false", result->message, result->rows, result->duration);
}

/* Send out db none data result. */
static void db_send_nondata_result(DBResult *result) {
    db_send("{ \"status\": %d, \"success\": %s, \"message\": \"%s\", \"duration\": %lf }\n", 
            result->status, result->success ? "true" : "false", result->message, result->duration);
}

/* Send out db show tables result. */
static void db_send_map_list(DBResult *result) {
    MapList *map_list = (MapList *)result->data;
    db_send("{ \"status\": %d, \"success\": %s, \"message\": \"%s\", \"data\": ",
            result->status, result->success ? "true" : "false", result->message);
    map_list->size == 1 ? db_send("") : db_send("[");
    uint32_t i = 0;
    for(i = 0; i < map_list->size; i++) {
        Map *map = map_list->data[i];
        db_send_map(map);
        if (i < map_list->size - 1)
            db_send(", ");
    }
    map_list->size == 1 ? db_send("") : db_send("]");
    db_send(", \"duration\": %lf }\n", result->duration);
}

/* Send out db execution result. */
void db_send_result(DBResult *result) {
    switch (result->stmt_type) {
        case SELECT_STMT:
            db_send_select_result(result);
            break;
        case SHOW_STMT:
        case DESCRIBE_STMT:
            db_send_map_list(result);
            break;
        case DELETE_STMT:
            db_send_nondata_rows_result(result);
            break;
        default:
            db_send_nondata_result(result);
            break;
    }
}
