#ifndef XEN_TOKEN_H
#define XEN_TOKEN_H

#include <string>

// keywords
#define DEF -2
#define RETURN -3
#define IF -4
#define ELSE -5
#define INT -6
#define STRING -7
#define DOUBLE -8

// identifers
#define IDENTIFIER -20

// numbers
#define NUMBER -21
#define DOUBLE_NUMBER -22

// brackets
#define OPEN_PARAN -30
#define CLOSE_PARAN -31
#define OPEN_BRACKET -32
#define CLOSE_BRACKET -33

// binary operators
#define ADD_OP -40
#define SUB_OP -41
#define MUL_OP -42
#define DIV_OP -43
#define EQ_OP -44

// symbols
#define COLON -50
#define SEMI_COLON -51
#define COMMA -52

class Token {

public:
  std::string data;
  int type;
  unsigned int line;

  Token(std::string data, int type, unsigned int line_number)
      : data(data), type(type), line(line_number) {}
};

#endif
