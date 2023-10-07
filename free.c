#include "free.h"
#include <stdint.h>
#include <stdlib.h>

// free KeyValue
void free_key_value(KeyValue *key_value) {
    if (key_value != NULL) {
#ifdef DEBUG
    printf("address of key: 0x%p\n", key_value->key);
#endif
        free(key_value->key);
        if (key_value->value != NULL)
            free(key_value->value);
        free(key_value);
    } 
}

// free Row.
void free_row(Row *row) {
    if (row != NULL) {
        if (row->table_name)
            free(row->table_name);
        for(uint32_t i = 0; i < row->column_len; i++) {
            // free_key_value((KeyValue *)(row->data + i));
        }
        free(row);
    }
}

// free SelectResult.
void free_select_result(SelectResult *select_result) {
    if (select_result != NULL) {
        if (select_result->table_name != NULL)
            free(select_result->table_name);
        for(uint32_t i = 0; i < select_result->row_size; i++) {
            Row *row = *(select_result->row + i);
            free_row(row);
        }
        free(select_result);
    }
}

// free input buffer.
void free_input_buffer(InputBuffer *input_buffer) {
    if (input_buffer != NULL) {
        if (input_buffer->input != NULL)
            free(input_buffer->input);
        free(input_buffer);
    }
}
