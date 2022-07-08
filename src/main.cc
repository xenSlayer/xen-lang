/*
=======================================================
                            ___
 ___  ___ ____   ____      |  | _____    ____    ____
 \  \/  // __ \ /  _ \     |  | \__  \  /    \  / ___\
  >    <\  ___/|  | | \    |  |__/ __ \|   |  \/ /_/  >
 /__/\_ \\___  >__| | /    |____(____  /___|  /\___  /
       \/    \/     \/               \/     \//_____/
=======================================================
*/

#include <iostream>

#include "../include/memory.h"
#include "../include/token.h"

#include "lexer.cc"

//
//
// =======================================================
//                        MAIN                            ~
// =======================================================

int main(int argc, const char *argv[]) {

  std::cout << "starting xen compiler..." << std::endl;

  Lexer lexer = Lexer();
  Token token = lexer.get_token();
  while (token.data) {
    std::cout << token.line << ". " << token.data << " :: type " << token.type
              << std::endl;
    token = lexer.get_token();
  }

  PrintMemoryUsage();
  std::cin.get();

  return 0;
}
