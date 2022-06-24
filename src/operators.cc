// ++++++++++++++++++++++++++++++++++++++++++++++++
// +         OPERATORS PRECENDENCE                +
// ++++++++++++++++++++++++++++++++++++++++++++++++

#include "../include/operators.h"
#include <iostream>

// base class
class Operators {
  virtual int getTokPrecedence(int &CurTok);
};

// binary operators
// + - *
class BinaryOperator : Operators {
public:
  /// GetTokPrecedence - Get the precedence of the pending binary operator
  /// token.
  int getTokPrecedence(int &CurTok) override {
    int TokPrec = -1;
    if (!isascii(CurTok)) {
      return -1;
    } // if operator is found in our map

    else if (int TokPrec = BinaryOpPrecedence.count(CurTok) > 0) {
      // Make sure it's a declared binop.
      TokPrec = BinaryOpPrecedence[CurTok];

      if (TokPrec <= 0) {
        return -1;
      }
    }
    return TokPrec;
  }
};
