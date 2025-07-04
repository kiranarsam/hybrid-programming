#include <iostream>
#include <cmath>
#include <iomanip>

// Formula: 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 ..... = Pi/4
double calculatePi(int terms)
{
  double sum = 0.0;

  for (int i = 0; i < terms; i++)
  {
    int sign = std::pow(-1, i);
    double term = 1.0 / (2 * i + 1);
    sum += sign * term;
  }

  return sum * 4.0;
}

int main(int argc, char **argv)
{
  // You can change the input value to get accuracy for calculating PI
  std::cout << "Pi = " << std::setprecision(15) << calculatePi(1E7) << std::endl;
  return 0;
}
