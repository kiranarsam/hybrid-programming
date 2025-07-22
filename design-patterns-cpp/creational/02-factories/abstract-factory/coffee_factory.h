#pragma once
#include <memory>
#include "hot_drink.h"
#include "hot_drink_factory.h"

class HotDrink;

class CoffeeFactory : public HotDrinkFactory
{
public:
  std::unique_ptr<HotDrink> make() const override
  {
    return std::make_unique<Coffee>();
  }
};