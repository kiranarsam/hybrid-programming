#pragma once
#include "hot_drink_factory.h"

class TeaFactory : public HotDrinkFactory
{
public:
  std::unique_ptr<HotDrink> make() const override {
    return std::make_unique<Tea>();
  }
};