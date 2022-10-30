%{
#include <stdlib.h>
#include "y.tab.h"
%}

%%

[a-z]       {
                yylval.sIndex = *yytext - 'a';
                return VARIABLE;
            }

[0-9]+      {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[()=+\-*/\n] {
                return *yytext;
             }

[ \t]+      ;       /* ignore whitespace */
.           yyerror("Unknown character");

%%

