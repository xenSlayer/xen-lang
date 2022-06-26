// ++++++++++++++++++++++++++++++++++++++++++++++++
// +                 PARSER                       +
// ++++++++++++++++++++++++++++++++++++++++++++++++

#include <iostream>
#include <memory>
#include <stdlib.h>

#include "AST.cc"
#include "lexer.cc"
#include "logger.cc"
#include "operators.cc"

/// CurTok/getNextToken - Provide a simple token buffer.  CurTok is the
/// current token the parser is looking at.
// Every function in our parser will assume that CurTok is the current token
// that needs to be parsed.

static int CurTok;

class Parser {

private:
  Logger *logger = new Logger();
  // / getNextToken reads another token from the lexer and updates CurTok with
  // / its results.
public:
  ~Parser() { delete logger; }

  int getNextToken() {
    std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>();
    // std::unique_ptr<Lexer> lexer(new Lexer());
    return CurTok = lexer->get_token();
  }

  /// numberexpr ::= number
  std::unique_ptr<ExprAST> ParseNumberExpr() {
    auto Result = std::make_unique<NumberExprAST>(NumVal);
    getNextToken(); // consume the number
    return std::move(Result);
  }

  /// parenexpr ::= '(' expression ')'
  std::unique_ptr<ExprAST> ParseParenExpr() {
    getNextToken(); // eat (.

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
  std::unique_ptr<ExprAST> ParseIdentifierExpr() {
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
      delete logger;
      return std::make_unique<CallExprAST>(IdName, std::move(Args));
    }
  }

  /// primary
  ///   ::= identifierexpr
  ///   ::= numberexpr
  ///   ::= parenexpr
  // for example, the expression “a+b+(c+d)*e*f+g”
  std::unique_ptr<ExprAST> ParsePrimary() {
    Logger *logger = new Logger();
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
    delete logger;
  }

  /// expression
  ///   ::= primary binoprhs
  ///
  std::unique_ptr<ExprAST> ParseExpression() {
    // returns the expression
    auto LHS = ParsePrimary();
    if (LHS) {
      return ParseBinOpRHS(0, std::move(LHS));
    }
    return nullptr;
  }

  /// binoprhs
  ///   ::= ('+' primary)*
  std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec,
                                         std::unique_ptr<ExprAST> LHS) {

    std::unique_ptr<BinaryOperator> Op = std::make_unique<BinaryOperator>();
    while (true) {
      int CurTokPrec = Op->getTokPrecedence(CurTok);

      // ignore if precedence of the current token 'operator' is less, i.e its
      // not a valid bin op.
      // If this is a binop that binds at least as tightly as the current
      // binop, consume it, otherwise we are done.
      if (CurTokPrec < ExprPrec) {
        return LHS;
      } else { // if its is a valid binop
        int BinOp = CurTok;
        getNextToken(); // eat binop
        auto RHS = ParsePrimary();
        if (RHS) {
          int NextTokPrec = Op->getTokPrecedence(CurTok);
          if (CurTokPrec < NextTokPrec) {
            LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS),
                                                  std::move(RHS));
          }
        } else {
          return nullptr;
        }
      }
    }
  }
};
