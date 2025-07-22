#include <iostream>
#include <memory>
#include <map>
#include "hot_drink.h"
#include "drink_factory.h"

std::unique_ptr<HotDrink> make_drink(const std::string& type)
{
  std::unique_ptr<HotDrink> drink;
  if (type == "tea")
  {
    drink = std::make_unique<Tea>();
    drink->prepare(200);
  }
  else
  {
    drink = std::make_unique<Coffee>();
    drink->prepare(50);
  }
  return drink;
}

int main(int argc, char **argv)
{
  auto t = make_drink("tea");
  auto c = make_drink("coffee");

  DrinkFactory df;
  df.make_drink("coffee");

  DrinkWithVolumeFactory dvf;
  dvf.make_drink("tea");
  dvf.make_drink("coffee");

  return 0;
}