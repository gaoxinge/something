%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int sym[26];                    /* symbol table */
%}

%union {
    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index */
};

%token <iValue> INTEGER
%token <sIndex> VARIABLE

%type <iValue> expr

%left '+' '-'
%left '*' '/'

%%

program:
        program statement '\n'
        |
        ;

statement:
        expr                    { printf("%d\n", $1); }
        | VARIABLE '=' expr     { sym[$1] = $3; }
        ;

expr:
        INTEGER
        | VARIABLE              { $$ = sym[$1]; }
        | expr '+' expr         { $$ = $1 + $3; }
        | expr '-' expr         { $$ = $1 - $3; }
        | expr '*' expr         { $$ = $1 * $3; }
        | expr '/' expr         { $$ = $1 / $3; }
        | '(' expr ')'          { $$ = $2; }
        ;

%%

int yywrap() {
    return 1;
}

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main() {
    yyparse();
    return 0;
}
