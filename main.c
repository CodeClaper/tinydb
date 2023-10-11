#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "defs.h"
#include "token.h"
#include "input.h"
#include "stmt.h"
#include "free.h"
#include <readline/readline.h>
#include <readline/history.h>

char *data_dir;

// init variable
void init_variable() {
    data_dir = "/home/zc/data/";
}

// print prompt
void print_prompt() { 
    printf("tinydb > "); 
}

//Execute meta stament.
bool meta_statment(char *input) {
    if (strcmp("exit", input) == 0) {
        printf("Goodbye.\n");
        exit(EXIT_SUCCESS);
    } else if (strcmp("clear", input) == 0 || strcmp("cls", input) == 0) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        return true;
    } else if (strcmp("history", input) == 0) {
        HIST_ENTRY** hist_entry = history_list();
        if (hist_entry == NULL) {
            fprintf(stdout, "Empty.\n");
            return true;
        }
        HIST_ENTRY *hist;
        for (uint32_t i = 0; (hist = *(hist_entry + i)) != NULL; i++ ) {
            fprintf(stdout, "%d\t%s\n", (i + 1), hist->line);
        }
        return true;
    }
    return false;
}

int main(void) {
    init_variable();
    while(true) {
        char *sql = readline("tinydb > ");
        if (is_empty(sql)) {
            add_history(sql);
            free(sql);
            continue;
        }
        if(meta_statment(sql)) {
            add_history(sql);
            free(sql);
            continue;
        }
        Statement *statement = parse(sql);
        if (statement == NULL) {
            add_history(sql);
            free(sql);
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
        add_history(sql);
        free(sql);
    }
    return 0;
}
