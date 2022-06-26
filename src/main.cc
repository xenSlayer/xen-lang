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
// ==================== MAIN =============================
//
// =======================================================
int main(int argc, const char *argv[]) {
  {
    if (argc > 2 && std::string(argv[1]) == "compile") {
      std::cout << "starting xen compiler..." << std::endl;
      Utils utils = Utils();
      std::map<unsigned int, std::string> buffer = utils.scanner((std::string)argv[2]);

      std::vector<Token> *token_list = new std::vector<Token>;

      for (auto const &buff : buffer) {
        Token token = Token(buff.second, buff.first, tok_identifier);
        (*token_list).push_back(token);
      }

      for (Token token : *token_list) {
        std::cout << token.line << ". " << token.data << " :: " << token.type
                  << std::endl;
      }
      delete token_list;
    } else {
      std::cout << "invalid arguments\nexiting compiler..." << std::endl;
    }
  }
  PrintMemoryUsage();

  return 0;
}
