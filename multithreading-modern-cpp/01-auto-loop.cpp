// Example of loop using the "auto" type specifier
#include <iostream>
#include <vector>
#include "print_output.h"

int main()
{
	std::vector<int> vec{4, 2, 3, 5, 1};

	for (auto it = vec.begin(); it != vec.end(); ++it) {
		*it += 2;
	}

	std::cout << "Vector elements: ";
	print_for<int>(vec);
}