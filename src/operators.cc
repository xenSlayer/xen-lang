// ++++++++++++++++++++++++++++++++++++++++++++++++
// +         OPERATORS PRECENDENCE                +
// ++++++++++++++++++++++++++++++++++++++++++++++++
#include <iostream>
#include <map>
#include <string>

/* TOKEN PRECEDENCE
'<' = 10;
'>' = 10;
'+' = 20;
'-' = 20;
'*' = 40;  // highest.
*/

// base class
class IBinaryOperator {
public:
  virtual int getTokPrecedence(int CurTok) = 0;
};

// binary operators
// + - *
class BinaryOperator : IBinaryOperator {
public:
  /// GetTokPrecedence - Get the precedence of the pending binary operator
  /// token.
  int getTokPrecedence(int CurTok) override {

    static std::map<char, int> *BinaryOpPrecedence = new std::map<char, int>();

    (*BinaryOpPrecedence)['<'] = 5;
    (*BinaryOpPrecedence)['>'] = 5;
    (*BinaryOpPrecedence)['-'] = 10;
    (*BinaryOpPrecedence)['+'] = 20;
    (*BinaryOpPrecedence)['*'] = 40;
    (*BinaryOpPrecedence)['/'] = 50;

    int TokPrec = -1;

    if (!isascii(CurTok)) {
      return TokPrec;
    } // if operator is found in our map

    else if (int TokPrec = (*BinaryOpPrecedence).count(CurTok) > 0) {
      // Make sure it's a declared binop.
      TokPrec = (*BinaryOpPrecedence)[CurTok];

      std::cout << TokPrec;

      if (TokPrec <= 0) {
        return -1;
      }
    }
    delete BinaryOpPrecedence;
    return TokPrec;
  }
};

// int main() {
//     BinaryOperator *op = new BinaryOperator();
//     const char *oper = ":";
//     std::cout << op->getTokPrecedence((int)(oper[0]));
//     return 0;
// }
