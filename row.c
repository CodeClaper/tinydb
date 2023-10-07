#include "data.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// check if a key exist in select result rows
static bool check_if_exists(uint32_t key, SelectResult *select_result) {
    for(uint32_t i = 0; i < select_result->row_size; i++) {
        Row *row = *(select_result->row + i);
        if (row->key == key)
            return true;
    }
    return false;
}

// Merge two select result 
SelectResult *merge(SelectResult *first_result, SelectResult *sec_result) {
    for(uint32_t i = 0; i < sec_result->row_size; i++) {
        Row *row = *(sec_result->row + i);
        uint32_t key = row->key;
        if (!check_if_exists(key, first_result)) {
            first_result->row = realloc(first_result->row, sizeof(Row *) * (first_result->row_size + 1));
            Row *new_row = malloc(sizeof(Row));
            memcpy(new_row, row, sizeof(Row));
            *(first_result->row + first_result->row_size) = new_row;
            first_result->row_size++;
        }
    }
    return first_result;
}

// Reduce two select result 
SelectResult *reduce(SelectResult *first_result, SelectResult *sec_result){
    SelectResult *return_result = malloc(sizeof(SelectResult));
    return_result->row_size = 0;
    return_result->table_name = first_result->table_name;
    return_result->row = malloc(0);
    for(uint32_t i = 0; i < sec_result->row_size; i++) {
        Row *row = *(sec_result->row + i);
        uint32_t key = row->key;
        if (check_if_exists(key, first_result)) {
            return_result->row = realloc(return_result->row, sizeof(Row *) * (return_result->row_size + 1));
            Row *new_row = malloc(sizeof(Row));
            memcpy(new_row, row, sizeof(Row));
            *(return_result->row + return_result->row_size) = new_row;
            return_result->row_size++;
        }
    }
    return return_result;
}
