#include <iostream>

#include "../include/memory.h"
#include "../token.h"

extern int yylex();
extern int yylineno;
extern char *yytext;
extern FILE *yyin, *yyout;

int main() {
  int ntoken, vtoken;
  yyin = fopen("C:\\Users\\kiran\\Desktop\\xen-lang\\test\\test.xen", "r");
  ntoken = yylex();

  while (ntoken) {
    std::cout << ntoken << std::endl;
    std::cout << yytext << std::endl;
    ntoken = yylex();
    PrintMemoryUsage();
  }
  fclose(yyin);
  std::cin.get();
  return 0;
}
