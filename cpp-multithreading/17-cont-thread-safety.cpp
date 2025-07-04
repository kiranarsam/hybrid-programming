#include <iostream>
#include <thread>
#include <queue>

// There is thread-safety in this example.
// Will add in next continued sample

template <typename E>
class BlockingQueue
{
  private:
    int _max_size;
    std::queue<E> _queue;

  public:

    BlockingQueue(int max_size) : _max_size(max_size)
    {

    }

    void push(E e)
    {
      _queue.push(e);
    }

    int pop()
    {
      auto ele = _queue.front();
      _queue.pop();
      return ele;
    }
};

int main(int argc, char **argv)
{

  BlockingQueue<int> bqu(10);

  std::thread t1([&](){
    for(int i = 0; i < 10; i++)
    {
      bqu.push(i);
    }
  });

  std::thread t2([&](){
    for(int i = 0; i < 10; i++)
    {
      auto item = bqu.pop();
      std::cout << "Consumed = " << item << std::endl;
    }
  });

  t1.join();
  t2.join();

  return 0;
}
