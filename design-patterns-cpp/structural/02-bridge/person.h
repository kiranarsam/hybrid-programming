#pragma once
#include <string>

class Person
{
  std::string name;

  class PersonImpl;
  PersonImpl *impl; // bridge - not necessarily inner class, can vary
public:
  Person();
  ~Person();

  void greet();
};
