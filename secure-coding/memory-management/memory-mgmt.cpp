#include <iostream>

using namespace std;

class MyClass
{
  public:
    MyClass() {
      cout << "Constructor MyClass" << endl;
    }

    ~MyClass() {
      cout << "Destructor MyClass" << endl;
    }

};

int main()
{
  MyClass *obj1 = new MyClass;
  MyClass *objArray = new MyClass[3];


  delete obj1;
  delete [] objArray;
  return 0;
}