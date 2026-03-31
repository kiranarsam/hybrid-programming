#include <iostream>

int main() {
    size_t i {0};  // Iterator

    while (i < 100000) {
        // std::cout << "i : " << i << std::endl;
        ++i;
    }
    std::cout << "Done!, i: " << i << std::endl;

    return 0;
}