// Example of parallel execution policy with data race
// Requires C++17 compiler
#include <algorithm>
#include <vector>
#include <iostream>
#include <execution>
#include "print_output.h"

void execPar()
{
  std::vector<int> vec(20'000);
	int count = 0;

  // Data Race: below for_each, will execute on different threads
  // Data Race
	std::for_each(std::execution::par, vec.begin(), vec.end(),
		[&count] (int& x) { x = ++count; }
		);

	print_forrange<int>(vec);
}

void execSeq()
{
  std::vector<int> vec{ 3, 1, 4, 1, 5, 9 };
	// Sort the elements of vec in reverse order
	std::sort(std::execution::seq, vec.begin(), vec.end(),
                                     [](int a, int b) {
                                         return b < a;
	                                  });

	print_forrange<int>(vec);
}

void execParUnseq()
{
  std::vector<int> vec{ 3, 1, 4, 1, 5, 9 };
	// Sort the elements of vec in reverse order
	std::sort(std::execution::par_unseq, vec.begin(), vec.end(),
                                     [](int a, int b) {
                                         return b < a;
	});

	print_forrange<int>(vec);
}

// C++20
void execUnseq()
{
  std::vector<int> vec{ 3, 1, 4, 1, 5, 9 };
	// Sort the elements of vec in reverse order
	std::sort(std::execution::unseq, vec.begin(), vec.end(),
                                     [](int a, int b) {
                                         return b < a;
	});

	print_forrange<int>(vec);
}

int main() {

  execPar();
  execSeq();
  execParUnseq();
  execUnseq();

  return 0;
}