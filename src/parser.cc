#include <iostream>
#include <memory>
#include <stdlib.h>

#include "AST.cc"
#include "lexer.cc"
#include "utils/logger.cc"

/// CurTok/getNextToken - Provide a simple token buffer.  CurTok is the
/// current token the parser is looking at.
static int CurTok;

class Parser {
public:
  // / getNextToken reads another token from the lexer and updates CurTok with
  // / its results.
  static int getNextToken() {
    std::unique_ptr<Lexer> lexer(new Lexer());
    return CurTok = lexer->get_token();
  }

  // /// LogError* - These are little helper functions for error handling.
  // static std::unique_ptr<ExprAST> LogError(const std::string &error) {
  //   // print error in console screen
  //   fprintf(stderr, "LogError: %s\n", error);
  //   // std::cout << "LogError: " << error << std::endl;
  //   return nullptr;
  // }

  // // not  sure why exactly they have logger for prototypeAST
  // std::unique_ptr<PrototypeAST> LogErrorP(const std::string &error) {
  //   LogError(error);
  //   return nullptr;
  // }

  /// numberexpr ::= number
  static std::unique_ptr<ExprAST> ParseNumberExpr() {
    auto Result = std::make_unique<NumberExprAST>(NumVal);
    getNextToken(); // consume the number
    return std::move(Result);
  }

  /// parenexpr ::= '(' expression ')'
  static std::unique_ptr<ExprAST> ParseParenExpr() {
    std::unique_ptr<Logger> logger = std::make_unique<Logger>();

    getNextToken(); // eat (.

    // parse the expression
    // Todo ParseExpression()
    // auto V = ParseExpression();
    auto V = 0;
    // ParseExpression();
    if (!V) {
      return nullptr;
    }

    // check if the utf-8 char code match ')'
    if (CurTok != ')') {
      return logger->LogError("expected ')'");
    }

    getNextToken(); // eat ).
    // return V;
    return nullptr;
  }
};
