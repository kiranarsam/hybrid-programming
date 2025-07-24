#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <sstream>
#include <iostream>
#include <algorithm>

template <typename>
struct Observer;

template <typename T>
struct SaferObservable
{
  std::vector<Observer<T>*> observers;
  typedef std::recursive_mutex mutex_t;
  mutex_t mtx;
public:
  void notify(T& source, const std::string& field_name)
  {
    std::scoped_lock<mutex_t> lock{mtx};
    for (auto observer : observers) {
      if (observer) {
        observer->field_changed(source, field_name);
      }
    }
  }

  void subscribe(Observer<T>& observer)
  {
    std::scoped_lock<mutex_t> lock{mtx};
    std::stringstream ss;
    ss << std::hex << &observer;
    std::cout << "SaferObservable: subscribe = " << ss.str() << "\n";
    observers.push_back(&observer);
  }

  void unsubscribe(Observer<T>& observer)
  {
    // storage and remove need to be changed to map or unordered map
    auto it = std::find(std::begin(observers), std::end(observers), &observer);
    if (it != end(observers)) {
      *it = nullptr;
    }

    // std::scoped_lock<mutex_t> lock{mtx};
    // observers.erase(std::remove(observers.begin(), observers.end(), &observer), observers.end());
  }
};
