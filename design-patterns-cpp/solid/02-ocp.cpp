/** Open-Closed Principle:
 * 	--> Classes should be open for extension but closed for modification
 */
#include <string>
#include <vector>
#include <iostream>

enum class Color { RED, GREEN, BLUE };
enum class Size { SMALL, MEDIUM, LARGE };

struct Product
{
  std::string name;
  Color color;
  Size size;
};

struct ProductFilter
{
  typedef std::vector<Product *> Items;

  Items by_color(Items items, const Color color)
  {
    Items result;
    for (auto& i : items)
      if (i->color == color)
        result.push_back(i);
    return result;
  }

  Items by_size(Items items, const Size size)
  {
    Items result;
    for (auto& i : items)
      if (i->size == size)
        result.push_back(i);
    return result;
  }

  Items by_size_and_color(Items items, const Size size, const Color color)
  {
    Items result;
    for (auto& i : items)
      if (i->size == size && i->color == color)
        result.push_back(i);
    return result;
  }
};

// forward declaration for AndSpecification
template <typename T>
struct AndSpecification;

// template struct for Specification
template <typename T>
struct Specification
{
  virtual ~Specification() = default;
  virtual bool is_satisfied(T* item) const = 0;
};

// template class for AndSpecification
template <typename T>
struct AndSpecification : Specification<T>
{
  const Specification<T>& first;
  const Specification<T>& second;

  AndSpecification(const Specification<T>& first, const Specification<T>& second)
    : first(first), second(second)
  {
  }

  bool is_satisfied(T *item) const override
  {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};

// template normal function with operator&& (operator overloading with logical AND)
// return type operator&&(first, second){ return return type; }
template <typename T>
AndSpecification<T> operator&& (const Specification<T>& first, const Specification<T>& second)
{
  return { first, second };
}

// Template class for filter
template <typename T>
struct Filter
{
  virtual ~Filter() = default;
  virtual std::vector<T*> filter(std::vector<T*> items, Specification<T>& spec) = 0;
};

// template inherited class from Filter class/struct
struct BetterFilter : Filter<Product>
{
  std::vector<Product*> filter(std::vector<Product*> items, Specification<Product> &spec) override
  {
    std::vector<Product*> result;
    for (auto& p : items)
      if (spec.is_satisfied(p))
        result.push_back(p);
    return result;
  }
};

// color specification class
struct ColorSpecification : Specification<Product>
{
  Color color;

  explicit ColorSpecification(Color color) : color(color)
  {

  }

  bool is_satisfied(Product *item) const override
  {
    return item->color == color;
  }
};

// size specification class
struct SizeSpecification : Specification<Product>
{
  Size size;

  explicit SizeSpecification(const Size size) : size{ size }
  {
  }

  bool is_satisfied(Product* item) const override
  {
    return item->size == size;
  }
};

int main(int argc, char **argv)
{
  Product apple{"Apple", Color::RED, Size::SMALL};
  Product tree{"Tree", Color::GREEN, Size::LARGE};
  Product house{"House", Color::BLUE, Size::LARGE};

  const std::vector<Product*> all_products { &apple, &tree, &house };

  BetterFilter bf;
  ColorSpecification green(Color::GREEN); // Specification by color
  auto green_things = bf.filter(all_products, green);
  for (auto& x : green_things)
    std::cout << x->name << " is green\n";


  SizeSpecification large(Size::LARGE); // specification by size
  AndSpecification<Product> green_and_large(green, large);
  auto big_green_things = bf.filter(all_products, green_and_large);

  for (auto& x : big_green_things)
    std::cout << x->name << " is green and large\n";

  // use the operator instead (same for || etc.)
  auto spec = green && large; // using operator function [  return_type operator&&(first, second) ]
  for (auto& x : bf.filter(all_products, spec))
    std::cout << x->name << " is green and large\n";

  // warning: the following will compile but will NOT work
  auto spec2 = SizeSpecification{Size::LARGE} &&
               ColorSpecification{Color::BLUE};
  return 0;
}