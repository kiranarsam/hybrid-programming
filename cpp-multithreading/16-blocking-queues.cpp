#include <iostream>
#include <thread>

template <typename E>
class BlockingQueue
{
  public:
    void push(E e)
    {
      std::cout << "push" << std::endl;
    }

    void pop()
    {
      std::cout << "pop" << std::endl;
    }
};

int main(int argc, char **argv)
{

  BlockingQueue<int> bqu;

  std::thread t1(&BlockingQueue<int>::push, &bqu, 32);
  std::thread t2(&BlockingQueue<int>::pop, &bqu);

  t1.join();
  t2.join();

  return 0;
}
