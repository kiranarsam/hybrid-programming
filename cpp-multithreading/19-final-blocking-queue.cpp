#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>


template <typename E>
class BlockingQueue
{
  private:
    int _max_size;
    std::queue<E> _queue;
    std::mutex _mtx;
    std::condition_variable _cond;

  public:

    BlockingQueue(int max_size) : _max_size(max_size)
    {

    }

    void push(E e)
    {
      std::unique_lock<std::mutex> lock(_mtx);
      _cond.wait(lock, [this](){ return _queue.size() < _max_size;});

      _queue.push(e);

      lock.unlock();
      _cond.notify_one();
    }

    E front()
    {
      std::unique_lock<std::mutex> lock(_mtx);
      _cond.wait(lock, [this](){ return !_queue.empty(); });

      return _queue.front();
    }

    void pop()
    {
      std::unique_lock<std::mutex> lock(_mtx);
      _cond.wait(lock, [this](){ return !_queue.empty(); });

      _queue.pop();

      lock.unlock();
      _cond.notify_one();
    }

    int size()
    {
      std::lock_guard<std::mutex> lock(_mtx);
      return _queue.size();
    }
};

int main(int argc, char **argv)
{

  BlockingQueue<int> bqu(3);

  std::thread t1([&](){
    for(int i = 0; i < 10; i++)
    {
      std::cout << "Pushing: " << i << std::endl;
      std::cout << "Queue size: " << bqu.size() << std::endl;
      bqu.push(i);
    }

    std::cout << "Thread 1 exited" << std::endl;
  });

  std::thread t2([&](){
    for(int i = 0; i < 10; i++)
    {
      auto item = bqu.front();
      bqu.pop();
      std::cout << "Consumed: " << item << std::endl;
    }
    std::cout << "Thread 2 exited" << std::endl;
  });

  t1.join();
  t2.join();

  return 0;
}
