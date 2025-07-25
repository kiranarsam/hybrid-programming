// Algorithm call with predicate
// Uses lambda expression with capture
#include <iostream>
#include <algorithm>
#include <vector>
#include "print_output.h"

int main() {
	std::vector<int> vec{4, 2, 3, 5, 1};

	std::cout << "Elements of vector: ";
	print_forrange<int>(vec);

	int radix = 3;

	// Call std::count_if() algorithm using a lambda expression as predicate
	auto n_even = std::count_if(vec.begin(), vec.end(),
		// The lambda captures radix by value
		[radix] (int n)
		{
			return (n % radix == 0);
		});

	std::cout << "The vector has " << n_even << " element(s) which are exact multiples of " << radix << '\n';
	return 0;
}