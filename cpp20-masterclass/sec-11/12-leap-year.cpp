#include <iostream>

bool isLeapYear(unsigned int year) {
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
        is_leap = true;
    } else {
        is_leap = false;
    }

    return is_leap;
}

int main() {
    std::cout << "Is Leap Year: " << isLeapYear(2100) << std::endl;

    return 0;
}