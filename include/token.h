#ifndef XEN_TOKEN_H
#define XEN_TOKEN_H
#include <string>

class Token {

public:
  std::string data;
  int type;
  unsigned int line;

  Token(std::string data, unsigned int line, int type)
      : data(data), line(line), type(type) {}
};

// The lexer returns tokens [0-255] if it is an unknown character, otherwise
// one of these for known things.
enum _TokenType {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,

  // primary
  tok_identifier = -4,
  tok_number = -5,

  // punctuation
  // '('
  tok_open_paran = -30,
  // ')'
  tok_close_paran = -31,
  // '.'
  tok_comma = -32,

};

typedef enum _TokenType TokenType;

#endif
