#include <memory>
#include <string>
#include <vector>

struct Token {
  std::string data;
  int type;
  int line;
};

class Tokenizer {
private:
  std::vector<std::unique_ptr<Token>> tokens;

public:
  Token *create_token(const std::string &data, int &type, int &line) {
    Token *token = new Token();
    token->data = data;
    token->type = type;
    token->line = line;
    return token;
  }

  std::vector<std::unique_ptr<Token>> add_token(std::unique_ptr<Token> &token) {
    tokens.push_back(token);
    return tokens;
  }
};
