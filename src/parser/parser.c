#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parser.h"
#include "mmu.h"
#include "data.h"
#include "common.h"
#include "utils.h"
#include "log.h"
#include "y.tab.h"
#include "intpr.h"
#include "asserts.h"

typedef void* yyscan_t;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yylex_init(yyscan_t *scanner);
extern int yylex(yyscan_t scanner);
extern YY_BUFFER_STATE yy_scan_string(char *str, yyscan_t scanner);
extern int yyparse(void *scanner, List *states);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer, yyscan_t scanner);
extern int yylex_destroy(yyscan_t *scanner);


/* Parse sql and generate statement list. */
List *parse(char *sql) {
    if (sql == NULL)
        return NULL;

    trim(sql); /* Remove space characters, includes '\f', '\n', '\r', '\t', '\v'*/
    db_log(DEBUGER, "Execute sql: %s", sql);

    size_t size = strlen(sql);
    char buff[size + 1];
    sprintf(buff, "%s%c", sql, '\n');

    yyscan_t scanner;
    yylex_init(&scanner);

    YY_BUFFER_STATE buffer = yy_scan_string(buff, scanner);

    List *states = create_list(NODE_STATEMENT);

    if (yyparse(scanner, states) == 0) {
        yy_delete_buffer(buffer, scanner);
        yylex_destroy(scanner);
        return states;
    } else {
        yy_delete_buffer(buffer, scanner);
        yylex_destroy(scanner);
        return NULL;
    }
}
