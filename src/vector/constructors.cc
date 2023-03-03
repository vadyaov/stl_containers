#include "s21_vector.h"

using namespace s21;

template <typename T, typename A>
vector<T, A>::vector() : elem{nullptr},
                         space{nullptr},
                         last{nullptr},
                         alloc{A()} {
}

template <typename T, typename A>
vector<T, A>::vector(const A& a) noexcept : elem{nullptr}, space{nullptr}, last{nullptr}, alloc{a} {}

template <typename T, typename A>
vector<T,A>::vector(size_type count, const T& value, const A& a) : alloc{a} {
  elem = alloc.allocate(count);
  if (count)
    try {
      std::uninitialized_fill(elem, elem + count, value);
      space = last = elem + count;
    } catch (...) {
      alloc.deallocate(elem, count);
      throw;
    }
}
