%{
    /* definitions */
    #include "../include/token.h"
%}

/* %option noyywrap c++ */
%option outfile="lexer/lex.yy.c" case-insensitive yylineno noyywrap

NUMBERS [0-9]

/* rule */
%%

"def" return DEF;
"return" return RETURN;
"if" return IF;
"else" return ELSE;
"int" return INT;
"string" return STRING;
"double" return DOUBLE;

([a-zA-Z_])([a-zA-Z0-9_])* return IDENTIFIER;

{NUMBERS}+ return NUMBER;
([0-9])+(".")([0-9])+ return DOUBLE_NUMBER;

[{] return OPEN_BRACE;
[}] return CLOSE_BRACE;
[(] return OPEN_PARAN;
[)] return CLOSE_PARAN;

"+" return ADD_OP;
"-" return SUB_OP;
"*" return MUL_OP;
"/" return DIV_OP;
"=" return EQ_OP;

(:) return COLON;
(;) return SEMI_COLON;
(,) return COMMA;

#(.)+ ;

%%
