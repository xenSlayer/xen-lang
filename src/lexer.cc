#include <iostream>

#include "../include/token.h"
#include "../lexer/lex.yy.c"

const char *pathToFile = "C:\\Users\\kiran\\Desktop\\xen-lang\\test\\test.xen";

extern int yylex();
extern int yylineno;
extern char *yytext;
extern FILE *yyin, *yyout;

class ILexer {
public:
  virtual Token get_token() = 0;
};

// impl
class Lexer : ILexer {
public:
  Token get_token() override {
    yyin = fopen(pathToFile, "r");
    int curToken = yylex();
    if (curToken) {
      Token token = Token(yytext, curToken, yylineno);
      return token;
    } else {
      fclose(yyin);
      delete yytext;
      delete yyin;
      delete yyout;
    }
  }
};
