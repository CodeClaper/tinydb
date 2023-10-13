#include "output.h"
#include "data.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 1024

//Print
static void print(Output *out, char *word, uint32_t *buff_size) {
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
}  

//Get key string
static char *get_row_key_str(char *ori_key) {
    size_t len = strlen(ori_key) + 3;
    char *key = malloc(len);
    memset(key, 0, len);
    sprintf(key, "\"%s\"", ori_key);
    return key;
}

//Get value string.
static char *get_row_value_str(KeyValue *key_value) {
    switch(key_value->data_type) {
        case T_INT: 
            {
                char *s = malloc(100);
                memset(s, 0, 100);
                sprintf(s, "%d", *(uint32_t *)key_value->value);
                return s;
            }
        case T_STRING:
            {
                return strdup((char *)key_value->value);
            }
        case T_FLOAT: 
            {
                char *s = malloc(100);
                memset(s, 0, 100);
                sprintf(s, "%f", *(float *)key_value->value);
                return s;
            }
        case T_DOUBLE:
            {
                char *s = malloc(100);
                memset(s, 0, 100);
                sprintf(s, "%f", *(double *)key_value->value);
                return s;
            }
        default:
            fprintf(stdout, "not support data type");
    }
    return NULL;
}

//Genetate output.
void put_select_result(Output *out_put, SelectResult *select_result, QueryParam *query_param) {
    uint32_t buff_size = BUFF_SIZE;
    print(out_put, "[", &buff_size);
    for (uint32_t i = 0; i < select_result->row_size; i++) {
        Row *row = *(select_result->row + i);
        print(out_put, "{", &buff_size); 
        for (uint32_t j = 0; j < row->column_len; j++) {
            KeyValue *key_value = *(row->data + j);
            char *key = get_row_key_str(key_value->key);
            char *value = get_row_value_str(key_value);
            print(out_put, key, &buff_size);
            print(out_put, value, &buff_size);
            free(key);
            free(value);
            if (j < row->column_len - 1) 
                print(out_put, ", ", &buff_size);
        }
        print(out_put, "}", &buff_size); 
        if (i < select_result->row_size - 1)
            print(out_put, ", ", &buff_size);
    }
    print(out_put, "]", &buff_size);
}
