#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>

#include "utils.cc"

int main(int argc, const char *argv[]) {
  if (argc > 2) {
    std::cout << "starting xen compiler..." << std::endl;
    std::unique_ptr<Util> util = std::make_unique<Util>();
    std::cout << (std::string)argv[0] << std::endl;
    // while (1) {
    //   std::string content = util->read_ascii_file((std::string)argv[2]);
    //   std::cout << content << std::endl;
    // }
    util->read_ascii_file((std::string)argv[2]);

  } else {
    std::cout << "invalid arguments\nexiting compiler..." << std::endl;
    exit(0);
  }

  return 0;
}
