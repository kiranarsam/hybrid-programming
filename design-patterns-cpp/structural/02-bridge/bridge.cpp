#include <iostream>
#include <string>
#include <vector>
#include "person.h"

// Bridge ACTIVITY 1
// person

// Bridge ACTIVITY 2
// two classes of objects
// Renderers - determine how an object is drawn
// Shapes - determine what to draw
class Renderer
{
public:
  virtual void render_circle(float x, float y, float radius) = 0;
};

class VectorRenderer : public Renderer
{
public:
  void render_circle(float x, float y, float radius) override
  {
    std::cout << "Rasterizing circle of radius " << radius << std::endl;
  }
};

class RasterRenderer : public Renderer
{
public:
  void render_circle(float x, float y, float radius) override
  {
    std::cout << "Drawing a vector circle of radius " << radius << std::endl;
  }
};

class Shape
{
protected:
  Renderer& renderer;

  Shape(Renderer& renderer) : renderer{ renderer } {}

public:
  virtual void draw() = 0; // implementation specific
  virtual void resize(float factor) = 0; // abstraction specific
};

class Circle : public Shape
{
  float x, y, radius;

public:
  Circle(Renderer& renderer, float x, float y, float radius)
    : Shape{renderer},
      x{x},
      y{y},
      radius{radius}
  {
  }

  void draw() override
  {
    renderer.render_circle(x, y, radius);
  }

  void resize(float factor) override
  {
    radius *= factor;
  }
};

// normal function, bridge. render is bridge, how to draw an object
void bridge()
{
  RasterRenderer rr;
  Circle raster_circle{ rr, 5,5,5 };
  raster_circle.draw();
  raster_circle.resize(2);
  raster_circle.draw();
}

int main()
{
  // pimpl
  // binary interfaces are fragile; this removes most of the internals to a separate class
  // prevents recompilation of sources reliant on the header

  Person p;
  p.greet();

  bridge();

  return 0;
}
