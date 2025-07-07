// Example of a loop in traditional C++
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vec{4, 2, 3, 5, 1};

  std::cout << "Vector Before Elements: ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << ", ";
  std::cout << std::endl;

	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		*it += 2;

	std::cout << "Vector After Elements: ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << ", ";

  std::cout << std::endl;
}