#include "data.h"
#include "type.h"
#include "mmu.h"

/* Generate new KeyValue instance. */
KeyValue *new_key_value(char *key, void *value, DataType data_type) {
    KeyValue *key_value = instance(KeyValue);
    key_value->key = key;
    key_value->value = value;
    key_value->data_type = data_type;
    key_value->is_array = false;
    return key_value;
}

/* Generate new row instance. */
Row *new_row(void *key, char *table_name, uint32_t column_len) {
    Row *row = instance(Row);
    row->key = key;
    row->table_name = table_name;
    row->column_len = column_len;
    row->data = db_malloc(sizeof(KeyValue *) * column_len, "pointer");
    return row;
}

/* Generate new ArrayValue instance. */
ArrayValue *new_array_value(DataType data_type, uint32_t size) {
    ArrayValue *array_value = instance(ArrayValue);
    array_value->type = data_type;
    array_value->size = size;
    array_value->set = db_malloc(sizeof(void *) * size, "pointer");
    return array_value;
}

/* Generate new select result structure. */
SelectResult *new_select_result(char *table_name) {
    SelectResult *select_result = instance(SelectResult);
    select_result->row_size = 0;
    select_result->table_name = table_name ? db_strdup(table_name) : NULL;
    select_result->range_variable = NULL;
    select_result->rows = create_list(NODE_ROW);
    select_result->derived = NULL;
    select_result->last_derived = false;
    return select_result;
}

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

