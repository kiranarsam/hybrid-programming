#include <iostream>
#include <memory>

int main()
{

  // Creates a unique pointer and allocate memory for an integer
  std::unique_ptr<int> ptr = std::make_unique<int>(42);

  // Access the values
  std::cout << "Value = " << *ptr << std::endl;

  // No need to call delete, memory is automatically deallocated when ptr goes out of scope

  return 0;
}
