#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>
#include <algorithm>

struct Sentence
{
  struct WordToken
  {
    bool capitalize;
  };

  std::vector<std::string> words;
  std::map<int, WordToken> tokens;

  Sentence(const std::string& text)
  {
    std::istringstream iss{text};
    words = std::vector<std::string>(std::istream_iterator<std::string>{iss},
                           std::istream_iterator<std::string>{});
  }

  WordToken& operator[](size_t index)
  {
    tokens[index] = WordToken{};
    return tokens[index];
  }

  std::string str() const
  {
    std::vector<std::string> ws;
    for (size_t i = 0; i < words.size(); ++i)
    {
      std::string w = words[i];
      auto t = tokens.find(i);
      if (t != tokens.end() && t->second.capitalize)
      {
        // note: the annotation on ::toupper() below is only required
        // for GCC; other compilers work fine without it
        std::transform(w.begin(), w.end(), w.begin(), (int (&)(int)) std::toupper);
      }
      ws.push_back(w);
    }

    std::ostringstream oss;
    for (size_t i = 0; i < ws.size(); ++i)
    {
      oss << ws[i];
      if (i+1 != ws.size()) oss << " ";
    }
    return oss.str();
  }
};

int main(int ac, char* av[])
{
    Sentence s{"alpha beta gamma"};
    s[0].capitalize = s[2].capitalize = false;
    s[1].capitalize = true;
    std::cout << s.str() << "\n";
  return 0;
}