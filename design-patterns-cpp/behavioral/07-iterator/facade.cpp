#include <iostream>
#include <string>
#include <algorithm>

struct Node
{
  std::string value;
  Node* next = nullptr;

  explicit Node(const std::string& value) : value(value) { }

  Node(const std::string& value, Node* const parent) : value(value)
  {
    parent->next = this;
  }
};

struct ListIterator
{
  Node* current = nullptr;

  ListIterator() { }

  explicit ListIterator(Node* const current) : current(current) { }

  Node& dereference() const {
    return *current;
  }

  void increment() { current = current->next; }

private:

  bool equal(const ListIterator& other) const {
    return other.current == current;
  }

};

int main(int argc, char **argv)
{
  Node alpha{ "alpha" };
  Node beta{ "beta", &alpha};
  Node gamma{ "gamma", &beta };

  ListIterator iterator_start{ &alpha };
  ListIterator iterator_end{};

  for( ; iterator_start.current != iterator_end.current; ) {
    const auto node =  iterator_start.dereference();
    std::cout << node.value << std::endl;
    iterator_start.increment();
  }

  return 0;
}
