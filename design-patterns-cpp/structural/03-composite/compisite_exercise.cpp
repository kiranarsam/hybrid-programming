#include <iostream>
#include <string>
#include <vector>
#include <numeric>

// Same interface is used for respective classes, which have similar outcomes
struct ContainsIntegers
{
  virtual int sum() = 0;
};

struct SingleValue : ContainsIntegers
{
  int value{ 0 };

  SingleValue() = default;

  explicit SingleValue(const int value)
    : value{value}
  {
  }

  // Same interface
  int sum() override {
    return value;
  }
};

struct ManyValues : std::vector<int>, ContainsIntegers
{
  void add(const int value)
  {
    push_back(value); // this is vector api
  }

  // Same interface
  int sum() override {
    return std::accumulate(begin(), end(), 0);
  }
};

int sum(const std::vector<ContainsIntegers*> items)
{
  int result{0};
  for (auto item : items) {
    result += item->sum();
  }
  return result;
}

int main(int argc, char* argv[])
{
  SingleValue single_value{ 11 };
  ManyValues other_values;
  other_values.add(22);
  other_values.add(33);

  auto res = sum({ &single_value, &other_values });
  std::cout << "Res = " << res << "\n";

  return 0;
}