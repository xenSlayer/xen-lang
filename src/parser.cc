// ++++++++++++++++++++++++++++++++++++++++++++++++
// +                 PARSER                       +
// ++++++++++++++++++++++++++++++++++++++++++++++++

#include <iostream>
#include <memory>
#include <stdlib.h>

#include "AST.cc"
#include "lexer.cc"
#include "logger.cc"

/// CurTok/getNextToken - Provide a simple token buffer.  CurTok is the
/// current token the parser is looking at.
// Every function in our parser will assume that CurTok is the current token
// that needs to be parsed.

// static int CurTok;

class Parser {
public:
  static int CurTok;

private:
  std::unique_ptr<Logger> logger = std::make_unique<Logger>();
  // / getNextToken reads another token from the lexer and updates CurTok with
  // / its results.
  static int getNextToken() {
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>();
    // std::unique_ptr<Lexer> lexer(new Lexer());
    return CurTok = lexer->get_token();
  }

  /// numberexpr ::= number
  static std::unique_ptr<ExprAST> ParseNumberExpr() {
    auto Result = std::make_unique<NumberExprAST>(NumVal);
    getNextToken(); // consume the number
    return std::move(Result);
  }

  /// parenexpr ::= '(' expression ')'
  static std::unique_ptr<ExprAST> ParseParenExpr() {
    getNextToken(); // eat (.

    std::unique_ptr<Logger> logger = std::make_unique<Logger>();

    // parse the expression
    auto V = ParseExpression();
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

  /// identifierexpr
  ///   ::= identifier
  ///   ::= identifier '(' expression* ')'
  static std::unique_ptr<ExprAST> ParseIdentifierExpr() {
    std::unique_ptr<Logger> logger = std::make_unique<Logger>();
    std::string IdName = IdentifierStr;

    getNextToken();      // eat Identifier
    if (CurTok != '(') { // Simple variable ref.
      return std::make_unique<VariableExprAST>(IdName);
    }

    // Call
    getNextToken(); // eat '('

    // for storing the arguments
    std::vector<std::unique_ptr<ExprAST>> Args;

    if (CurTok != ')') {
      while (true) {
        auto Arg = ParseExpression();
        if (Arg)
          // push_back -> insert item in the arrary 'vector'
          Args.push_back(std::move(Arg));
        else
          return nullptr;

        if (CurTok == ')') {
          getNextToken();
          break;
        }
        if (CurTok == ',') {
          getNextToken(); // eat ','
          continue;
        } else
          return logger->LogError("Expected ')' or ',' in argument list");
      }
      return std::make_unique<CallExprAST>(IdName, std::move(Args));
    }
  }

  /// primary
  ///   ::= identifierexpr
  ///   ::= numberexpr
  ///   ::= parenexpr
  // for example, the expression “a+b+(c+d)*e*f+g”
  static std::unique_ptr<ExprAST> ParsePrimary() {
    std::unique_ptr<Logger> logger = std::make_unique<Logger>();
    switch (CurTok) {
    case tok_identifier:
      return ParseIdentifierExpr();
    case tok_number:
      return ParseNumberExpr();
    case '(':
      return ParseParenExpr();
    default:
      logger->LogError("unknown token when expecting an expression");
      break;
    }
  }

  /// expression
  ///   ::= primary binoprhs
  ///
  static std::unique_ptr<ExprAST> ParseExpression() {
    // returns the expression
    auto LHS = ParsePrimary();
    if (LHS) {
      return ParseBinOpRHS(0, std::move(LHS));
    }
    return nullptr;
  }

  /// binoprhs
  ///   ::= ('+' primary)*
  static std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec,
                                                std::unique_ptr<ExprAST> LHS) {
    while (true) {
    }
  }
};
