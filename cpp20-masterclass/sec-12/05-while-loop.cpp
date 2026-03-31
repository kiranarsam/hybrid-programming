#include <iostream>

int main() {
    const size_t COUNT {10};
    size_t i {0};  // Iterator declaration

    while (i < COUNT) {  // Test
        std::cout << i << " : I love C++" << std::endl;
        ++i;  // Incrementation
    }
    return 0;
}