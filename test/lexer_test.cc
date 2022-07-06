#include <iostream>
#include <string>
// #include <string_view>

class Tokenizer {
public:
  Tokenizer(std::string &input) : m_input(input){};

  std::string next() {
    while (m_index < m_input.size()) {
      char c = m_input.at(m_index);
      switch (c) {
      case '_':
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
      case 'g':
      case 'h':
      case 'i':
      case 'j':
      case 'k':
      case 'l':
      case 'm':
      case 'n':
      case 'o':
      case 'p':
      case 'q':
      case 'r':
      case 's':
      case 't':
      case 'u':
      case 'v':
      case 'w':
      case 'x':
      case 'y':
      case 'z':
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
      case 'I':
      case 'J':
      case 'K':
      case 'L':
      case 'M':
      case 'N':
      case 'O':
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
      case 'T':
      case 'U':
      case 'V':
      case 'W':
      case 'X':
      case 'Y':
      case 'Z': {
        unsigned int m_init = m_index;
        do {
          m_index++;
        } while (isalnum(m_input.at(m_index)));

        return m_input.substr(m_init, m_index);
        break;
      }
      case '(':
        return m_input.substr(m_index, m_index);
      default:
        break;
      }
      m_index++;
      m_input.substr(0, 20);
    }
  }

private:
  std::string &m_input;
  unsigned int m_index{0};
};

int main() {
  std::string code = "def kiran(int 20, int ok) {}";
  Tokenizer *tokenizer = new Tokenizer(code);
  int i = 0;
  std::cout << isalnum('2') << std::endl;

  // while (i < 4) {
  //   std::cout << tokenizer->next() << std::endl;
  //   i++;
  // }

  return 0;
}
