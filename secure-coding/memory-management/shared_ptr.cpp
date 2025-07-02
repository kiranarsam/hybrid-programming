#include <iostream>
#include <memory>

int main()
{

  // Creates a shared pointer and allocate memory for an array of integers
  std::shared_ptr<int[]> ptr = std::make_shared<int[]>(5);

  // Access the values
  for (int i = 0; i < 5; i++)
  {
    ptr[i] = i * 10;
    std::cout << ptr[i] << " ";

  }
  std::cout << std::endl;


  // No need to call delete, memory is automatically deallocated when last shared ptr goes out of scope

  return 0;
}
