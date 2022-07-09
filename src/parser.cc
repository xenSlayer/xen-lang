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

#include "token.h"

/// CurTok/getNextToken - Provide a simple token buffer.  CurTok is the
/// current token the parser is looking at.
// Every function in our parser will assume that CurTok is the current token
// that needs to be parsed.

class IParser {
public:
private:
  virtual void fill_token() = 0;
  virtual std::unique_ptr<ExprAST> ParseNumberExpr() = 0;
  virtual std::unique_ptr<ExprAST> ParseParenExpr() = 0;
  virtual std::unique_ptr<ExprAST> ParseIdentifierExpr() = 0;
  virtual std::unique_ptr<ExprAST> ParsePrimary() = 0;
  virtual std::unique_ptr<ExprAST> ParseExpression() = 0;
  virtual std::unique_ptr<ExprAST>
  ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) = 0;
  virtual std::unique_ptr<PrototypeAST> ParsePrototype() = 0;
  virtual std::unique_ptr<FunctionAST> ParseDefinition() = 0;
  virtual std::unique_ptr<PrototypeAST> ParseExtern() = 0;
  virtual std::unique_ptr<FunctionAST> ParseTopLevelExpr() = 0;
};

class Parser : IParser {

private:
  Logger *logger = new Logger();
  Lexer *lexer = new Lexer();
  Token *token;

  // / getNextToken reads another token from the lexer and updates CurTok with
  // / its results.
public:
  ~Parser() {
    delete logger;
    delete lexer;
    delete token;
  }

  void fill_token() override { token = lexer->get_token(); }

  /// numberexpr ::= number
  std::unique_ptr<ExprAST> ParseNumberExpr() override {
    // fill_token();
    auto Result = std::make_unique<NumberExprAST>(strtod(token->data, NULL));
    fill_token(); // consume the number
    return std::move(Result);
  }

  /// parenexpr ::= '(' expression ')'
  std::unique_ptr<ExprAST> ParseParenExpr() override {

    fill_token(); // eat (.

    // parse the expression
    auto V = ParseExpression();
    // ParseExpression();
    if (!V) {
      return nullptr;
    }

    // check if the utf-8 char code match ')'
    if (token->data[0] != ')') {
      return logger->LogError("expected ')'", token->line);
    }

    fill_token(); // eat ).
    // return V;
    return nullptr;
  }

  /// identifierexpr
  ///   ::= identifier
  ///   ::= identifier '(' expression* ')'
  // first check if it's only an identifier
  // if it has '(' after id then its a call expression
  std::unique_ptr<ExprAST> ParseIdentifierOrCallExpr() {
    // identifierName
    std::string IdName = token->data;

    fill_token(); // eat Identifier

    if (token->data[0] != '(') { // Simple variable ref.
      return std::make_unique<VariableExprAST>(IdName);
    }

    // Call
    fill_token(); // eat '('

    // for storing the arguments
    std::vector<std::unique_ptr<ExprAST>> Args;

    if (token->data[0] != ')') {
      while (true) {
        auto Arg = ParseExpression();
        if (Arg)
          // push_back -> insert item in the arrary 'vector'
          Args.push_back(std::move(Arg));
        else
          return nullptr;

        if (token->data[0] == ')') {
          fill_token();
          break;
        }
        if (token->data[0] == ',') {
          fill_token(); // eat ','
          continue;
        } else {
          return logger->LogError("Expected ')' or ',' in argument list",
                                  token->line);
        }
      }
      return std::make_unique<CallExprAST>(IdName, std::move(Args));
    }
  }

  /// primary
  ///   ::= identifierexpr
  ///   ::= numberexpr
  ///   ::= parenexpr
  // for example, the expression “a, 2, def, main()”
  // unary expression with no RHS or LHS i.e not binary
  std::unique_ptr<ExprAST> ParsePrimary() override {
    switch (token->type) {
    case IDENTIFIER:
      return ParseIdentifierOrCallExpr();
    case NUMBER:
      return ParseNumberExpr();
    case OPEN_PARAN: // '('
      return ParseParenExpr();
    default:
      logger->LogError("unknown token when expecting an expression",
                       token->line);
      break;
    }
  }

  /// expression
  ///   ::= primary binoprhs
  ///
  std::unique_ptr<ExprAST> ParseExpression() override {
    // returns the expression
    // example 1+2*3
    // curTok = 1
    // here LHS = 1 (NumberExprAST)
    // curTok = +
    auto LHS = ParsePrimary();
    if (LHS) {
      return ParseBinOpRHS(0, std::move(LHS));
    }
    return nullptr;
  }

  /// binoprhs
  ///   ::= ('+' primary)*
  std::unique_ptr<ExprAST>
  ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) override {

    std::unique_ptr<BinaryOperator> Op = std::make_unique<BinaryOperator>();

    while (1) {
      // checking the precedence of curTok ie. '+'
      int _op = (int)(token->data[0]);
      int CurTokPrec = Op->getTokPrecedence(_op);

      // ignore if precedence of the current token 'operator' is less, i.e its
      // not a valid bin op.
      // If this is a binop that binds at least as tightly as the current
      // binop, consume it, otherwise we are done.
      // if + precedence is less then 0 than return LHS. ie. not true here
      // if + was some invalid binop then return the LHS only
      if (ExprPrec > CurTokPrec) {
        return LHS;
      } else { // if its is a valid binop
        // here binop = '+'
        int BinOp = (int)(token->data[0]);
        // curTok = '2'
        fill_token(); // eat binop
        // check if there is another binop
        // RHS = NumberExprAST with val '2'
        // curTok = *
        auto RHS = ParsePrimary();
        if (RHS) {
          // precedence of *
          int NextTokPrec = Op->getTokPrecedence(token->data[0]);
          // if precedence of + < *
          // where curTokPrec = prec of +
          // NextTokPrec = prec of *
          // '*' > '+' ie. true here
          if (NextTokPrec > CurTokPrec) {
            // increase the precedence of +
            RHS = ParseBinOpRHS(CurTokPrec + 1, std::move(RHS));
            if (!RHS) {
              return nullptr;
            }
          }
          LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS),
                                                std::move(RHS));
        } else {
          return nullptr;
        }
      }
    }
  }

  // handling of function prototypes (function signature)
  // eg. foo(int arg1, int arg2)
  std::unique_ptr<PrototypeAST> ParsePrototype() override {
    if (token->type != IDENTIFIER) {
      return logger->LogErrorP("Expected function name in prototype",
                               token->line);
    }

    // store the name of the function
    // here FName = foo
    std::string FName = token->data;
    fill_token();

    if (token->data[0] != '(') {
      return logger->LogErrorP("Expected '(' after function name", token->line);
    }
    std::unique_ptr<std::vector<std::string>> argNames =
        std::make_unique<std::vector<std::string>>();

    // store the argument names
    // i.e arg1, arg2 in a vector
    while (token->type == IDENTIFIER) {
      fill_token();
      (*argNames).push_back(token->data);
    }

    if (token->data[0] != ')') {
      return logger->LogErrorP("Exprected ')' in the prototype", token->line);
    }

    fill_token();

    return std::make_unique<PrototypeAST>(FName, std::move(*argNames));
  }

  /// definition ::= 'def' prototype expression
  std::unique_ptr<FunctionAST> ParseDefinition() override {
    // std::unique_ptr<Logger> logger = std::make_unique<Logger>();
    fill_token(); // we assume curTok is tok_def

    std::unique_ptr<PrototypeAST> Proto = ParsePrototype();
    if (!Proto) {
      return nullptr;
    }
    auto Body = ParseExpression();
    if (Body) {
      return std::make_unique<FunctionAST>(std::move(Proto), std::move(Body));
    } else {
      return nullptr;
    }
  }

  // we support ‘extern’ to declare functions like ‘sin’ and ‘cos’ as well as to
  // support forward declaration of user functions. These ‘extern’s are just
  // prototypes with no body
  std::unique_ptr<PrototypeAST> ParseExtern() override {
    fill_token(); // eat extern
    return ParsePrototype();
  }

  // Finally, we’ll also let the user type in arbitrary top-level expressions
  // and evaluate them on the fly. We will handle this by defining anonymous
  // nullary (zero argument) functions for them
  std::unique_ptr<FunctionAST> ParseTopLevelExpr() override {
    if (auto E = ParseExpression()) {
      // Make an anonymous proto.
      auto Proto =
          std::make_unique<PrototypeAST>("", std::vector<std::string>());
      return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
    }
    return nullptr;
  }
};
