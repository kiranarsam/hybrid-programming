#include <string>
#include <vector>
#include <ostream>
#include <sstream>
#include <algorithm>
#include <iostream>

class Field {
private:
  std::string name, type;
public:
  Field(const std::string& name, const std::string& type) : name{name}, type{type}
  {
  }

  friend std::ostream& operator << (std::ostream& os, const Field& obj)
  {
    return os << obj.type << " " << obj.name << ";";
  }
};

class Class {
private:
  std::string name;
  std::vector<Field> fields;
public:

  void setClassName(const std::string& name)
  {
    this->name = name;
  }

  void addField(Field &&field)
  {
    fields.emplace_back(field);
  }

  friend std::ostream& operator<<(std::ostream& os, const Class& obj)
  {
    os << "class " << obj.name << "\n{\n";
    for (auto&& field : obj.fields) {
      os << "  " << field << "\n";
    }
    return os << "};\n";
  }
};

class CodeBuilder
{
private:
  Class the_class;
public:
  CodeBuilder(const std::string& class_name)
  {
    the_class.setClassName(class_name);
  }

  CodeBuilder& add_field(const std::string& name, const std::string& type)
  {
    the_class.addField(Field{name, type});
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const CodeBuilder& obj)
  {
    return os << obj.the_class;
  }
};

// trim from start (in place)
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
    return !std::isspace(ch);
  }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
    return !std::isspace(ch);
  }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
  ltrim(s);
  return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
  rtrim(s);
  return s;
}


int main(int argc, char **argv)
{
  // Test 1
  CodeBuilder cb1{ "Foo" };
  std::ostringstream oss1;
  oss1 << cb1;
  auto printed1 = oss1.str();
  trim(printed1);
  std::cout << printed1 << std::endl;

  // Test 2
  auto cb2 = CodeBuilder{ "Person" }
      .add_field("name", "string")
      .add_field("age", "int");
  std::ostringstream oss2;
  oss2 << cb2;
  auto printed2 = oss2.str();
  trim(printed2);
  std::cout << printed2 << std::endl;

  return 0;
}
