%{
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "mmu.h"
#include "utils.h"
#include "intpr.h"
#include "log.h"
#include "y.tab.h"
int lineno = 1;
int yyerror(void *scanner, List *states ,const char *s);
int yylex(void *);

/* macro to save the text and return a token */
#define TOK(name) { return name; }
%}

%option caseless
%option reentrant

%%
BEGIN                   return BEGINN;
COMMIT                  return COMMIT;
ROLLBACK                return ROLLBACK;
CREATE                  return CREATE;
DROP                    return DROP;
SELECT                  return SELECT;
INSERT                  return INSERT;
UPDATE                  return UPDATE;
DELETE                  return DELETE;
DESC                    return DESCRIBE;
DESCRIBE                return DESCRIBE;
FROM                    return FROM;
TABLE                   return TABLE;
WHERE                   return WHERE;
LIKE                    return LIKE;
IN                      return IN;
LIMIT                   return LIMIT;
SHOW                    return SHOW;
TABLES                  return TABLES;
AS                      return AS;
AND                     return AND;
OR                      return OR;
NOT                     return NOT;
INTO                    return INTO;
SET                     return SET;
VALUES                  return VALUES;
PRIMARY                 return PRIMARY;
KEY                     return KEY;
UNIQUE                  return UNIQUE;
DEFAULT                 return DEFAULT;
REFERENCES              return REFERENCES;
CHECK                   return CHECK;
FOREIGN                 return FOREIGN;
COMMENT                 return COMMENT;
ALTER                   return ALTER;
COLUMN                  return COLUMN;
ADD                     return ADD;
CHANGE                  return CHANGE;
BEFORE                  return BEFORE;
AFTER                   return AFTER;
INT                     return INT;
LONG                    return LONG;
CHAR                    return CHAR;
VARCHAR                 return VARCHAR;
FLOAT                   return FLOAT;
DOUBLE                  return DOUBLE;
STRING                  return STRING;
DATE                    return DATE;
BOOL                    return BOOL;
TIMESTAMP               return TIMESTAMP;
NULL                    return NULLX;
SYSTEM                  return SYSTEM;
MEMORY                  return MEMORY;
CONFIG                  return CONFIG;
[-+*/(),.;{}\[\]]	    return yytext[0];
[=]                     return EQ;
[>]                     return GT;
[<]                     return LT;
"!="                    return NE;
">="                    return GE;
"<="                    return LE;
MAX                     return MAX;
MIN                     return MIN;
SUM                     return SUM;
COUNT                   return COUNT;
AVG                     return AVG;
REF                     return REF;
TRUE                    return TRUE;
FALSE                   return FALSE;
[a-zA-Z][a-zA-Z0-9_]*   { yylval.strVal = db_strdup(yytext); return IDENTIFIER;} 
`[a-zA-Z][a-zA-Z0-9_]*` { 
                            yylval.strVal = replace_all(yytext, "`", ""); 
                            return IDENTIFIER;
                        } 
[0-9]+                  { yylval.intVal = parse_long(yytext); return INTVALUE;}
[0-9]+	|
[0-9]+"."[0-9]* |
"."[0-9]*	            { yylval.floatVal = parse_double(yytext); return FLOATVALUE; }
'[^'\n]*'	            { if (strcmp(yytext, "''") == 0) 
                          { 
                              yylval.strVal = db_strdup(" ");
                          } else 
                          {
                              char *str = strtok(yytext, "\'");  
                              yylval.strVal = db_strdup(str);
                          } 
                          return STRINGVALUE;
                        } 
'[^'\n]*$	            { yyerror(yyscanner, NULL, "Unterminated string");  return YYerror;}
\n                      { lineno++; return NL;}
[ \t]                   /* igonore space */
"--".*$		;	        /* comment */
%%

int yyerror(void *scanner, List *states, const char *s) {
    struct yyguts_t * yyg = (struct yyguts_t*)scanner;
	db_log(ERROR, "Sql syntax error near [%s].", yyg->yytext_r);
    return 0;
}
