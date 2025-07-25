#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <functional>
#include <string>

#include "circular_buffer.hpp"

#define MAXIMUM_BUFFER_SIZE 10U

/**
 * Only one handle should be enabled based on application needs.
 * Otherwise, buffer checks every 5ms and execute the tasks.
 */
// #define ENABLE_SOCKET_PAIR_HANDLE  // Using socket pair to handle the tasks in buffer
// #define ENABLE_PIPE_HANDLE         // Using pipes to handle the tasks in buffer
// #define ENABLE_COND_VAR_HANDLE     // Using conditional variable to handle the tasks in buffer

struct ThreadInputData
{
  const char* name;
  uint32_t stack_size;
  uint32_t priority;
  bool joinable;
  uint32_t num_threads;
};

class ThreadPool;

struct ThreadContext
{
  ThreadContext() = default;
  ThreadContext(const ThreadContext& other) = default;
  ThreadContext(ThreadContext&& other) = default;
  ThreadContext& operator=(const ThreadContext& other) = default;
  ThreadContext& operator=(ThreadContext&& other) = default;

  ThreadPool *pool;
  uint32_t id;
  const char* name;
  uint32_t priority;
  bool joinable;
  pthread_t thread;
#if defined(ENABLE_SOCKET_PAIR_HANDLE) || defined(ENABLE_PIPE_HANDLE)
  int fd[2];
  struct pollfd poll_fds[1];
#endif
};

typedef void *(*FuncTask)(void *);

class ThreadPool final
{
public:
  ThreadPool() : m_terminate_threads(false)
  {
#if defined(ENABLE_SOCKET_PAIR_HANDLE) || defined(ENABLE_PIPE_HANDLE)
    m_next_thread = 0U;
#endif
	}

  ThreadPool(const ThreadPool &other) = delete;
  ThreadPool(ThreadPool &&other) = delete;
  ThreadPool &operator=(const ThreadPool &other) = delete;
  ThreadPool &operator=(ThreadPool &&other) = delete;

  ~ThreadPool() { terminateThreads(); }

  void initialize(ThreadInputData &data)
  {
    uint32_t max_buffer = data.num_threads * MAXIMUM_BUFFER_SIZE;
    m_buffer.resize(max_buffer);
    m_context.resize(data.num_threads);

    for(uint32_t idx = 0U; idx < data.num_threads; idx++) {
      pthread_attr_t attrs;
      if (pthread_attr_init(&attrs) != 0) {
        std::cout << "pthread_attr_init() failed \n";
      }

      if(data.stack_size > 1000U) {
        if (pthread_attr_setstacksize(&attrs, data.stack_size) != 0) {
          std::cout << "pthread_attr_setstacksize() failed; size = " << data.stack_size << " \n";
        }
      }

      if(data.joinable) {
        if (pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE) != 0) {
          std::cout << "pthread_attr_setdetachstate() failed \n";
        }
      } else {
        if (pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED) != 0) {
          std::cout << "pthread_attr_setdetachstate() failed \n";
        }
      }

      std::string thread_name = "";
      thread_name = std::string(data.name) + "_" + std::to_string(idx);
      auto &context = m_context[idx];
      context.id = idx;
      context.name = thread_name.c_str();
      context.joinable = data.joinable;
      context.priority = data.priority;

      initializeHandles(context);

      if (pthread_create(&(m_context[idx].thread), &attrs, &ThreadPool::run, &m_context[idx]) != 0) {
        std::cout << "pthread_create() failed \n";
      }

      if (pthread_attr_destroy(&attrs) != 0) {
        std::cout << "pthread_attr_destroy() failed \n";
      }
    }
  }

  void terminateThreads()
  {
    if (!m_terminate_threads)
    {
      m_terminate_threads = true;

#ifdef ENABLE_COND_VAR_HANDLE
      m_cond_var.notify_all();
#endif

      uint32_t idx = 0;
      for(auto &data : m_context) {
#if defined(ENABLE_SOCKET_PAIR_HANDLE) || defined(ENABLE_PIPE_HANDLE)
        close(data.fd[0]);
        close(data.fd[1]);
#endif
        if(data.joinable) {
          if ( pthread_join(data.thread, nullptr) != 0) {
            std::cout << "pthread_join() failed \n";
          }
        }
        ++idx;
      }

      m_buffer.clear();
      m_context.clear();
    }
  }

  std::future<void *> addTask(FuncTask &&func, void *arg)
  {
    std::unique_lock<std::mutex> lock(m_mtx);
    if (m_terminate_threads) {
      lock.unlock();
      return dummyTask();
    }

    if (m_buffer.full()) {
      lock.unlock();
      return dummyTask();
    }

    std::packaged_task<void *()> task(
      std::bind(std::forward<FuncTask>(func), std::forward<void *>(arg))
    );

    std::future<void *> future = task.get_future();
    m_buffer.push(std::move(task));
    lock.unlock();

#ifdef ENABLE_COND_VAR_HANDLE
    m_cond_var.notify_one();
#elif defined(ENABLE_SOCKET_PAIR_HANDLE) || defined(ENABLE_PIPE_HANDLE)
    uint32_t m_next_thread_index = (m_next_thread++) % m_context.size();
    char buffer = '1';
    write(m_context[m_next_thread_index].fd[1], &buffer, 1);
#endif
    return future;
  }

private:
  static void* run(void* arg)
  {
    ThreadContext *data = static_cast<ThreadContext *>(arg);
    Worker worker(std::move(*data));
    worker();
    return nullptr;
  }

  std::future<void *> dummyTask()
  {
    std::promise<void *> promise;
    std::future<void *> future = promise.get_future();
    promise.set_value(nullptr);
    return future;
  }

  class Worker final
  {
  private:
    ThreadContext m_data;
    ThreadPool *m_pool;
    uint32_t m_id;
  public:
    Worker(ThreadContext &&data) noexcept : m_data(std::move(data))
    {
      m_pool = m_data.pool;
      m_id = m_data.id;
    }

    void operator()()
    {
        bool ret = false;
        while (!ret)
        {
#ifdef ENABLE_COND_VAR_HANDLE
            ret = processTasks();
#elif defined(ENABLE_SOCKET_PAIR_HANDLE) || defined(ENABLE_PIPE_HANDLE)
            ret = processTasksWithoutCondVar();
#else
            ret = processTasks();
            usleep(5000); // 5 ms
            std::unique_lock<std::mutex> lock(m_pool->m_mtx);
            ret = m_pool->m_terminate_threads;
            lock.unlock();
#endif
        }
    }

private:

    bool processTasks()
    {
      bool ret = false;
      std::packaged_task<void *()> taskFunc;
      std::unique_lock<std::mutex> lock(m_pool->m_mtx);
#ifdef ENABLE_COND_VAR_HANDLE
      m_pool->m_cond_var.wait(lock, [this]() {
        return !m_pool->m_buffer.empty() || m_pool->m_terminate_threads;
      });

      if (m_pool->m_terminate_threads) {
        lock.unlock();
        return true;
      }
#endif
      if (!m_pool->m_buffer.empty()) {
        taskFunc = std::move(m_pool->m_buffer.front());
        m_pool->m_buffer.pop();
      }

      lock.unlock();
      if (taskFunc.valid()) {
          taskFunc();
      }
      return ret;
    }

#if defined(ENABLE_SOCKET_PAIR_HANDLE) || defined(ENABLE_PIPE_HANDLE)
    bool processTasksWithoutCondVar()
    {
      bool ret = false;
      int ret = poll(m_data.poll_fds, 1, 500);
      if (ret < 0) {
        std::cout << "Error polling pipe" << std::endl;
        return true;
      }

      std::unique_lock<std::mutex> lock(m_pool->m_mtx);
      if (m_pool->m_terminate_threads) {
        lock.unlock();
        return true;
      }

      if ((ret > 0) && (m_data.poll_fds[0].revents & POLLIN)) {
        char buffer;
        read(m_data.fd[0], &buffer, 1);
        ret = processTasks();
      }
      return ret;
    }
#endif
  };

  void initializeHandles(ThreadContext &data)
  {
#ifdef ENABLE_SOCKET_PAIR_HANDLE
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, data.fd) == -1) {
      std::cout << "Error creating socket pairs" << std::endl;
      return;
    }

#elif defined(ENABLE_PIPE_HANDLE)
    if (pipe(data.fd) == -1)
    {
      std::cout << "Error creating pipe" << std::endl;
      return;
    }

    if(fcntl(data.fd[0], F_SETFL, O_NONBLOCK) == -1) {
      std::cout << "Error seting fcntl on read file descriptor" << std::endl;
      return;
    }
#endif

#if defined(ENABLE_SOCKET_PAIR_HANDLE) || defined(ENABLE_PIPE_HANDLE)
    data.poll_fds[0].fd = data.fd[0];
    data.poll_fds[0].events = POLLIN;
#endif
    data.pool = this;
  }

  CircularBuffer<std::packaged_task<void *()>> m_buffer;
  std::vector<ThreadContext> m_context;
#ifdef ENABLE_COND_VAR_HANDLE
  std::condition_variable m_cond_var;
#endif
  std::mutex m_mtx;
#if defined(ENABLE_SOCKET_PAIR_HANDLE) || defined(ENABLE_PIPE_HANDLE)
  uint32_t m_next_thread;
#endif
  bool m_terminate_threads;
};

static void * hello1(void *arg)
{
  std::cout << "From Hello One \n";
  return nullptr;
}

static void * hello2(void *arg)
{
  std::cout << "From Hello Two \n";
  return nullptr;
}

/**
 * Thread Input Data:
 * Number of threads can be created per instance of thread pool.
 */
std::vector<ThreadInputData> items {
  {
    "Thread_01",
    51200U,
    120U,
    true,
    1
  },
  {
    "Thread_02",
    51200U,
    121U,
    true,
    2
  }
};

class Application
{
public:
  Application() {
    // Initializing data related to thread pool only
    tp.initialize(::items[0]);
  }

  void run() {
    auto fut1 = tp.addTask(hello1, this);
    auto fut2 = tp.addTask(hello2, this);

    fut1.get();
    fut2.get();
  }

private:
  // Once instance of thread pool
  ThreadPool tp;
};

int main(int argc, char **argv)
{
  Application app;
  app.run();

  return 0;
}
