// ++++++++++++++++++++++++++++++++++++++++++++++++
// +                UTILS                         +
// ++++++++++++++++++++++++++++++++++++++++++++++++

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "../include/const.h"

#include "logger.cc"

class IUtil {
public:
  virtual const std::map<unsigned int, std::string>
  scanner(const std::string &path) = 0;

private:
  virtual bool is_valid_xen_file(const std::string &path) = 0;
  virtual bool is_code_line(const std::string &line) = 0;
};

class Util : IUtil {
public:
  const std::map<unsigned int, std::string>
  scanner(const std::string &path) override {
    Logger *logger = new Logger();
    logger->log("reading file contents");
    std::ifstream file;
    unsigned int line_number = 0;
    std::string line;
    std::map<unsigned int, std::string> buffer = {};

    file.open(path, std::ios::in);
    // check file validity and open/read .xen file
    if (is_valid_xen_file(path) && file.is_open()) {
      while (getline(file, line)) {
        line_number++;
        // only if the line is not comment
        if (is_code_line(line))
          buffer[line_number] = line;
        // std::cout << line << std::endl;
      }
      return std::move(buffer);
      file.close();
    } else {
      logger->error("unable to open file");
      // printf("Unable to open file %s", path);
      // std::cout << "Exiting compiler..." << std::endl;
      exit(0);
    }
  }

private:
  // ? check if the file is a valid xen file.
  // ! exit the program if the file in nat a valid xen file
  // TODO change the code below to check the file is valid xen file
  // ! code below may break if the file path contains period in folder name
  bool is_valid_xen_file(const std::string &path) override {
    if (path.substr(path.find_last_of(".") + 1) == "xen")
      return true;
    else
      return false;
  }

  bool is_code_line(const std::string &line) override {
    if (line.front() != xenconst::comment && !line.empty())
      return true;
    else
      return false;
  }
};
