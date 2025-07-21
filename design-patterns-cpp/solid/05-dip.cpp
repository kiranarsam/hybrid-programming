/**
 * Dependency Inversion Principle:
 * 	--> High-level modules should not depend upon low-level ones; Use abstractions
 */

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

// A. High-level modules should not depend on low-level modules.
//    Both should depend on abstractions.
// B. Abstractions should not depend on details.
//    Details should depend on abstractions.

enum class Relationship
{
  PARENT,
  CHILD,
  SIBLING
};

struct Person
{
  std::string name;
};

class RelationshipBrowser
{
public:
  virtual std::vector<Person> find_all_children_of(const std::string& name) = 0;
};

class Relationships : public RelationshipBrowser // low-level
{
  // vector and tuple. relations member variable don't dependen on other objects
  std::vector<std::tuple<Person, Relationship, Person>> relations;
public:

  void add_parent_and_child(const Person& parent, const Person& child)
  {
    relations.push_back({parent, Relationship::PARENT, child});
    relations.push_back({child, Relationship::CHILD, parent});
  }

  std::vector<Person> find_all_children_of(const std::string &name) override
  {
    std::vector<Person> result;
    for (auto&& [first, rel, second] : relations)
    {
      if (first.name == name && rel == Relationship::PARENT)
      {
        result.push_back(second);
      }
    }
    return result;
  }
};

class Research // high-level
{
public:
  Research(RelationshipBrowser& browser)
  {
    for (auto& child : browser.find_all_children_of("John"))
    {
      std::cout << "John has a child called " << child.name << std::endl;
    }
  }
};

int main()
{
  Person parent{"John"};
  Person child1{"Chris"};
  Person child2{"Matt"};

  Relationships relationships;
  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  Research _(relationships);

  return 0;
}