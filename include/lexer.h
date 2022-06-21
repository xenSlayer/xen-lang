// ++++++++++++++++++++++++++++++++++++++++++++++++
// +                LEXER TOKENS                  +
// ++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef XEN_LEXER_H
#define XEN_LEXER_H

#include <string>
// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum _Token {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,
  tok_return = 0,

  // primary
  tok_identifier = -4,
  tok_number = -5,
};

typedef enum _Token Token;

#endif
