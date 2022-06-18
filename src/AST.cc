#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ++++++++++++++++++++++++++++++++++++++++++++++++
// +                 AST NODES                    +
// ++++++++++++++++++++++++++++++++++++++++++++++++

/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  // virtual class allows to override the constructor implmentation in subclass
  // ~ExprAST - Destructor
  virtual ~ExprAST() {}
};

/// NumberExprAST - Expression class for numeric literals like "1.0".
// for AST handling of numberic expression
class NumberExprAST : public ExprAST {
  double val;

public:
  // assigning value through constructor.lol
  // val(v) means val takes the value from v 😭
  NumberExprAST(double v) : val(v) {}
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
// for AST handling of variable expression 🏁
class VariableExprAST : public ExprAST {
  std::string variable;

public:
  VariableExprAST(const std::string &var) : variable(var) {}
};

/// BinaryExprAST - Expression class for a binary operator.
// 1 + 2
// op -> +
class BinaryExprAST : public ExprAST {
  char Op; // + - *

  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(char op, std::unique_ptr<ExprAST> LHS,
                std::unique_ptr<ExprAST> RHS)
      : Op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

/// CallExprAST - Expression class for function calls.
// (string arg1, int arg2)
// the callee and the args
// callee -> ()
// args -> arg1, arg2
class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<std::unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const std::string &Callee,
              std::vector<std::unique_ptr<ExprAST>> Args)
      : Callee(Callee), Args(std::move(Args)) {}
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
// def my_function_name(int arg1, string arg2)
// name -> my_function_name
// args -> arg1, arg2
class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;

public:
  PrototypeAST(const std::string &name, std::vector<std::string> Args)
      : Name(name), Args(std::move(Args)) {}

  const std::string &getName() const { return Name; }
};

/// FunctionAST - This class represents a function definition itself.
class FunctionAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<ExprAST> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::unique_ptr<ExprAST> Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {}
};
