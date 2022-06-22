#include <fstream>
#include <iostream>
#include <string>

class Util {
public:
  char *read_ascii_file(const char *path) {
    // open and read .xen file
    FILE *file = fopen(path, "r");
    // check if the file is valid
    if (!file) {
      // return 0 if error opening file
      printf("ERROR: could not open file %s\n", path);
      return NULL;
    }

    // get the end of the file
    fseek(file, 0, SEEK_END);
    // size of the file for memory allocation
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // buffer memory allocation of current file size + 1
    char *buf = (char *)malloc(sizeof(char) * (size + 1));
    // if memory allocation fails
    if (!buf) {
      printf("ERROR: could not allocate memory for file!\n");
      return NULL;
    }
    fread(buf, 1, size, file);
    // add an extra byte at the end of file for reference
    buf[size] = '\0';

    fclose(file);

    // return the contents of the file as buffer
    return buf;
  }

  // std::string *read_file(const std::string &pathToFile) {
  //   std::fstream newfile;
  //   newfile.open(pathToFile, std::ios::in);
  //   if (newfile.is_open()) { // checking whether the file is open
  //     std::string tp;
  //     while (getline(
  //         newfile, tp)) { // read data from file object and put it into
  //         string.
  //       std::cout << tp << "\n"; // print the data of the string
  //     }
  //     newfile.close(); // close the file object.
  //   }
  // }
};
