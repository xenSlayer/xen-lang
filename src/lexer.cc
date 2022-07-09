#include <iostream>

#include "../include/token.h"
#include "../lexer/lex.yy.c"

const char *p2F = "C:\\Users\\kiran\\Desktop\\xen-lang\\test\\test.xen";

extern int yylex();
extern int yylineno;
extern char *yytext;
extern FILE *yyin, *yyout;

class ILexer {
public:
  virtual Token *get_token() = 0;
};

// impl
class Lexer : ILexer {

private:
  Token *token;

public:
  Lexer() { yyin = fopen(p2F, "r"); }
  ~Lexer() {
    fclose(yyin);
    delete token;
    delete yytext;
    delete yyin;
    delete yyout;
  }
  Token *get_token() override {
    int curToken = yylex();
    if (curToken) {
      Token tok = Token(yytext, curToken, yylineno);
      token = &tok;
      return token;
    }
  }
};
