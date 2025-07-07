// Example of passing an lvalue to a function
// which takes an rvalue reference
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Pass by move
// The object passed by the caller is moved into arg
void func(std::vector<std::string>&& arg)
{
	std::cout << "Move: Argument vector has " << arg.size() << " elements" << std::endl;
}

// pass by reference
void func02(std::vector<std::string>& arg)
{
	std::cout << "Reference: Argument vector has " << arg.size() << " elements" << std::endl;
}

// pass by value
void func03(std::vector<std::string> arg)
{
	std::cout << "Value: Argument vector has " << arg.size() << " elements" << std::endl;
}

int main()
{
	std::vector<std::string> vec(1000000);

  func03(vec); // pass by value
  func02(vec); // pass by reference

	std::cout << "Before calling func, vector has " << vec.size() << " elements\n";
	// Casts vec to an rvalue
	func(std::move(vec)); // pass by move
	std::cout << "After calling func, vector has " << vec.size() << " elements\n";

  func(std::move(std::vector<std::string>{"hello", "bye"})); // pass by rvalue reference
}