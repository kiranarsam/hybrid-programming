#include <iostream>

class App
{
  public:
    // this method is callable object
    void operator () () {
      std::cout << "From Callable: operator()() " << std::endl;
    }
};

int main(int argc, char **argv)
{
  App app;

  // below line invovkes App::operator()()
  app();

  return 0;
}