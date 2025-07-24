#include "Observer.hpp"
#include "SaferObservable.hpp"
#include <iostream>

class Person : public SaferObservable<Person>
{
  int m_age{0};
public:
  Person(){}
  Person(int age) : m_age(age) {}

  int getAge() const
  {
    return m_age;
  }

  void setAge(int age)
  {
    if (this->m_age == age) {
      return;
    }

    auto old_can_vote = getCanVote();
    this->m_age = age;

    notify(*this, "age");

    if (old_can_vote != getCanVote()) {
      notify(*this, "can_vote");
    }
  }

  bool getCanVote() const {
    return this->m_age >= 16;
  }
};

// observer & observable
struct ConsolePersonObserver : Observer<Person>
{
private:
  void field_changed(Person &source, const std::string &field_name) override
  {
    std::cout << "Person's " << field_name << " has changed to ";
    if (field_name == "age") std::cout << source.getAge();
    if (field_name == "can_vote")
      std::cout << std::boolalpha << source.getCanVote();
    std::cout << ".\n";
  }
};

struct TrafficAdministration : Observer<Person>
{
  void field_changed(Person &source, const std::string &field_name) override
  {
    if (field_name == "age")
    {
      if (source.getAge() < 17)
        std::cout << "Whoa there, you're not old enough to drive!\n";
      else
      {
        std::cout << "Oh, ok, we no longer care!\n";
        source.unsubscribe(*this);
      }
    }
  }
};

int main(int argc, char* argv[])
{
  Person p;
  TrafficAdministration ta;
  p.subscribe(ta);

  p.setAge(15);
  p.setAge(16);
  try
  {
    p.setAge(17);
  }
  catch (const std::exception& e)
  {
    std::cout << "Oops, " << e.what() << "\n";
  }

  return 0;
}