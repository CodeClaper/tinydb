#include "output.h"
#include "data.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Get key value pair string.
char *get_key_value_pair_str(char *key, void *value, DataType data_type) {
    switch(data_type) {
        case T_BOOL:
            {
                uint32_t len = strlen(key) + 4 + 100; // key len + symbol len + value len. 
                char *s = malloc(len);
                memset(s, 0, len);
                sprintf(s, "\"%s\": %s", key, (*(bool *)value ? "true" : "false"));
                return s;
            }
        case T_INT: 
            {
                uint32_t len = strlen(key) + 4 + 100; // key len + symbol len + value len. 
                char *s = malloc(len);
                memset(s, 0, len);
                sprintf(s, "\"%s\": %d", key, *(uint32_t *)value);
                return s;
            }
        case T_STRING:
            {
                uint32_t len = strlen(key) + 6 + strlen(value); // key len + symbol len + value len. 
                char *s = malloc(len);
                memset(s, 0, len);
                sprintf(s, "\"%s\": \"%s\"", key, (char *)value);
                return s;
            }
        case T_FLOAT: 
            {
                uint32_t len = strlen(key) + 4 + 100; // key len + symbol len + value len. 
                char *s = malloc(len);
                memset(s, 0, len);
                sprintf(s, "\"%s\": %f", key, *(float *)value);
                return s;
            }
        case T_DOUBLE:
            {
                uint32_t len = strlen(key) + 4 + 100; // key len + symbol len + value len. 
                char *s = malloc(len);
                memset(s, 0, len);
                sprintf(s, "\"%s\": %lf", key, *(double *)value);
                return s;
            }
        default:
            fprintf(stdout, "not support data type");
    }
    return NULL;
}

//Print out
void print_out(Output *out, char *word, uint32_t *buff_size) {
    int len = strlen(word);
    out->len += len;
    if (out->json_data == NULL) {
        out->json_data = malloc(*buff_size);
        memset(out->json_data, 0, *buff_size);
        sprintf(out->json_data, "%s" , word);
        return;
    } 
    if (out->len >= *buff_size) {
        *buff_size += BUFF_SIZE;
        char *temp = out->json_data;
        out->json_data = malloc(*buff_size);
        memset(out->json_data, 0, *buff_size);
        sprintf(out->json_data, "%s%s" , temp, word);
        free(temp);
        return;
    }
    sprintf(out->json_data, "%s%s", out->json_data, word);
    free(word);
}  

//Genetate output.
void put_select_result(Output *out_put, SelectResult *select_result, QueryParam *query_param) {
    uint32_t buff_size = BUFF_SIZE;
    print_out(out_put, "[", &buff_size);
    for (uint32_t i = 0; i < select_result->row_size; i++) {
        Row *row = *(select_result->row + i);
        print_out(out_put, "{", &buff_size); 
        for (uint32_t j = 0; j < row->column_len; j++) {
            KeyValue *key_value = *(row->data + j);
            print_out(out_put, get_key_value_pair_str(key_value->key, key_value->value, key_value->data_type), &buff_size);
            if (j < row->column_len - 1) 
                print_out(out_put, ", ", &buff_size);
        }
        print_out(out_put, "}", &buff_size); 
        if (i < select_result->row_size - 1)
            print_out(out_put, ", ", &buff_size);
    }
    print_out(out_put, "]", &buff_size);
}
