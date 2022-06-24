#include <iostream>
#include <stdlib.h>

#include "AST.cc"

// interfacec for logger class
class ILogger {
public:
  virtual std::unique_ptr<ExprAST> LogError(const std::string error) = 0;
  virtual std::unique_ptr<PrototypeAST> LogErrorP(const std::string &error) = 0;
  virtual void error(const std::string &error) = 0;
  virtual void warning(const std::string &error) = 0;
  virtual void log(const std::string &error) = 0;
};

// The LogError routines are simple helper routines that our parser will use to
// handle errors. The error recovery in our parser will not be the best and is
// not particular user-friendly
class Logger : ILogger {
public:
  /// LogError* - These are little helper functions for error handling.
  std::unique_ptr<ExprAST> LogError(const std::string error) override {
    // print error in console screen
    // fprintf(stderr, " %s\n", error);
    std::cout << "[ERROR]: " << error << std::endl;
    return nullptr;
  }

  // not  sure why exactly they have logger for prototypeAST
  std::unique_ptr<PrototypeAST> LogErrorP(const std::string &error) override {
    LogError(error);
    return nullptr;
  }

  void error(const std::string &error) override {
    std::cout << "[ERROR]: " << error << std::endl;
  }

  void warning(const std::string &error) override {
    std::cout << "[WARNING]: " << error << std::endl;
  }

  void log(const std::string &error) override {
    std::cout << "[LOG]: " << error << std::endl;
  }
};
