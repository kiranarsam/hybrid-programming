#include <iostream>

int *max_return_pointer(int *a, int *b) {
    if (*a > *b) {
        return a;
    } else {
        return b;
    }
}

int *max_input_by_value(int a, int b) {
    if (a > b) {
        // warning: address of local variable ‘a’ returned [-Wreturn-local-addr]
        return &a;  // Pointer to local variable returned
    } else {
        // warning: address of local variable ‘b’ returned [-Wreturn-local-addr]
        return &b;  // Pointer to local variable returned
    }
}

int *sum(int *a, int *b) {
    int result = *a + *b;
    // warning: address of local variable ‘result’ returned [-Wreturn-local-addr]
    return &result;  // Pointer to local variable returned
}

int main() {
    int x {56};
    int y {45};
    int *p_max = max_return_pointer(&x, &y);

    std::cout << "x : " << x << std::endl;
    std::cout << "y : " << y << std::endl;
    std::cout << "*p_max : " << *p_max << std::endl;

    ++(*p_max);

    std::cout << "-----" << std::endl;
    std::cout << "x : " << x << std::endl;
    std::cout << "y : " << y << std::endl;
    std::cout << "*p_max : " << *p_max << std::endl;

    int x2 {56};
    int y2 {45};
    int *p_sum = sum(&x2, &y2);
    //  std::cout << *p_sum << std::endl; // Segmentation fault (core dumped)

    int x3 {56};
    int y3 {45};
    int *p_sum3 = max_input_by_value(x3, y3);
    // std::cout << *p_sum3 << std::endl; // Segmentation fault (core dumped)

    std::cout << "Done!" << std::endl;

    return 0;
}