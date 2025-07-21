#pragma once
#include "person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
protected:
  Person& person;
  explicit PersonBuilderBase(Person& person) : person{ person }
  {
  }
public:
  operator Person() const
  {
    return std::move(person);
  }

  // builder facets
  PersonAddressBuilder lives() const;
  PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase
{
private:
  Person p;
public:
  PersonBuilder(): PersonBuilderBase{p}
  {
  }
};