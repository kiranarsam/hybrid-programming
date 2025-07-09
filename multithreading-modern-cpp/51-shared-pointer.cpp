// Operations on std::shared_ptr
#include <memory>
#include <iostream>
#include <thread>
#include <mutex>

void basicSharedPointer()
{
// Pass a pointer as the constructor argument
	std::shared_ptr<int> ptr1(new int(42));

	// Calling std::make_shared() is better
	auto ptr2 = std::make_shared<int>(42);

	// Can be dereferenced
	std::cout << *ptr1 << '\n';

	// Pointer arithmetic is not supported
	// ++ptr1;

	// Assignment, copying and moving are allowed
	ptr1 = ptr2;
	std::shared_ptr<int> ptr3(ptr2);
	std::shared_ptr<int> ptr4(std::move(ptr2));

	// Releases the allocated memory
	ptr1 = nullptr;
}


// std::shared_ptr and thread safety
// Operations which only affect the reference counter are safe
// and do not need to be synchronized
// std::shared_ptr has an "atomic" reference counter
std::shared_ptr<int> shptr = std::make_shared<int>(42);

void func1()
{
    // Increments shared_p's reference counter - safe
    std::shared_ptr<int> shp1 = shptr;
}

void func2()
{
    // Increments shared_p's reference counter - safe
    std::shared_ptr<int> shp2 = shptr;
}

// std::shared_ptr and thread safety
// Operations which affect the pointed-to data are not safe
// They must be synchronized
// Mutex to protect std::shared_ptr's data
std::mutex mut;
void func11()
{
	// Potentially conflicting access - must be protected
	std::lock_guard<std::mutex> lgd(mut);
	*shptr = 5;
}

void func22()
{
	// Potentially conflicting access - must be protected
	std::lock_guard<std::mutex> lgd(mut);
	*shptr = 7;
}

int main()
{

  basicSharedPointer();

  std::thread thr1(func1);
	std::thread thr2(func2);
	thr1.join();
	thr2.join();

  std::cout << "shptr data: " << *shptr << '\n';

	std::thread thr11(func11);
	std::thread thr22(func22);

	thr11.join();
	thr22.join();

	std::cout << "shptr data: " << *shptr << '\n';

  return 0;
}