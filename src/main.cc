#include <iostream>
#include <memory>

#include "lexer.cc"
#include "logger.cc"
#include "utils.cc"

int main(int argc, const char *argv[]) {
  // logger
  std::unique_ptr<Logger> logger = std::make_unique<Logger>();

  if (argc < 0) {
    logger->LogError("Invalid arguments");
    int i;
    std::cin >> i;
    return 1;
  }

  if (argc > 0) {
    for (int i = 0; i < argc; i++) {
      std::cout << "Argument " << i << " = " << argv[i] << std::endl;
    }

    std::unique_ptr<Util> util = std::make_unique<Util>();
    auto content = util->read_ascii_file(
        "C:\\Users\\kiran\\Desktop\\llvm\\test\\test.xen");
    std::cout << content << std::endl;
  } else {
    std::cout << "\031[ERROR]: Invalid arguments\031[0m\n" << std::endl;
    std::cout << "[LOG]: Stopping components..." << std::endl;
    exit(0);
  }

  std::unique_ptr<Lexer> lexer(new Lexer());

  while (true) {
    auto response = lexer->get_token();
    std::cout << response << std::endl;
  }

  return 0;
}
