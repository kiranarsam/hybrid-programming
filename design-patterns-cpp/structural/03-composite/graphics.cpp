#include <iostream>
#include <vector>
#include <memory>

struct GraphicObject
{
  virtual void draw() = 0;
};

struct Circle : GraphicObject
{
  void draw() override
  {
    std::cout << "Circle" << std::endl;
  }
};

struct Group : GraphicObject
{
  std::string name;

  explicit Group(const std::string& name) : name{name}
  {
  }

  void draw() override
  {
    std::cout << "Group " << name.c_str() << " contains:" << std::endl;
    for (auto&& o : objects)
      o->draw();
  }

  std::vector<GraphicObject*> objects;
};

int main(int argc, char **argv)
{
  // Root object
  Group root("root");

  Circle c1;
  root.objects.push_back(&c1);

  Circle c2;
  // Sub group object
  Group subgroup("sub");
  subgroup.objects.push_back(&c2);

  // Added subgroup into group object
  root.objects.push_back(&subgroup);

  // draw
  root.draw();

  return 0;
}