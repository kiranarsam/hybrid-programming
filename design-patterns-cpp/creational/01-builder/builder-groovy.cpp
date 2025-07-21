#include <string>
#include <vector>
#include <iostream>

namespace html {
  class Tag
  {
    std::string name;
    std::string text;
    std::vector<Tag> children;
    public:

    std::vector<std::pair<std::string, std::string>> attributes;

    void insertAttributes(std::pair<std::string, std::string> &&pair)
    {
      attributes.emplace_back(pair);
    }

    friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
    {
      os << "<" << tag.name;

      for (const auto& att : tag.attributes)
        os << " " << att.first << "=\"" << att.second << "\"";

      if (tag.children.size() == 0 && tag.text.length() == 0)
      {
        os << "/>" << std::endl;
      }
      else
      {
        os << ">" << std::endl;

        if (tag.text.length())
          os << tag.text << std::endl;

        for (const auto& child : tag.children)
          os << child;

        os << "</" << tag.name << ">" << std::endl;
      }

      return os;
    }
  protected:

    Tag(const std::string& name, const std::string& text)
      : name{name},
        text{text}
    {
    }


    Tag(const std::string& name, const std::vector<Tag>& children)
      : name{name},
        children{children}
    {
    }
  };

  class P : public Tag
  {
    public:
    explicit P(const std::string& text)
      : Tag{"p", text}
    {
    }

    P(std::initializer_list<Tag> children)
      : Tag("p", children)
    {
    }

  };

  class IMG : public Tag
  {
    public:
    explicit IMG(const std::string& url)
      : Tag{"img", ""}
    {
      insertAttributes(make_pair("src", url));
    }
  };
}

int main(int argc, char **argv)
{
  using namespace html;

  std::cout <<

    P {
      IMG {"http://pokemon.com/pikachu.png"}
    }

    << std::endl;

  return 0;
}