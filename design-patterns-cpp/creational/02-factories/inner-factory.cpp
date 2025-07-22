#include <cmath>
#include <iostream>

class Point
{
private:
  // use a factory method
  Point(float x, float y) : x(x), y(y) {}

  class PointFactory
  {
    PointFactory() {}
  public:
    static Point NewCartesian(float x, float y)
    {
      return { x,y };
    }
    static Point NewPolar(float r, float theta)
    {
      return{ r*cos(theta), r*sin(theta) };
    }
  };

  friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
    return os
      << "x: " << obj.x
      << " y: " << obj.y;
  }

public:
  float x, y;
  static PointFactory Factory;
};

int main()
{
  // will not work
  // Point p{ 1,2 };

  // nope!
  // Point::PointFactory pf;

  // if factory is public, then
  //auto p = Point::PointFactory::NewCartesian(3, 4);

  // at any rate, use this
  auto pp = Point::Factory.NewCartesian(2, 3);

  std::cout << pp << std::endl;

  return 0;
}