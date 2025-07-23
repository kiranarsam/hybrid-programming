#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
using namespace std;

struct Flower
{
  virtual string str() = 0;
};

struct Rose : Flower
{
  string str() override {
    return "A rose";
  }
};

struct RedFlower : Flower
{
  Flower& flower;

  RedFlower(Flower &flower) : flower(flower) {}

  string str() override
  {
    string s = flower.str();

    if (s.find("red") != string::npos) {
      return s;
    }
    else if (s.find("blue") != string::npos) {
      return s + " and red";
    }
    else {
      return s + " that is red";
    }
  }
};

struct BlueFlower : Flower
{
  Flower& flower;

  BlueFlower(Flower &flower) : flower(flower) {}

  string str() override
  {
    string s = flower.str();

    if (s.find("blue") != string::npos) {
      return s;
    }
    else if (s.find("red") != string::npos) {
      return s + " and blue";
    }
    else {
      return s + " that is blue";
    }
  }
};

int main(int ac, char* av[])
{
  Rose rose;
  BlueFlower blue_rose{rose};
  RedFlower red_rose{rose};

  std::cout << rose.str() << "\n";

  std::cout << blue_rose.str() << "\n";

  std::cout << red_rose.str() << "\n";

  std::cout << RedFlower{red_rose}.str() << " *** "
            << "This rose was made red twice, but you should print once."  << "\n";

  std::cout << BlueFlower{red_rose}.str() << "\n";

  std::cout << RedFlower{blue_rose}.str()  << "\n";

  BlueFlower b_r_rose{red_rose};
  RedFlower r_b_r_rose{b_r_rose};
  std::cout << r_b_r_rose.str() << "\n *** \n"
    << "This is a complicated case. I'm expecting that "
    << "a rose defined as Red{Blue{Red{Rose{}}}} is printed "
    << "as 'red and blue'."  << "\n";

  return 0;
}