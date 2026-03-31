#include <iostream>

int main() {
    const int COUNT {0};
    size_t i {0};  // Iterator declaration

    do {
        std::cout << i << " : I love C++" << std::endl;
        ++i;  // Incrementation
    } while (i < COUNT);

    return 0;
}