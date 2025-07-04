#include <iostream>
#include <thread>
#include <mutex>

class App
{
  private:
    int count = 0;
    std::mutex mtx;

  public:
    void operator()()
    {
      for(int i = 0; i < 1E6; i++)
      {
        // data synchronization
        std::lock_guard<std::mutex> guard(mtx);
        ++count;
      }
    }

    int getCount()
    {
      return count;
    }
};

int main(int argc, char **argv)
{
  App app;

  std::thread t1(std::ref(app));
  std::thread t2(std::ref(app));

  t1.join();
  t2.join();

  std::cout << "Count = " << app.getCount() << std::endl;
  return 0;
}
