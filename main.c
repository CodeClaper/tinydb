#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "defs.h"
#include "token.h"
#include "input.h"
#include "stmt.h"
#include "free.h"

char *data_dir;

// init variable
void init_variable() {
    data_dir = "/home/zc/data/";
}

// print prompt
void print_prompt() { 
    printf("tinydb > "); 
}

bool meta_statment(char *input) {
    if (strcmp("exit", input) == 0) {
        printf("Goodbye.\n");
        exit(EXIT_SUCCESS);
    } else if (strcmp("clear", input) == 0) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        return true;
    } 
    return false;
}

int main(void) {
    init_variable();
    while(true) {
        print_prompt();
        InputBuffer *input_buffer = read_input();
        if (input_buffer->input_length == 0) {
            free_input_buffer(input_buffer);
            continue;
        }
        if(meta_statment(input_buffer->input)) {
            free_input_buffer(input_buffer);
            continue;
        }
        Statement *statement = parse(input_buffer->input);
        if (statement == NULL) {
            free_input_buffer(input_buffer);
            continue;
        }
        switch(statement->statement_type) {
            case STMT_CREATE_TABLE:
                statement_create_table(statement);
                break;
            case STMT_INSERT:
                statement_insert(statement); 
                break; 
            case STMT_SELECT:
                statement_select(statement); 
                break; 
            case STMT_UPDATE:
                statement_update(statement); 
                break; 
            case STMT_DELETE:
                statement_delete(statement); 
                break; 
            case STMT_DESCRIBE:
                statement_describe(statement);
                break;
            case STMT_SHOW_TABLES:
                statement_show_tables(statement);
                break;
        }
        free_input_buffer(input_buffer);
    }
    return 0;
}
