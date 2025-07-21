#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

struct HtmlBuilder;

struct HtmlElement
{
  std::string name;
  std::string text;
  std::vector<HtmlElement> elements;
  const size_t indent_size = 2;

  HtmlElement() {}
  HtmlElement(const std::string& name, const std::string& text)
    : name(name), text(text)
  {
  }

  std::string str(int indent = 0) const
  {
    std::ostringstream oss;
    std::string i(indent_size*indent, ' ');
    oss << i << "<" << name << ">" << std::endl;
    if (text.size() > 0) {
      oss << std::string(indent_size*(indent + 1), ' ') << text << std::endl;
    }

    for (const auto& e : elements) {
      oss << e.str(indent + 1);
    }

    oss << i << "</" << name << ">" << std::endl;
    return oss.str();
  }

  static std::unique_ptr<HtmlBuilder> build(const std::string& root_name)
  {
    return std::make_unique<HtmlBuilder>(root_name);
  }
};

struct HtmlBuilder
{
  HtmlBuilder(std::string root_name)
  {
    root.name = root_name;
  }

  // void to start with
  HtmlBuilder& add_child(std::string child_name, std::string child_text)
  {
    root.elements.emplace_back(HtmlElement{ child_name, child_text });
    return *this;
  }

  // pointer based
  HtmlBuilder* add_child_2(const std::string& child_name, const std::string& child_text)
  {
    root.elements.emplace_back(HtmlElement{ child_name, child_text });
    return this;
  }

  std::string str() { return root.str(); }

  operator HtmlElement() const {
    std::cout << "Invoked operator HtmlElement() \n";
    return root;
  }

  HtmlElement root;
};

int main(int argc, char **argv)
{
  // <p>hello</p>
  auto text = "hello";
  std::string output;
  output += "<p>";
  output += text;
  output += "</p>";
  printf("<p>%s</p>", text);

  // <ul><li>hello</li><li>world</li></ul>
  std::string words[] = { "hello", "world" };
  std::ostringstream oss;
  oss << "<ul>";
  for (auto w : words)
    oss << "  <li>" << w << "</li>";
  oss << "</ul>";
  printf("%s\n", oss.str().c_str());

  // easier
  HtmlBuilder builder{ "ul" };
  builder.add_child("li", "hello").add_child("li", "world");
  std::cout << builder.str() << std::endl;


  auto builder2 = HtmlElement::build("ul");
  builder2->add_child_2("li", "hello");
  builder2->add_child_2("li", "world");
  std::cout << builder2->str();

  return 0;
}