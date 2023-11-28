#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "mem.h"
#include "data.h"
#include "common.h"
#include "misc.h"
#include "utils.h"
#include "intpr.h"
#include "y.tab.h"

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yylex(void);
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern int yyparse(ASTNode *node);

Statement *adapt(ASTNode *node) {
    if (node == NULL)
        return NULL;
    Statement *statement = db_malloc2(sizeof(Statement), "Statement");
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
        case SHOW_STMT:
            statement->statement_type = STMT_SHOW;
            break;
    }
    statement->ast_node = node;
    return statement;
}

/* Parse token. */
Statement *parse(char *input) {
    if (input == NULL)
        return NULL;
    /* Remove space characters, includes '\f', '\n', '\r', '\t', '\v'*/
    trim(input);
    printf("input sql:  %s\n", input);
    size_t size = strlen(input);
    char buff[size + 1];
    sprintf(buff, "%s%c", input, '\n');
    YY_BUFFER_STATE buffer = yy_scan_string(buff);
    ASTNode *node = db_malloc2(sizeof(ASTNode), "ASTNode");
    if (yyparse(node) == 0) 
        return adapt(node);
    else
        return NULL;
    
}
