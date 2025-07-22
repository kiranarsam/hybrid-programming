// #include "di.h"
#include <cstdio>
#include <iostream>
#include <memory>

using std::make_unique;
using std::make_shared;

class Engine
{
private:
  float volume = 5;
  int horse_power = 400;

  friend std::ostream& operator<<(std::ostream& os, const Engine& obj)
  {
    return os
      << "volume: " << obj.volume
      << " horse_power: " << obj.horse_power;
  }
public:
  Engine() = default;
};

class ILogger
{
public:
  virtual ~ILogger()
  {
  }

  virtual void Log(const std::string& s) = 0;
};

class ConsoleLogger : public ILogger
{
public:
  ConsoleLogger()
  {
  }

  void Log(const std::string& s) override
  {
    std::cout << "LOG:" << s.c_str() << std::endl;
  }
};

class Car
{
  std::unique_ptr<Engine> engine;
  std::shared_ptr<ILogger> logger;
public:
  Car(std::unique_ptr<Engine> engine, const std::shared_ptr<ILogger>& logger)
    : engine{move(engine)},
      logger{logger}
  {
    logger->Log("making a car");
  }

  friend std::ostream& operator<<(std::ostream& os, const Car& obj)
  {
    return os << "car with engine: " << *obj.engine;
  }
};

int main()
{
  // manual
  auto logger = make_shared<ConsoleLogger>();
  auto c = make_shared<Car>(make_unique<Engine>(),logger);

  std::cout << *logger << std::endl;
  std::cout << *c << std::endl;

  // using namespace boost;
  // auto injector = di::make_injector(
  //   di::bind<ILogger>().to<ConsoleLogger>()
  // );
  // auto car = injector.create<std::shared_ptr<Car>>();

  // std::cout << *car << std::endl;

  return 0;
}
