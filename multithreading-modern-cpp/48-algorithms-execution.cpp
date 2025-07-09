// An algorithm's predicate function throws an exception
// The algorithm has an execution policy
#include <algorithm>
#include <vector>
#include <exception>
#include <iostream>
#include <execution>
#include "print_output.h"

namespace se = std::execution;

// predicate with execution policy and throwing exception
void exceptSeq()
{
  std::vector<int> vec{3,1,4,1,5,9};

	try {
		// Predicate throws an exception
		std::sort(se::seq, vec.begin(), vec.end(), [](int a, int b) {
			throw std::out_of_range("Oops"); return true;
		});
	}
	catch (std::exception& e) {
		std::cout << "Caught exception: " << e.what() << '\n';
	}

	print_forrange<int>(vec);
}

// predicate with no execution policy and throws exception
void exceptNoPolicy()
{
  std::vector<int> vec{3,1,4,1,5,9};

  try {
		// Predicate throws an exception
		std::sort(vec.begin(), vec.end(), [](int a, int b) {
			throw std::out_of_range("Oops"); return true;
		});
	}
	catch (std::exception& e) {
		std::cout << "Caught exception: " << e.what() << '\n';
	}

	print_forrange<int>(vec);
}

int main()
{

  // When exception is thrown with execution policy doesn't catch the handler
  // execution policies doesn't apply with throwing exception
  // exceptSeq();
  exceptNoPolicy();

  return 0;
}