#include <cmath>
#include <iostream>

enum class PointType
{
  CARTESIAN,
  POLAR
};

class Point
{
  /*Point(float a, float b, PointType type = PointType::cartesian)
  {
    if (type == PointType::cartesian)
    {
      x = a; y = b;
    }
    else
    {
      x = a*cos(b);
      y = a*sin(b);
    }
  }*/

  // use a factory method
  Point(float x, float y) : x(x), y(y){}
public:
  float x, y;

  friend class PointFactory;

  friend std::ostream& operator << (std::ostream& os, const Point& obj)
  {
    return os << obj.x << "," << obj.y;
  }
};

class PointFactory
{
public:
  static Point NewCartesian(float x, float y)
  {
    return Point{ x,y };
  }

  static Point NewPolar(float r, float theta)
  {
    return Point{ r*cos(theta), r*sin(theta) };
  }
};

int main(int argc, char **argv)
{
  Point p = PointFactory::NewCartesian(5,4);

  std::cout << p << std::endl;

  return 0;
}
