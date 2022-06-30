#include <cstdio>
#include <stdlib.h>
#include <string>

#include "../include/token.h"

class ILexer {
public:
  virtual int get_token() = 0;
};

class Lexer : ILexer {
private:
  std::map<unsigned int, std::string> buffer;
  static std::string IdentifierStr; // Filled in if tok_identifier
  static double NumVal;             // Filled in if tok_number
public:
  Lexer(std::map<unsigned int, std::string> buffer) : buffer(buffer) {}

  // gettok - Return the next token from standard input.
  // Todo convert get_token to read whole content of the file rather then
  // console content
  Token *get_token() override {

    for (auto const &buff : buffer) {
      Token token = Token(buff.second, buff.first, tok_identifier);
      (*token_list).push_back(token);
    }

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
