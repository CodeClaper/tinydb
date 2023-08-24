#include "token.h"
#include "common.h"
#include "misc.h"
#include "sql/intpr.h"
#include "sql/y.tab.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yylex(void);
extern int yyparse(void);
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

Statement *adapt(ASTNode *node) {
    if (node == NULL)
        return NULL;
    Statement *statement = malloc(sizeof(Statement));
    if (statement == NULL)
        MALLOC_ERROR;
    switch(node->statement_type) {
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
    }
    statement->ast_node = node;
    return statement;
}

// parse token
Statement *parse(char *input) {
    char *state = malloc(strlen(input) + 1);
    sprintf(state, "%s%c", input, '\n');
    YY_BUFFER_STATE buffer = yy_scan_string(state);
    if(yyparse() == 0) {
        ASTNode *node = get_ast_node();
        return adapt(node);
    } else {
        return NULL;
    }
}
