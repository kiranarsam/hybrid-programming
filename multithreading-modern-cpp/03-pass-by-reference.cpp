// Example of a function argument which is an rvalue reference
#include <iostream>
#include <string>

// The caller's object will be moved into x
void func(int && x)
{
	std::cout << "Rvalue reference" << std::endl;
}

void func(std::string &name)
{
  std::cout << "Name = " << name << std::endl;
}

int main()
{
	func(2); // R-value reference

  int y = 2;
	//func(y);      // Error! Must be a moveable rvalue

  std::string name = "John";
  func(name); // Pass-by-Reference.

  return 0;
}