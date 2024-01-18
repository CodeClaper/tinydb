#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "mmu.h"
#include "data.h"
#include "common.h"
#include "utils.h"
#include "intpr.h"
#include "log.h"
#include "y.tab.h"
#include "asserts.h"

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yylex(void);
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern int yyparse(ASTNode *node);

Statement *new_statement(ASTNode *node) {

    assert_not_null(node, "ASTNode not allowed to be NULL. \n");

    Statement *statement = db_malloc(sizeof(Statement), SDT_STATEMENT);
    statement->ast_node = node;
    statement->statement_type = node->statement_type;

    return statement;
}

/* Parse sql. */
Statement *parse(char *sql) {
    if (sql == NULL)
        return NULL;

    trim(sql); /* Remove space characters, includes '\f', '\n', '\r', '\t', '\v'*/
    db_log(DEBUGER, "Execute sql: %s", sql);

    size_t size = strlen(sql);
    char buff[size + 1];
    sprintf(buff, "%s%c", sql, '\n');
    YY_BUFFER_STATE buffer = yy_scan_string(buff);

    ASTNode *node = db_malloc(sizeof(ASTNode), SDT_AST_NODE);

    return yyparse(node) == 0 ? new_statement(node) : NULL;
}
