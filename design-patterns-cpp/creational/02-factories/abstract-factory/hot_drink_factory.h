#pragma once
#include "hot_drink.h"

class HotDrinkFactory
{
public:
  virtual std::unique_ptr<HotDrink> make() const = 0;
};