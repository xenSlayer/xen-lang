#ifndef XEN_TOKEN_H
#define XEN_TOKEN_H
#include <string>

struct Token {
  std::string data;
  int type;
  unsigned int line;
};

// The lexer returns tokens [0-255] if it is an unknown character, otherwise
// one of these for known things.
enum _TokenType {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,
  tok_return = 0,

  // primary
  tok_identifier = -4,
  tok_number = -5,
};

typedef enum _TokenType TokenType;

#endif