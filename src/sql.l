%{
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "intpr.h"
#include "ret.h"
#include "y.tab.h"
#include "log.h"
int lineno = 1;
int yyerror(const char *s);
int yylex();
%}
%%
begin                   return BEGINN;
commit                  return COMMIT;
create                  return CREATE;
drop                    return DROP;
select                  return SELECT;
insert                  return INSERT;
update                  return UPDATE;
delete                  return DELETE;
describe                return DESCRIBE;
from                    return FROM;
table                   return TABLE;
where                   return WHERE;
show                    return SHOW;
tables                  return TABLES;
and                     return AND;
or                      return OR;
into                    return INTO;
set                     return SET;
values                  return VALUES;
primary                 return PRIMARY;
key                     return KEY;
int                     return INT;
long                    return LONG;
char                    return CHAR;
float                   return FLOAT;
double                  return DOUBLE;
string                  return STRING;
date                    return DATE;
bool                    return BOOL;
timestamp               return TIMESTAMP;
not                     return NOT;
null                    return NULLX;
system                  return SYSTEM;
memory                  return MEMORY;
config                  return CONFIG;
[*]                     return ALL;
[,]                     return COMMA;
[;]                     return SEMICOLON;
[(]                     return LEFTPAREN;
[)]                     return RIGHTPAREN;
[=]                     return EQ;
[>]                     return GT;
[<]                     return LT;
[']                     return QUOTE;
[.]                     return POINT;
"!="                    return NE;
">="                    return GE;
"<="                    return LE;
max                     return MAX;
min                     return MIN;
sum                     return SUM;
count                   return COUNT;
avg                     return AVG;
true                    return TRUE;
false                   return FALSE;
[a-zA-Z][a-zA-Z0-9_]*   { yylval.s_value = strdup(yytext); return IDENTIFIER;} 
[0-9]+                  { yylval.i_value = atoi(yytext); return INTVALUE;}
[0-9]+	|
[0-9]+"."[0-9]* |
"."[0-9]*	            { yylval.f_value = atof(yytext); return FLOATVALUE; }
'[^'\n]*'	            { if (strcmp(yytext, "''") == 0) { yylval.s_value = strdup(" ");} else {char *str = strtok(yytext, "\'");  yylval.s_value =  strdup(str);} return STRINGVALUE;} 
'[^'\n]*$	            { yyerror("Unterminated string");  return YYerror;}
\n                      { lineno++; return NL;}
[ \t]           /* igonore space */
"--".*$		;	/* comment */
%%

int yyerror(const char *s) {
    DBResult *result = new_db_result();
	error_result(result, EXECUTE_SQL_ERROR ,"Sql syntax error near '%s' ", yytext);
    db_send_result(result);
    return 0;
}
