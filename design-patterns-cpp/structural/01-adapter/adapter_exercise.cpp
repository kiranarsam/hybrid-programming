#include <iostream>

class Square
{
  int side{ 0 };
public:
  explicit Square(const int side) : side(side) {  }

  int getSide() const {
    return side;
  }
};

class Rectangle
{
public:
  virtual int width() const = 0;
  virtual int height() const = 0;

  int area() const {
    return width() * height();
  }
};

class SquareToRectangleAdapter : public Rectangle
{
  const Square& square;
public:
  SquareToRectangleAdapter(const Square& square) : square(square) {}

  int width() const override
  {
    return square.getSide();
  }

  int height() const override
  {
    return square.getSide();
  }
};

int main(int argc, char** argv)
{
  Square sq{ 11 };
  SquareToRectangleAdapter adapter{ sq };
  std::cout << adapter.area() << std::endl;
  return 0;
}