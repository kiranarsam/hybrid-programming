#pragma once

#include <iostream>
#include <memory>

template <typename T>
class Pimpl
{
private:
  std::unique_ptr<T> impl;
public:
  Pimpl();
  ~Pimpl();

  template <typename ...Args>
  Pimpl(Args&& ...args);

  // pointer
  T* operator->();

  // reference
  T& operator*();
};

// constructor
template<typename T>
Pimpl<T>::Pimpl() : impl{std::make_unique<T>()}
{
  std::cout << "template: Pimpl() \n";
}

// destructor
template<typename T>
Pimpl<T>::~Pimpl()
{
  std::cout << "template: ~Pimpl() \n";
}

// constructor with template
template<typename T>
template<typename... Args>
Pimpl<T>::Pimpl(Args&&... args)
  :impl{ new T{std::forward<Args>(args)... }}
{
  std::cout << "template: Pimpl() && \n";
}

// return pointer
template<typename T>
T *Pimpl<T>::operator->()
{
  std::cout << "template: operator->() \n";
  return impl.get();
}

// return reference
template<typename T>
T &Pimpl<T>::operator*()
{
  std::cout << "template: operator*() \n";
  return *impl.get();
}
