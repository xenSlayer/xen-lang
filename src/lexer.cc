#include <cstdio>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>

#include "../include/token.h"
#include "utils.cc"

std::string pathToFile = "C:\\Users\\kiran\\Desktop\\xen-lang-"
                         "LLVM\\test\\test.xen";

class ILexer {
private:
  virtual Token *tokenizer() = 0;

public:
  virtual Token *get_token() = 0;
};

class Lexer : ILexer {
private:
  std::ifstream file;
  const std::map<unsigned int, std::string> *buffer;
  // create tokens from buffer
  Token *tokenizer() override {
    // tokenize one line at a time
    // run when parser needs next token
    std::string *identifierStr = new std::string();
    double numval;
    // loop through each line
    for (auto const &buff : *buffer) {
      // loop through each charachter
      for (int i = 0; i < buff.second.length(); i++) {
        // is space encountered then increment i
        if (buff.second[i] == ' ') {
          i++;
        }
        if (isalpha(buff.second[i])) {
          *identifierStr += buff.second[i];
          i++;
          if (isalnum(buff.second[i])) {
            *identifierStr += buff.second[i];
          }
        }
      }
    }
  }

public:
  Lexer() {
    Utils *utils = new Utils();
    buffer = utils->scanner(pathToFile);
  }

  ~Lexer() { delete buffer; }

  // gettok - Return the next token from standard input.
  // Todo convert get_token to read whole content of the file rather then
  // console content
  Token *get_token() override {

    static int LastChar = ' ';

    // Skip any whitespace.
    while (isspace(LastChar)) {
      LastChar = getchar();
      // if alphabet char
      // get identifier
      // eg. def -> d char is alphabet
      if (isalpha(LastChar)) {
        // identifier: [a-zA-Z][a-zA-Z0-9]*
        IdentifierStr = LastChar;
        // if alphanumeric (combination of alphabet and numeric characters)
        while (isalnum((LastChar = getchar()))) {
          IdentifierStr += LastChar;
        }

        if (IdentifierStr == "def") {
          return tok_def;
        }
        if (IdentifierStr == "extern") {
          return tok_extern;
        }
        if (IdentifierStr == "return") {
          return tok_return;
        }
        return tok_identifier;
      }

      // if digit
      // get number
      // numbers like 100, 200, 200.0
      else if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr = "";
        // get the number until it stops to encounter a dot '.' or digit
        // 12.00
        do {
          NumStr += LastChar;
          LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');
        // convert string to double/floating number 12.0
        NumVal = strtod(NumStr.c_str(), 0);
        return tok_number;
      }

      // comments line handling
      else if (LastChar == '#') {
        // comment until the end of line
        do {
          LastChar = getchar();
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF) {
          return Lexer::get_token();
        }
      }

      // if end of file input
      else if (LastChar == EOF) {
        return tok_eof;
      }

      // Otherwise, just return the character as its ascii value.
      int ThisChar = LastChar;
      LastChar = getchar();
      return ThisChar;
    }
  }
};
