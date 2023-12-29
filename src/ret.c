/*
 * =============================================== Result Module ===============================================================
 * DBResult is the json format that db finally output, include flows:
 * [status]   The status is statement execution result.
 * [success]  Whether execution result successful or fail.
 * [rows]     The number of influent rows.
 * [data]     Query data.
 * [message]  Output message.
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
#include "table.h"
#include "asserts.h"
#include "session.h"

/* Generate new db result. */
DBResult *new_db_result() {

    /* New DbResule and initialize it. */
    DBResult *result = db_malloc2(sizeof(DBResult), "DBResult");
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
    result->message = strdup(buff);
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
    result->message = strdup(buff);
    db_error("%s", buff);
    va_end(ap);
}

/* Send out db select execution result. */
static void db_send_select_result(DBResult *result) {
    db_send("{\"status\": %d, \"success\": %s, \"rows\": %d, \"message\": \"%s\", \"data\": [", 
            result->status, result->success ? "true" : "false", result->rows, result->message);
    SelectResult *select_result = result->data;
    uint32_t i, j;
    for(i = 0; i < result->rows; i++) {
        Row *row = select_result->rows[i];
        Table *table = open_table(row->table_name);
        assert_not_null(table, "System error, found table '%s' fail. \n", row->table_name);
        int sys_reserved_column_size = table->meta_table->all_column_size - table->meta_table->column_size;
        db_send("{");
        for(j =0; j <row->column_len; j++) {
            KeyValue *key_value = *(row->data + j);

            /* Skip system reserved columns. */
            MetaColumn *meta_column = get_all_meta_column_by_name(table->meta_table, key_value->key);
            if (meta_column->sys_reserved) continue;

            char *key_value_pair = get_key_value_pair_str(key_value->key, key_value->value, key_value->data_type);
            db_send(key_value_pair);
            db_free(key_value_pair);

            /* split with ',' */
            if (j < row->column_len - 1 - sys_reserved_column_size) db_send(", ");
        }
        db_send("}");
        if (i < result->rows - 1) db_send(", ");
    }
    db_send("], \"duration\": %lf }\n", result->duration);
}

/* Send out db none data result. */
static void db_send_nondata_result(DBResult *result) {
    db_send("{\"status\": %d, \"success\": %s, \"rows\": %d, \"message\": \"%s\", \"duration\": %lf}\n", 
            result->status, result->success ? "true" : "false", result->rows, result->message, result->duration);
}

/* Send out db execution result. */
void db_send_result(DBResult *result) {
    switch (result->stmt_type) {
        case STMT_SELECT:
            db_send_select_result(result);
            break;
        case STMT_SHOW:
        case STMT_DESCRIBE:
            break;
        default:
            db_send_nondata_result(result);
            break;
    }
}
