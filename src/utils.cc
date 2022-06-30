// ++++++++++++++++++++++++++++++++++++++++++++++++
// +                UTILS                         +
// ++++++++++++++++++++++++++++++++++++++++++++++++

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "../include/const.h"
#include "../include/memory.h"

#include "logger.cc"

class IUtils {
public:
  virtual const std::map<unsigned int, std::string> *
  scanner(std::string &pathToFile) = 0;
};

class Utils : IUtils {
private:
  // ? check if the file is a valid xen file.
  // ! exit the program if the file in nat a valid xen file
  // TODO change the code below to check the file is valid xen file
  // ! code below may break if the file path contains period in folder name
  bool _is_valid_xen_file(std::string &path) {
    if (path.substr(path.find_last_of(".") + 1) == "xen")
      return true;
    else
      return false;
  }

  bool _is_code_line(const std::string &line) {
    if (line.front() != xenconst::comment && !line.empty())
      return true;
    else
      return false;
  }

public:
  const std::map<unsigned int, std::string> *
  scanner(std::string &pathToFile) override {
    Logger logger = Logger();

    std::ifstream file;

    logger.log("reading file contents");

    file.open(pathToFile, std::ios::in);

    // check file validity and open/read .xen file
    if (_is_valid_xen_file(pathToFile) && file.is_open()) {
      unsigned int line_number = 0;
      std::unique_ptr<std::string> line = std::make_unique<std::string>();
      std::map<unsigned int, std::string> *buffer =
          new std::map<unsigned int, std::string>;
      while (getline(file, *line)) {
        line_number++;
        // ignore if comment lines encountered
        if (_is_code_line(*line))
          (*buffer)[line_number] = *line;
      }
      file.close();
      PrintMemoryUsage();
      return buffer;
    } else {
      logger.error("unable to open file");
    }
  }
};
