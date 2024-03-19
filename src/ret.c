/*
 * =============================================== Result Module ===============================================================
 * DBResult is the json format that db finally output, include flows:
 * [success]  Whether execution result successful or fail.
 * [message]  Output message.
 * [data]     Query data.
 * [rows]     The number of rows affected.
 * [duration] The execution time.
 * =============================================================================================================================
 * */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
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
    result->success = false;
    result->message = NULL;
    result->data = NULL;
    result->rows = 0;
    result->duration = 0;
    return result;
}

/* Generate new db result set. */
DBResultSet *new_db_result_set() {
    DBResultSet *result_set = db_malloc(sizeof(DBResultSet), SDT_DB_RESULT_SET);
    result_set->size = 0;
    result_set->set = db_malloc(0, SDT_POINTER);
    return result_set;
}

/* Add db result to set. */
void add_db_result(DBResultSet *result_set, DBResult *result) {
    result_set->set = db_realloc(result_set->set, sizeof(DBResult *) * (result_set->size + 1));
    result_set->set[result_set->size++] = result;
}

/* Assign db result message. */
void assgin_result_message(DBResult *result, char *format, ...) {
    /* Combinate message. */
    char message[BUFF_SIZE];
    va_list ap;
    va_start(ap, format);
    vsprintf(message, format, ap);

    /* If message may be already older message, free it. */
    if (result->message) {
        db_free(result->message);
    }
    result->message = db_strdup(message);
    va_end(ap);
}

/* Send out row. */
static void db_send_row(Row *row) {
    db_send("{ ");
    int i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        switch (key_value->data_type) {
            /* Specially deal with T_REFERENCE data. */
            case T_REFERENCE: {
                db_send("\"%s\": ", key_value->key);
                Refer *refer = (Refer *)key_value->value;
                assert_not_null(refer, "Try to get Reference type value fail.\n");
                Row *sub_row = define_row(refer);
                if (sub_row == NULL || row_is_deleted(sub_row)) 
                    db_send("null");
                else {
                    Row *slim_row = copy_row_without_reserved(sub_row);
                    db_send_row(slim_row);
                    free_row(slim_row);
                }
                free_row(sub_row);
                break;
            }
            case T_ROW: {
                db_send("\"%s\": ", key_value->key);
                Row *sub_row = key_value->value;
                if (sub_row == NULL) 
                    db_send("null");
                else 
                    db_send_row(sub_row);
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
        KeyValue *key_value = map->body[i];
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
    db_send("{ \"success\": %s, \"message\": \"%s\"", result->success ? "true" : "false", result->success ? result->message : get_log_msg());
    if (result->success) {
        db_send(", \"data\": ");
        SelectResult *select_result = result->data;
        db_send("[");
        int i;
        for(i = 0; i < select_result->row_size; i++) {
            /* Send out row. */
            Row *row = select_result->rows[i];
            db_send_row(row);
            if (i < select_result->row_size - 1)
                db_send(", ");
        }
        db_send("]");
        db_send(", \"rows\": %d", result->rows);
    }
    db_send(", \"duration\": %lf }", result->duration);
}

/* Send out db none data result. */
static void db_send_nondata_rows_result(DBResult *result) {
    db_send("{ \"success\": %s, \"message\": \"%s\", \"rows\": %d,\"duration\": %lf }\n", 
             result->success ? "true" : "false", result->success ? result->message : get_log_msg(), result->rows, result->duration);
}

/* Send out db none data result. */
static void db_send_nondata_result(DBResult *result) {
    db_send("{ \"success\": %s, \"message\": \"%s\", \"duration\": %lf }", 
            result->success ? "true" : "false", result->success? result->message : get_log_msg(), result->duration);
}

/* Send out db show tables result. */
static void db_send_map_list(DBResult *result) {
    MapList *map_list = (MapList *)result->data;
    db_send("{ \"success\": %s, \"message\": \"%s\" ", result->success ? "true" : "false", result->success ? result->message : get_log_msg());
    if (result->success) {
        db_send(", \"data\": ");
        map_list->size == 1 ? db_send("") : db_send("[");
        int i;
        for(i = 0; i < map_list->size; i++) {
            Map *map = map_list->data[i];
            db_send_map(map);
            if (i < map_list->size - 1)
                db_send(", ");
        }
        map_list->size == 1 ? db_send("") : db_send("]");
    }
    db_send(", \"duration\": %lf }", result->duration);
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

/* Send out db execution result set. */
void db_send_result_set(DBResultSet *result_set) {
    db_send(result_set->size > 1 ? "[" : "");
    for (uint32_t i = 0; i < result_set->size; i++) {
        db_send_result(result_set->set[i]);
        if (i < result_set->size - 1)
            db_send(", ");
    }
    db_send(result_set->size > 1 ? "]\n" : "\n");
}
