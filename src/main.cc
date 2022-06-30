//=================================================================
//                            __                                   /
// ___  ___ ____   ____      |  | _____    ____    ____            /
// \  \/  // __ \ /  _ \     |  | \__  \  /    \  / ___\           /
//  >    <\  ___/|  | | \    |  |__/ __ \|   |  \/ /_/  >          /
// /__/\_ \\___  >__| | /    |____(____  /___|  /\___  /           /
//       \/    \/     \/               \/     \//_____/            /
//                                                                 /
//=================================================================
#include <iostream>
#include <memory>
#include <vector>

#include "../include/memory.h"
#include "../include/token.h"

#include "utils.cc"

//
//
// =======================================================
//                        MAIN                            ~
// =======================================================
int main(int argc, const char *argv[]) {
  {
    if (argc >= 0) {
      std::cout << "starting xen compiler..." << std::endl;
      Utils utils = Utils();

      std::string pathToFile = "C:\\Users\\kiran\\Desktop\\xen-lang-"
                               "LLVM\\test\\test.xen";
      // pointer to buffer
      auto *buffer = utils.scanner(pathToFile);

      PrintMemoryUsage();      

      std::vector<Token> *token_list = new std::vector<Token>;

      for (auto const &buff : *buffer) {
        Token *token = new Token((buff.second).c_str(), buff.first, tok_identifier);
        (*token_list).push_back(*token);
        delete token;
      }

      for (Token token : *token_list) {
        std::cout << token.line << ". " << token.data << " :: " << token.type
                  << std::endl;
      }

      delete token_list;
      delete buffer;
    } else {
      std::cout << "invalid arguments\nexiting compiler..." << std::endl;
    }
  }
  PrintMemoryUsage();
  std::cin.get();

  return 0;
}
