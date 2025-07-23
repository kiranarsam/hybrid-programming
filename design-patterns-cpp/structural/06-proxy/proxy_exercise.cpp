#include <iostream>
#include <string>

class Person
{
  friend class ResponsiblePerson;
  int m_age;
public:
  Person(int age) : m_age(age) {}

  int getAge() const { return m_age; }
  void setAge(int age) { this->m_age = age; }

  std::string drink() const { return "drinking"; }
  std::string drive() const { return "driving"; }
  std::string drinkAndDrive() const { return "driving while drunk"; }
};

class ResponsiblePerson
{
public:
  ResponsiblePerson(const Person &person) : m_person(person) {}

  int getAge() const { return m_person.m_age; }
  void setAge(int value) { m_person.m_age = value; }

  std::string drink() const {
    if (getAge() >= 18)
      return m_person.drink();
    else return "too young";
  }

  std::string drive() const {
    if (getAge() >= 16)
      return m_person.drive();
    else return "too young";
  }

  std::string drinkAndDrive() const
  {
    auto res = m_person.drinkAndDrive();
    res += " dead";
    return res.c_str();
  }

private:
  Person m_person;
};

int main(int argc, char** argv)
{
  Person p{10};
  ResponsiblePerson rp{p};

  std::cout << rp.drive() << "\n";
  std::cout << rp.drink() << "\n";
  std::cout << rp.drinkAndDrive() << "\n";

  rp.setAge(20);

  std::cout << rp.drive() << "\n";
  std::cout << rp.drink() << "\n";
  std::cout << rp.drinkAndDrive() << "\n";

  return 0;
}