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

#include "lexer.cc"
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

      Lexer *lexer = new Lexer();
      lexer->get_token();

    } else {
      std::cout << "invalid arguments\nexiting compiler..." << std::endl;
    }
  }
  PrintMemoryUsage();
  std::cin.get();

  return 0;
}
