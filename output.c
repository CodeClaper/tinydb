#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "output.h"
#include "mem.h"
#include "data.h"
#include "misc.h"


//Get key value pair string.
char *get_key_value_pair_str(char *key, void *value, DataType data_type) {
    switch(data_type) {
        case T_BOOL:
            {
                uint32_t len = strlen(key) + 4 + 100; // key len + symbol len + value len. 
                char *s = db_malloc2(len, "BOOL String value");
                sprintf(s, "\"%s\": %s", key, (*(bool *)value ? "true" : "false"));
                return s;
            }
        case T_INT: 
            {
                uint32_t len = strlen(key) + 4 + 100; // key len + symbol len + value len. 
                char *s = db_malloc2(len, "Int String value");
                sprintf(s, "\"%s\": %d", key, *(uint32_t *)value);
                return s;
            }
        case T_CHAR:
            {
                uint32_t len = strlen(key) + 6 + 1; // key len + symbol len + value len. 
                char *s = db_malloc2(len, "Char String value");
                sprintf(s, "\"%s\": \'%c\'", key, *(char *)value);
                return s;
            }
        case T_STRING:
            {
                uint32_t len = strlen(key) + 6 + strlen(value); // key len + symbol len + value len. 
                char *s = db_malloc2(len, "String value");
                sprintf(s, "\"%s\": \"%s\"", key, (char *)value);
                return s;
            }
        case T_FLOAT: 
            {
                uint32_t len = strlen(key) + 4 + 100; // key len + symbol len + value len. 
                char *s = db_malloc2(len, "Float String value");
                sprintf(s, "\"%s\": %f", key, *(float *)value);
                return s;
            }
        case T_DOUBLE:
            {
                uint32_t len = strlen(key) + 4 + 100; // key len + symbol len + value len. 
                char *s = db_malloc2(len, "Double String value");
                sprintf(s, "\"%s\": %lf", key, *(double *)value);
                return s;
            }
        case T_TIMESTAMP: 
            {
                char temp[90];
                uint32_t len = strlen(key) + 4 + 100; // key len + symbol len + value len. 
                char *s = db_malloc2(len, "Timestamp String value.");
                time_t t = *(time_t *)value;
                struct tm *tmp_time = localtime(&t);
                strftime(temp, sizeof(temp), "%Y-%m-%d %H:%M:%S", tmp_time);
                sprintf(s, "\"%s\": \"%s\"", key, temp);
                return s;
            }
        case T_DATE: 
            {
                char temp[90];
                uint32_t len = strlen(key) + 4 + 100; // key len + symbol len + value len. 
                char *s = db_malloc2(len, "Date String value.");
                time_t t = *(time_t *)value;
                struct tm *tmp_time = localtime(&t);
                strftime(temp, sizeof(temp), "%Y-%m-%d", tmp_time);
                sprintf(s, "\"%s\": \"%s\"", key, temp);
                return s;
            }
        default:
            fatal("Not support data type");
    }
    return NULL;
}

//Print out data
void print_data(Output *out, char *word) {
    uint32_t len, increase_len;
    if (out->json_data == NULL) {
        out->json_data = db_malloc2(out->buffer_size, "Output.json_data");
        sprintf(out->json_data, "%s", word);
        db_free(word);
        return;
    } 
    increase_len = strlen(word);
    len = strlen(out->json_data) + increase_len;
    if (len >= out->buffer_size) {
        out->buffer_size += BUFF_SIZE;
        char *temp = out->json_data;
        out->json_data = db_malloc2(out->buffer_size, "Output.json_data");
        sprintf(out->json_data, "%s%s" , temp, word);
        db_free(temp);
        db_free(word);
        return;
    }
    sprintf(out->json_data, "%s%s", out->json_data, word);
    db_free(word);
}  

//Print out data
void print_data_s(Output *out, char *format, char *value) {
    uint32_t len = strlen(format) +  strlen(value);
    char *msg = db_malloc2(len, "String value");
    sprintf(msg, format, value);
    print_data(out, msg);
}  

//Print out data
void print_data_d(Output *out, char *format, int value) {
    uint32_t len = strlen(format) +  100;
    char *msg = db_malloc2(len, "String value");
    sprintf(msg, format, value);
    print_data(out, msg);
}  

//Print out message
void print_message(Output *out, char *word) {
    uint32_t len, increase_len;
    if (out->message == NULL) {
        out->message = db_malloc2(out->buffer_size, "Output.message");
        sprintf(out->message, "%s", word);
        return;
    } 
    increase_len = strlen(word);
    len = strlen(out->message) + increase_len;
    if (len >= out->buffer_size) {
        out->buffer_size += BUFF_SIZE;
        char *temp = out->message;
        out->message = db_malloc2(out->buffer_size, "Output.message");
        sprintf(out->message, "%s%s" , temp, word);
        db_free(temp);
        return;
    }
    sprintf(out->message, "%s%s", out->message, word);
    db_free(word);
}  


