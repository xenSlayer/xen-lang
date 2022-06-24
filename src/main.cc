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
#include <typeinfo>
#include <vector>

#include "../include/token.h"

#include "utils.cc"

int main(int argc, const char *argv[]) {
  if (argc > 2) {
    std::cout << "starting xen compiler..." << std::endl;
    std::unique_ptr<Util> util = std::make_unique<Util>();

    std::map<unsigned int, std::string> buffer =
        util->scanner((std::string)argv[2]);

    std::vector<Token> token_list = {};

    for (auto const &buff : buffer) {
      Token *token = new Token();
      token->data = buff.second;
      token->line = buff.first;
      token->type = tok_identifier;
      token_list.push_back(*(token));
      free(token);
    }

    for (int i = 0; i < token_list.max_size(); i++) {
      Token token = token_list[i];
      std::cout << token.line << ". " << token.data << " :: " << token.type
                << std::endl;
    }

  } else {
    std::cout << "invalid arguments\nexiting compiler..." << std::endl;
    exit(0);
  }

  return 0;
}
