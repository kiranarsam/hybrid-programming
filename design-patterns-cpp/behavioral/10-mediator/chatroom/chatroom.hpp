#pragma once
#include <algorithm>
#include "person.hpp"

struct ChatRoom
{
  std::vector<Person*> people;

  void broadcast(const std::string& origin, const std::string& message);

  void join(Person* p);

  void message(const std::string& origin, const std::string& who, const std::string& message)
  {
    auto target = std::find_if(
      std::begin(people),
      std::end(people),
      [&](const Person *p) {
        return p->name == who;
      });

    if (target != std::end(people))
    {
      (*target)->receive(origin, message);
    }
  }
};
