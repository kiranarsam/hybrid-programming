#include <iostream>

void customMemoryHandler()
{
  std::cerr << "Memory Allocation failed, Custom Memory handler called \n";
  std::abort();
}


// try, catch , Error handling
int main()
{
  std::set_new_handler(customMemoryHandler);
  try
  {
    int *ptr = new int[1000000000000000000]; // attempt to allocate huge memory

    // ...

    delete [] ptr;
  }
  catch(const std::bad_alloc &e) // exception bad_alloc thrown by new operator
  {
    std::cerr << "Memory Allocation Failed: " << e.what() << '\n';
  }
  catch(const std::exception& e)
  {
    std::cerr << "Exception Occured: " << e.what() << '\n';
  }

  return 0;
}