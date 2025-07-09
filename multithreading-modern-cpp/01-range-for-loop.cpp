// Example of range-for loop
#include <iostream>
#include <vector>
#include "print_output.h"

int main()
{
	std::vector<int> vec{4, 2, 3, 5, 1};

	std::cout << "Vector elements before: ";
	print_forrange<int>(vec);

	// We need to use a reference to modify the elements
	for (auto& i : vec) {
		i += 2;
	}

	std::cout << "Vector elements after: ";
	print_forrange<int>(vec);
	return 0;
}