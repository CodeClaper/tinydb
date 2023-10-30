#include "data.h"
#include "token.h"
#include "common.h"
#include "misc.h"
#include "intpr.h"
#include "y.tab.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yylex(void);
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern int yyparse(ASTNode *node);

Statement *adapt(ASTNode *node) {
    if (node == NULL)
        return NULL;
    Statement *statement = malloc(sizeof(Statement));
    if (statement == NULL)
        MALLOC_ERROR;
    switch(node->statement_type) {
        case CREATE_TABLE_STMT:
            statement->statement_type = STMT_CREATE_TABLE;
            break;
        case SELECT_STMT:
            statement->statement_type = STMT_SELECT;
            break;
        case INSERT_STMT:
            statement->statement_type = STMT_INSERT;
            break;
        case UPDATE_STMT:
            statement->statement_type = STMT_UPDATE;
            break;
        case DELETE_STMT:
            statement->statement_type = STMT_DELETE;
            break;
        case DESCRIBE_STMT:
            statement->statement_type = STMT_DESCRIBE;
            break;
        case SHOW_TABLES_STMT:
            statement->statement_type = STMT_SHOW_TABLES;
            break;
    }
    statement->ast_node = node;
    return statement;
}

// parse token
Statement *parse(char *input) {
    if (input == NULL)
        return NULL;
    char *state = malloc(strlen(input) + 2);
    memset(state, 0, strlen(input) + 2);
    sprintf(state, "%s%c", input, '\n');
    YY_BUFFER_STATE buffer = yy_scan_string(state);
    ASTNode *node = malloc(sizeof(ASTNode));
    memset(node, 0, sizeof(ASTNode));
    if(yyparse(node) == 0) {
        free(state);
        return adapt(node);
    } else {
        free(state);
        return NULL;
    }
}
