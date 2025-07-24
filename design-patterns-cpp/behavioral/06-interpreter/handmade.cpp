#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <memory>

struct Token
{
  enum Type { INTEGER, PLUS, MINUS, LEFT_PAREN, RIGHT_PAREN } type;

  std::string text;

  explicit Token(Type type, const std::string& text)
    : type{type}, text{text}
  {

  }

  friend std::ostream& operator<<(std::ostream& os, const Token& obj)
  {
    return os << "`" << obj.text << "`";
  }
};

std::vector<Token> lex(const std::string& input)
{
  std::vector<Token> result;

  for (int i = 0; i < input.size(); ++i)
  {
    switch (input[i])
    {
    case '+':
      result.push_back(Token{ Token::PLUS, "+" });
      break;
    case '-':
      result.push_back(Token{ Token::MINUS, "-" });
      break;
    case '(':
      result.push_back(Token{ Token::LEFT_PAREN, "(" });
      break;
    case ')':
      result.push_back(Token{ Token::RIGHT_PAREN, ")" });
      break;
    default:
      // number
      std::ostringstream buffer;
      buffer << input[i];
      for (int j = i + 1; j < input.size(); ++j)
      {
        if (isdigit(input[j]))
        {
          buffer << input[j];
          ++i;
        }
        else
        {
          result.push_back(Token{ Token::INTEGER, buffer.str() });
          break;
        }
      }

      if (!buffer.str().empty())
      {
        // 20201210
        result.push_back(Token{ Token::INTEGER, buffer.str() });
      }
    }
  }

  return result;
}

// parsing =====================================================

struct Element
{
  virtual ~Element() = default;
  virtual int eval() const = 0;
};

struct Integer : Element
{
  int value;
  explicit Integer(const int value) : value(value)
  {
  }
  int eval() const override { return value; }
};

struct BinaryOperation : Element
{
  enum Type { ADDITION, SUBTRACTION } type;
  std::shared_ptr<Element> lhs, rhs;

  int eval() const override
  {
    if (type == ADDITION) {
      return lhs->eval() + rhs->eval();
    }
    return lhs->eval() - rhs->eval();
  }
};

std::unique_ptr<Element> parse(const std::vector<Token>& tokens)
{
  auto result = std::make_unique<BinaryOperation>();
  bool have_lhs = false;
  for (size_t i = 0; i < tokens.size(); i++)
  {
    auto token = tokens[i];
    switch(token.type)
    {
    case Token::INTEGER:
    {
      int value = std::stoi(token.text);
      auto integer = std::make_shared<Integer>(value);
      if (!have_lhs) {
        result->lhs = integer;
        have_lhs = true;
      }
      else result->rhs = integer;
    }
      break;
    case Token::PLUS:
      result->type = BinaryOperation::ADDITION;
      break;
    case Token::MINUS:
      result->type = BinaryOperation::SUBTRACTION;
      break;
    case Token::LEFT_PAREN:
    {
      int j = i;
      for (; j < tokens.size(); ++j)
        if (tokens[j].type == Token::RIGHT_PAREN)
          break; // found it!

      std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
      auto element = parse(subexpression);
      if (!have_lhs)
      {
        result->lhs = std::move(element);
        have_lhs = true;
      }
      else result->rhs = std::move(element);
      i = j; // advance
    }
    break;
    }
  }
  return result;
}

int main()
{
  std::string input{ "(14-4)+11" }; // see if you can make nested braces work
  auto tokens = lex(input);

  // let's see the tokens
  for (auto& t : tokens)
    std::cout << t << "   ";
  std::cout << std::endl;

  try {
    auto parsed = parse(tokens);
    std::cout << input << " = " << parsed->eval() << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
