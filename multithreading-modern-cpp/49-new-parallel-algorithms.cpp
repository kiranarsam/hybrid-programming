#include <numeric>
#include <iostream>
#include <vector>
#include <execution>
#include "print_output.h"

// Example of std::accumulate()
void algoAccumulate()
{
  std::vector<int> vec { 0, 1, 2, 3, 4, 5, 6, 7 };

	std::cout << "Vector elements: ";
	print_forrange<int>(vec);

	// Sum the elements of vec, using initial value 0
	// Performed in left-to-right order, one addition at a time
	// ((((0 + 1) + 2) + 3) + ...)
	auto sum = std::accumulate(vec.begin(), vec.end(), 0);

	std::cout << "The sum of the elements is " << sum << '\n';
}

// Example of std::reduce()
void algoReduce()
{
  std::vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7};

	std::cout << "Vector elements: ";
	print_forrange<int>(vec);

	// Sum the elements of vec, using initial value 0
	// Performed as four parallel additions
	// ((0 + 1) + (2 + 3) + (4 + 5) + (6 + 7))
	auto sum = std::reduce(std::execution::par, vec.begin(), vec.end(), 0);

	std::cout << "The sum of the elements is " << sum << '\n';
}

// Example of std::partial_sum()
void algoPartialSum()
{
  std::vector<int> vec { 1, 2, 3, 4} ;
	std::vector<int> vec2(vec.size());

	// The elements of vec2 will be { 1, 1 + 2, 1 + 2 + 3, 1 + 2 + 3 + 4 };
	// vec2 will contain { 1, 3, 6, 10 };
	std::partial_sum(vec.begin(), vec.end(), vec2.begin());

	std::cout << "Vector elements: ";
	print_forrange<int>(vec);

	std::cout << "Elements of partial sum vector: ";
	print_forrange<int>(vec2);
}

// Example of std::inclusive_scan()
void algoInclusiveScan()
{
  std::vector<int> vec{ 1, 2, 3, 4 };
	std::vector<int> vec2(vec.size());

	// The elements of vec2 will be { 1, 1 + 2, 1 + 2 + 3, 1 + 2 + 3 + 4 };
	// vec2 will contain { 1, 3, 6, 10 };
	std::inclusive_scan(std::execution::par, vec.begin(), vec.end(), vec2.begin());

	std::cout << "Vector elements: ";
	print_forrange<int>(vec);

	std::cout << "Elements of inclusive scan vector: ";
	print_forrange<int>(vec2);
}

// Example of std::exclusive_scan()
void algoExclusiveScan()
{
  std::vector<int> vec{ 1, 2, 3, 4 };
	std::vector<int> vec2(vec.size());

	// The elements of vec2 will be { -1, 1 + (-1), 1 + 2 + (-1), 1 + 2 + 3 + (-1) }
	// vec2 will contain { -1, 0, 2, 5 };
	std::exclusive_scan(std::execution::par_unseq, vec.begin(), vec.end(), vec2.begin(), -1);

	// This is equivalent to
	std::vector<int> vec3 { -1, 1, 2, 3 };
	std::vector<int> vec4(vec.size());
	std::inclusive_scan(vec3.begin(), vec3.end(), vec4.begin());

	std::cout << "Vector elements: ";
	print_forrange<int>(vec);

	std::cout << "Elements of exclusive scan vector: ";
	print_forrange<int>(vec2);

	std::cout << "Elements of inclusive scan vector: ";
	print_forrange<int>(vec4);
}

//Example of std::inner_product()
void algoInnerProduct()
{
  std::vector<int> x{1, 2, 3, 4, 5};
	std::vector<int> y{5, 4, 3, 2, 1};

	auto result = std::inner_product(x.begin(), x.end(),    // Iterator range for first vector
                                                y.begin(),  // Start of second vector
                                                0);         // Initial value of sum

	std::cout << "First vector:  ";
	print_forrange<int>(x);

	std::cout << "Second vector: ";
	print_forrange<int>(y);

	std::cout << "Result is " << result << '\n';            // Displays 35
}

//Example for std::transform()
void algoTransform()
{
  std::vector<int> vec{1, 2, 3, 4};
	std::vector<int> vec2;

	// Double each element of vec and store the results in vec2
	std::transform(vec.begin(), vec.end(),
	               std::back_inserter(vec2),
        	       [] (int n) {return 2*n;}
	);

	// Display the input vector
	std::cout << "Input vector:  ";
	print_forrange<int>(vec);

	// Display the output vector
	std::cout << "Output vector: ";
	print_forrange<int>(vec2);
}

// Example for std::transform Binary
void algoTransformBinary()
{
  std::vector<int> vec{1, 2, 3, 4};
	std::vector<int> vec2{5, 6, 7, 8};
	std::vector<int> vec3;

	// Add each element in v to the corresponding element in v2 and store the result in v3
	std::transform(vec.begin(), vec.end(),
				   vec2.begin(),
		           std::back_inserter(vec3),
		           [](int n1, int n2) {return n1 + n2;}
	);

	// Display the first input vector
	std::cout << "First input vector:  ";
	print_forrange<int>(vec);

	// Display the second input vector
	std::cout << "Second input vector: ";
	print_forrange<int>(vec2);

	// Display the output vector
	std::cout << "Output vector: ";
	print_forrange<int>(vec3);
}

//Example for std::transform_reduce()
void algoTransformReduce()
{
  std::vector<int> x{1, 2, 3, 4, 5};
	std::vector<int> y{5, 4, 3, 2, 1};

	auto result = std::transform_reduce(std::execution::par,              // Execution policy
										x.begin(), x.end(),   // Iterator range for first vector
                                        y.begin(),            // Start of second vector
                                        0);                   // Initial value of sum

	std::cout << "First vector:  ";
	print_forrange<int>(x);

	std::cout << "Second vector: ";
	print_forrange<int>(y);

	std::cout << "Result is " << result << '\n';            // Displays 35
}

// Example for std::transform_reduce() with + and - operator overloaded
void algoTransformReduceWithPlusMinusOper()
{
  std::vector<double> expected{ 0.1, 0.2, 0.3, 0.4, 0.5 };
	std::vector<double> actual{ 0.09, 0.22, 0.27, 0.41, 0.52 };

	auto max_diff = std::transform_reduce(std::execution::par,
                                          begin(expected), end(expected),
                                          begin(actual),

                                          // Initial value for the largest difference
                                          0.0,

                                          //  "Reduce" operation
                                          [](auto diff1, auto diff2){ return std::max(diff1, diff2); },

                                          // "Transform" operation
                                          [](auto exp, auto act) { return std::abs(act-exp); }
	);

	std::cout << "Max difference is: " << max_diff << '\n';
}

int main()
{
  algoAccumulate();
  algoReduce();
  algoPartialSum();
  algoInclusiveScan();
  algoExclusiveScan();

  algoInnerProduct();
  algoTransform();
  algoTransformBinary();
  algoTransformReduce();

  algoTransformReduceWithPlusMinusOper();

  return 0;
}