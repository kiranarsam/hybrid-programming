#pragma once
#include "pimpl.hpp"

class Foo
{
  class FooImpl;
  Pimpl<Foo::FooImpl> fimpl;
public:
  Foo() = default;
  ~Foo() = default;
};

class Foo::FooImpl
{
public:
    FooImpl() = default;
    ~FooImpl() = default;
};