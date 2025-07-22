#include <vector>
#include <string>
#include <iostream>

namespace FactoryExercise {

struct Person
{
  int id;
  std::string name;

  friend std::ostream& operator<<(std::ostream& os, const Person& obj) {
    return os
      << "id: " << obj.id
      << " name: " << obj.name;
  }
};

class PersonFactory
{
private:
  int id { 0 };
public:
  Person createPerson(const std::string& name) {
    return { id++, name };
  }
};

} // namespace

int main(int ac, char* argv[])
{
  FactoryExercise::PersonFactory pf;

  auto p1 = pf.createPerson("Chris");
  auto p2 = pf.createPerson("Sarah");

  std::cout << p1 << std::endl;
  std::cout << p2 << std::endl;
  return 0;
}