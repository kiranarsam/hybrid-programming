#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct Token
{
  int value;

  Token(int value) : value(value) {}
};

struct Memento
{
  std::vector<std::shared_ptr<Token>> tokens;
};

struct TokenMachine
{
  std::vector<std::shared_ptr<Token>> tokens;

  Memento add_token(int value)
  {
    return add_token(std::make_shared<Token>(value));
  }

  Memento add_token(const shared_ptr<Token>& token)
  {
    tokens.push_back(token);
    Memento m;
    for (auto t : tokens) {
      m.tokens.emplace_back(std::make_shared<Token>(t->value));
    }
    return m;
  }

  void revert(const Memento& m)
  {
    tokens.clear();
    for (auto t : m.tokens)
      tokens.emplace_back(std::make_shared<Token>(t->value));
  }
};

int main(int argc, char* argv[])
{
  TokenMachine tm;
  auto m = tm.add_token(123);
  tm.add_token(456);
  tm.revert(m);
  std::cout << "Token size = " << tm.tokens.size() << "\n";
  std::cout << "Token value = " << tm.tokens[0]->value << "\n";

  auto token = std::make_shared<Token>(111);
  tm.add_token(token);
  auto m1 = tm.add_token(222);
  token->value = 333;
  tm.revert(m1);

  std::cout << "Token size = " << tm.tokens.size() << "\n";
  std::cout << "Token value = " << tm.tokens[0]->value << "\n";

  return 0;
}
