#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "row.h"
#include "mem.h"
#include "data.h"
#include "copy.h"
#include "opr.h"
#include "table.h"
#include "index.h"

// check if a key exist in select result rows
static bool check_if_exists(void *key, SelectResult *select_result) {
    Table *table = open_table(select_result->table_name);
    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(table->meta_table);
    for(uint32_t i = 0; i < select_result->row_size; i++) {
        Row *row = *(select_result->row + i);
        if (equal(row->key, key, primary_key_meta_column->column_type))
            return true;
    }
    return false;
}

// Merge two select result 
SelectResult *merge(SelectResult *first_result, SelectResult *sec_result) {
    for(uint32_t i = 0; i < sec_result->row_size; i++) {
        Row *row = *(sec_result->row + i);
        void* key = row->key;
        if (!check_if_exists(key, first_result)) {
            first_result->row = db_realloc(first_result->row, sizeof(Row *) * (first_result->row_size + 1));
            *(first_result->row + first_result->row_size) = copy_row(row);
            first_result->row_size++;
        }
    }
    return first_result;
}

// Reduce two select result 
SelectResult *reduce(SelectResult *first_result, SelectResult *sec_result){
    SelectResult *return_result = db_malloc(sizeof(SelectResult));
    return_result->row_size = 0;
    return_result->table_name = db_malloc(strlen(first_result->table_name) + 1);
    strcpy(return_result->table_name, first_result->table_name);
    return_result->row = db_malloc(0);
    for(uint32_t i = 0; i < sec_result->row_size; i++) {
        Row *row = *(sec_result->row + i);
        void *key = row->key;
        if (check_if_exists(key, first_result)) {
            return_result->row = db_realloc(return_result->row, sizeof(Row *) * (return_result->row_size + 1));
            *(return_result->row + return_result->row_size) = copy_row(row);
            return_result->row_size++;
        }
    }
    return return_result;
}
