%{
#include <stdio.h>
#include <string.h>
#include "intpr.h"
#include "y.tab.h"
%}
%%
create      return CREATE;
select      return SELECT;
insert      return INSERT;
update      return UPDATE;
delete      return DELETE;
from        return FROM;
table       return TABLE;
where       return WHERE;
and         return AND;
or          return OR;
into        return INTO;
values      return VALUES;
primary     return PRIMARY;
key         return KEY;
int         return INT;
string      return STRING;
date        return DATE;
bit         return BIT;
timestamp   return TIMESTAMP;
[*]         return ALL;
[,]         return COMMA;
[;]         return SEMICOLON;
[(]         return LEFTPAREN;
[)]         return RIGHTPAREN;
[=]         return EQ;
[>]         return GT;
[<]         return LT;
[']         return QUOTE;
"!="        return NE;
">="        return GE;
"<="        return LE;
"max"       return MAX;
"min"       return MIN;
"SUM"       return SUM;
"count"     return COUNT;
"average"   return AVERAGE;
[a-zA-Z][a-zA-Z0-9]*    { yylval.s_value = strdup(yytext); return IDENTIFIER;} 
[0-9]+                  { yylval.i_value = atoi(yytext); return INTVALUE;}
[a-zA-Z0-9]+          { yylval.s_value = strdup(yytext); return STRINGVALUE;} 
\n          return NL;
[ \t]   /* igonore space */
%%
