%{
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "mmu.h"
#include "intpr.h"
#include "log.h"
#include "y.tab.h"
int lineno = 1;
int yyerror(const char *s);
int yylex();

/* macro to save the text and return a token */
#define TOK(name) { return name; }
%}

%option caseless

%%
begin                   return BEGINN;
commit                  return COMMIT;
rollback                return ROLLBACK;
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
like                    return LIKE;
in                      return IN;
limit                   return LIMIT;
show                    return SHOW;
tables                  return TABLES;
as                      return AS;
and                     return AND;
or                      return OR;
not                     return NOT;
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
null                    return NULLX;
system                  return SYSTEM;
memory                  return MEMORY;
config                  return CONFIG;
[-+*/(),.;{}\[\]]	    return yytext[0];
[=]                     return EQ;
[>]                     return GT;
[<]                     return LT;
"!="                    return NE;
">="                    return GE;
"<="                    return LE;
max                     return MAX;
min                     return MIN;
sum                     return SUM;
count                   return COUNT;
avg                     return AVG;
ref                     return REF;
true                    return TRUE;
false                   return FALSE;
[a-zA-Z][a-zA-Z0-9_]*   { yylval.strVal = db_strdup(yytext); return IDENTIFIER;} 
[0-9]+                  { yylval.intVal = atoi(yytext); return INTVALUE;}
[0-9]+	|
[0-9]+"."[0-9]* |
"."[0-9]*	            { yylval.floatVal = atof(yytext); return FLOATVALUE; }
'[^'\n]*'	            { if (strcmp(yytext, "''") == 0) { yylval.strVal = db_strdup(" ");} else {char *str = strtok(yytext, "\'");  yylval.strVal =  strdup(str);} return STRINGVALUE;} 
'[^'\n]*$	            { yyerror("Unterminated string");  return YYerror;}
\n                      { lineno++; return NL;}
[ \t]           /* igonore space */
"--".*$		;	/* comment */
%%

int yyerror(const char *s) {
	db_log(ERROR, "Sql syntax error near [%s].", yytext);
    return 0;
}
