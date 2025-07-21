/**
 * Liskov Substitution Principle:
 * --> You should be able to substitue a base type for a subtype
 *
 * Objects in a program should be replaceable with instances of their subtype
 * w/o altering the correctness of the program
 */
#include <iostream>

class Rectangle
{
protected:
  int width, height;
public:
  Rectangle(const int width, const int height)
    : width{width}, height{height}
  {
  }

  int getWidth() const
  {
    return width;
  }

  virtual void setWidth(const int width)
  {
    this->width = width;
  }

  int getHeight() const
  {
    return height;
  }

  virtual void setHeight(const int height)
  {
    this->height = height;
  }

  int area() const
  {
    return width * height;
  }
};

class Square : public Rectangle
{
public:
  Square(int size): Rectangle(size,size) {}

  void setWidth(const int width) override
  {
    this->width = height = width;
  }

  void setHeight(const int height) override
  {
    this->height = width = height;
  }
};

struct RectangleFactory
{
  static Rectangle createRectangle(int w, int h);
  static Rectangle createSquare(int size);
};

Rectangle RectangleFactory::createRectangle(int w, int h)
{
  Rectangle rect(3,5);
  return rect;
}

Rectangle RectangleFactory::createSquare(int w)
{
  Square square(5);
  return square;
}

void process(Rectangle& r)
{
  int w = r.getWidth();
  r.setHeight(10); // should not be modified from the base, its lsp violation
  /*
  * If r is base, we don't know whether r is rect or square.
  * if we modify any parameter, it might effect or alter other subtype, leads to LSP violation
  */
  std::cout << "expected area = " << (w * 10) << ", got " << r.area() << std::endl;
}

int main(int argc, char **argv)
{
  Rectangle r{ 5,5 };
  process(r);

  Square s{ 5 };
  process(s);

  return 0;
}

/**
 * How to avoid LSP violation:
 * class Shape{};
 * class Rectangle: public Shape{};
 * class Square: public Shape{};
 * This will avoid LSP violation, when one object is modified from base type, it doesn't effect other
 */