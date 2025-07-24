#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

template <typename>
struct Observer;

template <typename T>
struct Observable
{
  std::vector<Observer<T>*> observers;
public:
  void notify(T& source, const std::string& field_name)
  {
    for (auto observer : observers)
      observer->field_changed(source, field_name);
  }

  void subscribe(Observer<T>& observer)
  {
    std::stringstream ss;
    ss << std::hex << &observer;
    std::cout << "subscribe = " << ss.str() << "\n";
    observers.push_back(&observer);
  }

  void unsubscribe(Observer<T>& observer)
  {
    observers.erase(
      std::remove(observers.begin(), observers.end(), &observer),
      observers.end()
    );
  }
};
