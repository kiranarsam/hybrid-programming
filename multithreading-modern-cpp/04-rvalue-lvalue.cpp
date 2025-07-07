// Example of overloading on value type
#include <iostream>

// Define a moveable type
// (The compiler will provide move operators)
class Test {};

// Function which takes lvalue reference
void func(const Test& test)
{
	std::cout << "Lvalue reference\n";
}

// Function which takes rvalue reference
void func(Test&& test) {
	std::cout << "Rvalue reference\n";
}

int main(int argc, char **argv)
{
	Test test;

	std::cout << "Argument is test variable:\t\t";
	func(test); // lvalue reference

	std::cout << "Argument is temporary object:\t\t";
	func(Test()); // rvalue reference

	std::cout << "Argument through std::move():\t\t";
	func(std::move(test)); // rvalue reference
	std::cout << '\n';
  return 0;
}