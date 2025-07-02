#include <iostream>
#include <memory>

int main()
{
  std::shared_ptr<int> sPtr = std::make_shared<int>(11);

  std::cout << "sPtr reference count before assignment to wPtr: " << sPtr.use_count() << std::endl;

  // Create a weak ptr from Shared Pointer
  std::weak_ptr<int> wPtr = sPtr;

  std::cout << "sPtr reference count after assignment to wPtr: " << sPtr.use_count() << std::endl;

  if(wPtr.expired())
  {
    std::cout << "sPtr is no longer managing memory! " << std::endl;
  }
  else
  {
    std::cout << "sPtr is still managing memory! " << std::endl;
  }

  // Use lock() to obtain a shared pointer from the weak pointer
  if( auto ptr = wPtr.lock())
  {
    std::cout << "Value = " << *ptr << std::endl;
  }
  else
  {
    std::cout << "Object no longer exists! " << std::endl;
  }


  return 0;
}