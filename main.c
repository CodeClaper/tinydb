#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "defs.h"
#include "token.h"
#include "input.h"
#include "stmt.h"

char *data_dir;
InputBuffer *input_buffer;

// init variable
void init_variable() {
    data_dir = "./data/";
    input_buffer = malloc(sizeof(InputBuffer));
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
        read_input(input_buffer);
        if(meta_statment(input_buffer->input))
            continue;
        Statement *statement = parse(input_buffer->input);
        if (statement == NULL)
            continue;
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
        }
    }
    return 0;
}
