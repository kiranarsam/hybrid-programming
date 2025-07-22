#pragma once
#include <string>
#include "hot_drink.h"
#include "tea_factory.h"
#include "coffee_factory.h"
#include <map>
#include <functional>

class HotDrink;

class DrinkFactory
{
  std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;
public:
  DrinkFactory()
  {
    hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
    hot_factories["tea"] = std::make_unique<TeaFactory>();
  }

  std::unique_ptr<HotDrink> make_drink(const std::string& name)
  {
    auto drink = hot_factories[name]->make();
    drink->prepare(200); // oops!
    return drink;
  }
};

class DrinkWithVolumeFactory
{
  std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;
public:

  DrinkWithVolumeFactory()
  {
    factories["tea"] = [] {
      auto tea = std::make_unique<Tea>();
      tea->prepare(200);
      return tea;
    };

    factories["coffee"] = [] {
      auto tea = std::make_unique<Tea>();
      tea->prepare(50);
      return tea;
    };
  }

  std::unique_ptr<HotDrink> make_drink(const std::string& name);
};

inline std::unique_ptr<HotDrink> DrinkWithVolumeFactory::make_drink(const std::string& name)
{
  return factories[name]();
}
