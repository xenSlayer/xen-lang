// Online C++ compiler to run C++ program online
#include <iostream>
#include <map>
#include <string>
#include <vector>

// #include "../include/memory.h"
#include "../include/token.h"

// void clearIdentifierData() { *identifierStr = ""; };

int main() {
  std::string *identifierStr = new std::string();
  char punctuation = ' ';
  double numval;
  std::vector<Token> *tokens = new std::vector<Token>();
  Token *token;

  std::map<unsigned int, std::string> *buffer =
      new std::map<unsigned int, std::string>();

  (*buffer)[1] = "def xen kiran(k, k)";
  (*buffer)[2] = "kiran paudel";
  (*buffer)[3] = "xe";

  for (auto const &buff : *buffer) {
    // loop through each charachter
    for (int i = 0; i < buff.second.length(); i++) {
      // is space encountered then increment i and clear identiferStr
      if (isalpha(buff.second[i]) || buff.second[i] == '_') {
        *identifierStr += buff.second[i];
        i++;
        while (isalnum(buff.second[i])) {
          *identifierStr += buff.second[i];
          // i++;
        }
      }
      if (buff.second[i] == '(') {
        token = new Token("(", buff.first, tok_open_paran);
        (*tokens).push_back(*token);
        // i++;
      }

      if (buff.second[i] == ')') {
        token = new Token(")", buff.first, tok_close_paran);
        (*tokens).push_back(*token);
        // i++;
      }

      if (buff.second[i] == ',') {
        token = new Token(",", buff.first, tok_comma);
        (*tokens).push_back(*token);
        // i++;
      }

      if (buff.second[i] == '#') {
        break;
      }

      // if(buff.second[i] == '(') {break;}
      if (buff.second[i] == ' ' || i == buff.second.length()) {
        if (*identifierStr == "def") {
          token = new Token(*identifierStr, buff.first, tok_def);
          (*tokens).push_back(*token);
          delete token;
          *identifierStr = "";
        } else {
          token = new Token(*identifierStr, buff.first, tok_identifier);
          delete token;
          // clear the identifierStr
          *identifierStr = "";
        }
      }
    }
    *identifierStr = "";
  }

  for (int i = 0; i < (*tokens).size(); i++) {
    std::cout << (*tokens)[i].data << " :: " << (*tokens)[i].type
              << " :: " << (*tokens)[i].line << std::endl;
  }

  (*buffer).clear();
  delete identifierStr;
  delete tokens;
  delete buffer;
  // PrintMemoryUsage();
  return 0;
}
