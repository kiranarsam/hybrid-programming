#ifndef __PRINT_OUTPUT_H_
#define __PRINT_OUTPUT_H_
#include <vector>

template <typename T>
void print_for(std::vector<T> &vec)
{
	for (auto it = vec.begin(); it != vec.end(); ++it)
  {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;
}

template <typename T>
void print_forrange(std::vector<T> &vec)
{
	for (auto& it : vec)
  {
    std::cout << it << ", ";
  }
  std::cout << std::endl;
}

#endif /*__PRINT_OUTPUT_H_*/