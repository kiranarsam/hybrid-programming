#include <iostream>

int main() {
    // Type deduction with auto : Just a copy
    double some_var {55.5};

    auto x = some_var;

    std::cout << "sizeof(some_var) : " << sizeof(some_var) << std::endl;
    std::cout << "sizeof(x) : " << sizeof(x) << std::endl;
    std::cout << "&some_var : " << &some_var << std::endl;
    std::cout << "&x : " << &x << std::endl;
    std::cout << " some_var : " << some_var << std::endl;
    std::cout << " x : " << x << std::endl;

    double some_var2 = 55.5;  // double

    double &some_var_ref {some_var2};

    auto y = some_var_ref;  // y is not deduced as a reference to double
                            // it's just a double that contains the value
                            // in some_var_ref
    ++y;

    std::cout << "sizeof(some_var2) : " << sizeof(some_var2) << std::endl;        // 8
    std::cout << "sizeof(some_var_ref) : " << sizeof(some_var_ref) << std::endl;  // 8
    std::cout << "sizeof(y) : " << sizeof(y) << std::endl;                        // 8
    std::cout << "&some_var2 : " << &some_var2 << std::endl;                      // 0xabc123
    std::cout << "&some_var_ref : " << &some_var_ref << std::endl;                // 0xabc123
    std::cout << "&y : " << &y << std::endl;                                      // 0xaab543
    std::cout << "some_var2 : " << some_var2 << std::endl;                        // 55.5
    std::cout << "some_var_ref : " << some_var_ref << std::endl;                  // 55.5
    std::cout << "y : " << y << std::endl;                                        // 56.5

    // True reference deduction
    double some_var3 = 55.5;  // double
    double &some_var_ref3 {some_var3};

    auto &z = some_var_ref3;  // z is deduced as a double reference
    ++z;

    std::cout << "sizeof(some_var3) : " << sizeof(some_var3) << std::endl;          // 8
    std::cout << "sizeof(some_var_ref3) : " << sizeof(some_var_ref3) << std::endl;  // 8
    std::cout << "sizeof(z) : " << sizeof(z) << std::endl;                          // 8
    std::cout << "&some_var3 : " << &some_var3 << std::endl;                        // 0xabc123
    std::cout << "&some_var_ref3 : " << &some_var_ref3 << std::endl;                // 0xabc123
    std::cout << "&z : " << &z << std::endl;                                        // 0xabc123
    std::cout << "some_var3 : " << some_var3 << std::endl;                          // 56.5
    std::cout << "some_var_ref3 : " << some_var_ref3 << std::endl;                  // 56.5
    std::cout << "z : " << z << std::endl;                                          // 56.5

    // Constness is preserved with properly deduced references.
    const double some_other_var4 {44.3};
    const double &const_ref {some_other_var4};

    auto &p = const_ref;

    std::cout << "some_other_var4 : " << some_other_var4 << std::endl;
    std::cout << "const_ref : " << const_ref << std::endl;
    std::cout << "p : " << p << std::endl;

    //++p; // Compiler error

    std::cout << "some_other_var4 : " << some_other_var4 << std::endl;
    std::cout << "const_ref : " << const_ref << std::endl;
    std::cout << "p : " << p << std::endl;

    // Constness doesn't matter with non reference deduction
    const double i_am_const {71.2};
    const double &my_ref {i_am_const};

    auto q = my_ref;  // q is a separate variable, initialized with the
                      // value in i_am_const.
    ++q;              // Can modify q without a problem. It's a copy.

    return 0;
}