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

int main(void) {
    init_variable();
    while(true) {
        print_prompt();
        read_input(input_buffer);
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
        }
        free_statement(statement);
    }
    return 0;
}
