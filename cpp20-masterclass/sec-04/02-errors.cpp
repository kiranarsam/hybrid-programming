#include <iostream>

int main(int argc, char **argv) {
    std::cout << "Hello" << std::endl   // compiler error
    int value = 12 / 0;  // runtime error and warning error shown
    return 0;
}