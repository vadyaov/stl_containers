#ifndef _STL_CONTAINERS_CONTAINERS_STACK_H_
#define _STL_CONTAINERS_CONTAINERS_STACK_H_

#include <iostream>

#include "list.h"
#include "vector.h"

namespace s21 {

// LIFO - Last In First Out
template <class T, class Container = vector<T>>
class stack {
 public:
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

  stack() : c{} {}

  explicit stack(const Container& cont) : c{cont} {}

  explicit stack(std::initializer_list<value_type> init) : c{init} {}

  stack(const stack& other) : c{other.c} {}

  stack& operator=(const stack& other) {
    c = other.c;
    return *this;
  }

  stack(stack&& other) noexcept : c{std::move(other.c)} {}

  stack& operator=(stack&& other) {
    c = std::move(other.c);
    return *this;
  }

  ~stack() = default;

  reference top() { return c.back(); }

  const_reference top() const { return c.back(); }

  bool empty() const { return c.empty(); }

  size_type size() const { return c.size(); }

  void push(const value_type& value) { c.push_back(value); }

  void push(value_type&& value) { c.push_back(std::move(value)); }

  template <class... Args>
  void emplace(Args&&... args) {
    c.emplace_back(std::forward<Args>(args)...);
  }

  void pop() { c.pop_back(); }

  void swap(stack& other) noexcept { std::swap(c, other.c); }

  void print() {
    for (auto i : c) std::cout << " " << i;
    std::cout << std::endl;
  }

 private:
  Container c;
};
}  // namespace s21

#endif  // _STL_CONTAINERS_CONTAINERS_STACK_H_
