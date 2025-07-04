#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <cmath>

std::mutex g_mtx;

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

int work(int id)
{
  std::unique_lock<std::mutex> lock(g_mtx);
  std::cout << "Starting: " << id << std::endl;
  lock.unlock();
  int seconds = int((5.0 * rand())/RAND_MAX + 2);
  std::this_thread::sleep_for(std::chrono::seconds(seconds));

  return id;
}

int main(int argc, char **argv)
{
  BlockingQueue<std::shared_future<int>> futures(2); // at any time 3 threads are in working in pool
  int num_pools = 20;

  std::thread td([&](){
    for(int i = 0; i < num_pools; i++)
    {
      std::shared_future<int> f = std::async(std::launch::async, work, i);
      futures.push(f);
    }
  });


  for(int i = 0; i < num_pools; i++)
  {
    auto f = futures.front();
    auto result = f.get();
    futures.pop();
    std::cout << "Returned async future value: " << result << std::endl;
  }

  td.join();

  return 0;
}