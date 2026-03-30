#include <iostream>
int main() {
	  int value {45};
    std::cout << "The value is : " << value << std::endl;
    value = value + 5;
    //value +=5; // equivalent to value = value + 5
    std::cout << "The value is (after +=5) : " << value << std::endl; // 50
    value -=5; // equivalent to value = value - 5
    std::cout << "The value is (after -=5) : " << value << std::endl; // 45
    value *=2;
    std::cout << "The value is (after *=2) : " << value << std::endl; // 90
    value /= 3;
    std::cout << "The value is (after /=3) : " << value << std::endl; // 30
    value %= 11;
    std::cout << "The value is (after %=11) : " << value << std::endl;// 8
    return 0;
}