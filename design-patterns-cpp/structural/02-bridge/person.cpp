#include "person.h"
#include <iostream>

class Person::PersonImpl
{
public:
  void greet(Person* p);
};

void Person::PersonImpl::greet(Person* p)
{
  std::cout << "hello " << p->name << std::endl;
}

// class Person constructor
Person::Person() : impl(new PersonImpl)
{
}

// class Person destructor
Person::~Person()
{
  delete impl;
}

void Person::greet()
{
  impl->greet(this);
}
