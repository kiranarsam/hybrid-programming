#include <functional>
#include <iostream>

class SingletonTester
{
public:
  template <typename T>
  bool is_singleton(std::function<T*()> factory)
  {
    T* _1 = factory();
    T* _2 = factory();
    return _1 == _2;
  }
};

int main(int ac, char** argv)
{
  SingletonTester tester;
  auto test1 = tester.is_singleton<SingletonTester>([&]() { return &tester; });
  std::cout << "Test1: Is Singleton " << test1 << "\n";

  auto test2 = tester.is_singleton<SingletonTester>([]() { return new SingletonTester{}; });
  std::cout << "Test2: Is Singleton " << test2 << "\n";
  return 0;
}
