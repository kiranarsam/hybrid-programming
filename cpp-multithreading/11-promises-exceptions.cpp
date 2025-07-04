#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <iomanip>
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
  std::promise<double> promise;

  auto do_calculatePi = [&](int terms){
    try
    {
      auto result = calculatePi(terms);
      promise.set_value(result);
    }
    catch(...)
    {
      promise.set_exception(std::current_exception());
    }
  };

  std::thread t1(do_calculatePi, 1E6);


  std::future<double> future = promise.get_future();

  try
  {
    std::cout << "Pi = " << std::setprecision(15) << future.get() << std::endl;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  t1.join();

  return 0;
}
