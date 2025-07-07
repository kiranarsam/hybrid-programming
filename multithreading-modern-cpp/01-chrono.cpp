// Example of intervals in std::chrono
#include <chrono>
#include <iostream>

// Namespace alias to simplify the code
namespace sc = std::chrono;

int main()
{
	// Interval types defined in the std::chrono library
	sc::seconds(2);                              // 2 second interval
	std::chrono::milliseconds(20);               // 20 millisecond interval
	std::chrono::microseconds(50);               // 50 microsecond interval
  std::cout << "std::chrono::milliseconds(20) = " << std::chrono::milliseconds(20).count() << std::endl;

	// Literal suffixes added in C++14
	using namespace std::literals;
	2s;
	20ms;
	50us;
  std::cout << "20s = " << (20s).count() << std::endl; // output = 20
  std::cout << "20ms = " << (20ms).count() << std::endl; // output = 20
  std::cout << "20us = " << (20us).count() << std::endl; // output = 20
}