#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <cmath>
#include <iomanip>

// Formula: 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 ..... = Pi/4
double calculatePi(int terms, int start, int skip)
{
  double sum = 0.0;

  for (int i = start; i < terms; i += skip)
  {
    int sign = std::pow(-1, i);
    double term = 1.0 / (2 * i + 1);
    sum += sign * term;
  }

  return sum * 4.0;
}

int main(int argc, char **argv)
{
  std::vector<std::shared_future<double>> futures;
  const int CONCURRENCY = std::thread::hardware_concurrency();

  for(int i = 0; i < CONCURRENCY; i++)
  {
    std::shared_future<double> f = std::async(std::launch::async, calculatePi, 1E6, i, CONCURRENCY);
    futures.push_back(f);
  }

  double sum = 0.0;
  for (auto f : futures)
  {
    sum += f.get();
  }

  std::cout << std::setprecision(15) << "PI : " << M_PI << std::endl;
  std::cout << std::setprecision(15) << "Sum: " << sum << std::endl;

  return 0;
}