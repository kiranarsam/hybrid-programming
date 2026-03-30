#include <iostream>

// consteval ==> c++20
consteval int get_value() {
  return 3;
}

int main(int argc, char* argv[]) {
  constexpr int value = get_value(); // no errors seen, if compiled with c++20
  std::cout << "value: " << value << std::endl;
  return 0;
}

// Compile with c++20
// g++ -std=c++20 01-first.cpp
