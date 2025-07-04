#include <iostream>
#include <thread>
#include <cmath>
#include <future>
#include <exception>

// Formula: 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 ..... = Pi/4
double calculatePi(int terms)
{
  double sum = 0.0;

  if (terms < 1)
  {
    throw std::runtime_error("Terms should be more than 1");
  }

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
  std::packaged_task<double(int)> task1(calculatePi);

  std::future<double> future = task1.get_future();

  // std::thread t1(std::ref(task1), 1E6); // this also works fine
  std::thread t1(std::move(task1), 1E6);

  try
  {
    auto result = future.get();
    std::cout << "Pi = " << result << std::endl;
  }
  catch(const std::exception& e)
  {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }

  t1.join();

  return 0;
}