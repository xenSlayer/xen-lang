#include <iostream>

#include "../src/AST.cc"

class Logger {
public:
  /// LogError* - These are little helper functions for error handling.
  static std::unique_ptr<ExprAST> LogError(const std::string &error) {
    // print error in console screen
    fprintf(stderr, "LogError: %s\n", error);
    // std::cout << "LogError: " << error << std::endl;
    return nullptr;
  }

  // not  sure why exactly they have logger for prototypeAST
  static std::unique_ptr<PrototypeAST> LogErrorP(const std::string &error) {
    LogError(error);
    return nullptr;
  }
};
