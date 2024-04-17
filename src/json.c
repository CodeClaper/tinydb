/*
 * =============================================== Json output Module ===============================================================
 * DBResult is the json format that db finally output, include flows:
 * [success]  Whether execution result is successful or unsuccessful, its value is true or false.
 * [message]  Output message to client.
 * [data]     Query data, only used when select statement.
 * [rows]     The number of rows affected.
 * [duration] The execution time.
 * =============================================================================================================================
 * */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "data.h"
#include "mmu.h"
#include "json.h"
#include "log.h"
#include "utils.h"
#include "meta.h"
#include "copy.h"
#include "free.h"
#include "trans.h"
#include "select.h"
#include "asserts.h"
#include "session.h"

/* Handle duplicate Key. */
static void handle_dulicate_key(Row *row);

/* Send out row. */
static void db_send_row_json(Row *row);

/* Generate new db result. */
DBResult *new_db_result() {
    /* New DbResule and initialize it. */
    DBResult *result = instance(DBResult);
    result->success = false;
    result->message = NULL;
    result->data = NULL;
    result->rows = 0;
    result->duration = 0;
    return result;
}

/* Generate new db result set. */
DBResultSet *new_db_result_set() {
    DBResultSet *result_set = instance(DBResultSet);
    result_set->size = 0;
    result_set->set = db_malloc(0, "pointer");
    return result_set;
}

/* Add db result to set. */
void add_db_result(DBResultSet *result_set, DBResult *result) {
    result_set->set = db_realloc(result_set->set, sizeof(DBResult *) * (result_set->size + 1));
    result_set->set[result_set->size++] = result;
}

/* Send out subrow. */
static void db_send_subrow_json(Row *subrow) {
    if (subrow == NULL || row_is_deleted(subrow)) 
        db_send("null");
    else {
        Row *slimrow = copy_row_without_reserved(subrow);
        db_send_row_json(slimrow);
        free_row(slimrow);
    }
}

/* Send out row. */
static void db_send_row_json(Row *row) {
    /* Handler duplacate key. */
    handle_dulicate_key(row);
    db_send("{ ");
    uint32_t i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        switch (key_value->data_type) {
            /* Specially deal with T_REFERENCE data. */
            case T_REFERENCE: {
                db_send("\"%s\": ", key_value->key);
                Refer *refer = (Refer *)key_value->value;
                assert_not_null(refer, "Try to get Reference type value fail.\n");
                Row *subrow = define_row(refer);
                db_send_subrow_json(subrow);
                free_row(subrow);
                break;
            }
            case T_ROW: {
                db_send("\"%s\": ", key_value->key);
                Row *subrow = key_value->value;
                db_send_subrow_json(subrow);
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
            db_send_row_json(row);
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
        db_send("[");
        uint32_t i;
        for(i = 0; i < map_list->size; i++) {
            Map *map = map_list->data[i];
            db_send_map(map);
            if (i < map_list->size - 1)
                db_send(", ");
        }
        db_send("]");
    }
    db_send(", \"duration\": %lf }", result->duration);
}

/* Handle duplicate Key. */
static void handle_dulicate_key(Row *row) {
    uint32_t times = 0;
    uint32_t i,j;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *first = row->data[i];
        for (j = i + 1; j < row->column_len; j++) {
            KeyValue *second = row->data[j];
            if (streq(second->key, first->key)) {
                db_free(second->key);
                second->key = format("%s(%d)", first->key, ++times);
            }
        } 
    }
}

/* Send out db execution result. */
void db_send_result(DBResult *result) {
    switch (result->stmt_type) {
        case SELECT_STMT:
            db_send_select_result(result);
            break;
        case INSERT_STMT:
        case DELETE_STMT:
        case UPDATE_STMT:
            db_send_nondata_rows_result(result);
            break;
        case SHOW_STMT:
        case DESCRIBE_STMT:
            db_send_map_list(result);
            break;
        default:
            db_send_nondata_result(result);
            break;
    }
}

/* Send out db execution result set. */
void db_send_result_set(DBResultSet *result_set) {
    db_send(result_set->size > 1 ? "[" : "");
    uint32_t i;
    for (i = 0; i < result_set->size; i++) {
        db_send_result(result_set->set[i]);
        if (i < result_set->size - 1)
            db_send(", ");
    }
    db_send(result_set->size > 1 ? "]\n" : "\n");
}
