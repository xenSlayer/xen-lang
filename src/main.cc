#include <iostream>
#include <memory>

#include "lexer.cc"

int main() {
  std::unique_ptr<Lexer> lexer(new Lexer());

  while (true) {
    auto response = lexer->get_token();
    std::cout << response << std::endl;
  }

  return 0;
}
