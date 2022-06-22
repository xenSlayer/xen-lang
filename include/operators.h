// ++++++++++++++++++++++++++++++++++++++++++++++++
// +      BINARY OPERATOR PRECEDENCE              +
// ++++++++++++++++++++++++++++++++++++++++++++++++

/*
    '<' = 10;
    '>' = 10;
    '+' = 20;
    '-' = 20;
    '*' = 40;  // highest.
*/

#ifndef XEN_OPERATORS_H
#define XEN_OPERATORS_H

#include <map>

/// BinaryOpPrecedence - This holds the precedence for each binary operator that
/// is defined.
static std::map<char, int> BinaryOpPrecedence;

BinaryOpPrecedence = {};

BinaryOpPrecedence['<'] = 10;
BinaryOpPrecedence['>'] = 10;
BinaryOpPrecedence['+'] = 20;
BinaryOpPrecedence['-'] = 20;
BinaryOpPrecedence['*'] = 40;
BinaryOpPrecedence['/'] = 40;

#endif
