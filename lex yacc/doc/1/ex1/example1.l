%{
#include <stdio.h>
%}

%%

stop    printf("Stop command received\n");
start   printf("Start command received\n");

%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}
