#include <iostream>

class MyClass
{
  private:
    int x;
  public:
    MyClass(int n) : x(n) {
      std::cout << "Constructor MyClass" << std::endl;
    }

    ~MyClass() {
      std::cout << "Destructor MyClass" << std::endl;
    }

};


// Placement new operator
// Allocate memory

int main()
{
  int *ptr = new int;
  void *memory = operator new (sizeof(MyClass), ptr);

  MyClass *inst = new (memory) MyClass(42);

  std::cout << "Address of the istance: " << inst << std::endl;

  std::cout << "Address of ptr: " << ptr << std::endl;

  // Destruct the object
  inst->~MyClass();

  // Deallocate Memory
  operator delete(memory);

  return 0;
}