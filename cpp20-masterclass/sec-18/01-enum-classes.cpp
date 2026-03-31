#include <iostream>

// Declare an enum type
// The default type associated with enum classes with C++ is int
// unsigned char : 0 ~ 255
enum class Month : char {
    Jan = -1,
    January = Jan,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct = 100,
    Nov,
    Dec
};

int main() {
    Month month {Month::Jan};
    std::cout << "month : " << static_cast<int>(month) << std::endl;                    // -1
    std::cout << "Month::January : " << static_cast<int>(Month::January) << std::endl;  // -1
    std::cout << "Month::Feb : " << static_cast<int>(Month::Feb) << std::endl;          // 0
    std::cout << "Month::Mar : " << static_cast<int>(Month::Mar) << std::endl;          // 1
    std::cout << "Month::Nov : " << static_cast<int>(Month::Nov) << std::endl;          // 101
    std::cout << "sizeof(month) : " << sizeof(month) << std::endl;                      // 1

    return 0;
}