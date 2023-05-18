#ifndef _ARRAY_H
#define _ARRAY_H

#include <cstddef>
#include <stdexcept>

namespace s21 {
template <class T, std::size_t N>
struct array {
  T a[N]{0};

 public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;

  class iterator;
  class const_iterator;
  class reverse_iterator;
  class const_reverse_iterator;

  constexpr reference at(size_type pos) {
    if (!(pos < size())) throw std::out_of_range("array::at");

    return a[pos];
  }

  constexpr const_reference at(size_type pos) const {
    if (!(pos < size())) throw std::out_of_range("array::at");

    return a[pos];
  }

  constexpr reference operator[](size_type pos) { return a[pos]; }

  constexpr const_reference operator[](size_type pos) const { return a[pos]; }

  constexpr reference front() { return a[0]; }

  constexpr const_reference front() const { return a[0]; }

  constexpr reference back() { return a[N - 1]; }

  constexpr const_reference back() const { return a[N - 1]; }

  constexpr pointer data() noexcept { return a; }

  constexpr const_pointer data() const noexcept { return a; }

  constexpr iterator begin() noexcept { return iterator(a); }

  constexpr const_iterator begin() const noexcept { return const_iterator(a); }

  constexpr const_iterator cbegin() const noexcept { return const_iterator(a); }

  constexpr iterator end() noexcept { return iterator(a + N); }

  constexpr const_iterator end() const noexcept {
    return const_iterator(a + N);
  }

  constexpr const_iterator cend() const noexcept {
    return const_iterator(a + N);
  }

  constexpr bool empty() const noexcept { return size() == 0; }

  constexpr size_type size() const noexcept { return N; }

  void fill(const_reference value) { std::fill(begin(), end(), value); }

  constexpr void swap(array& other) noexcept { std::swap(*this, other); }

  class iterator {
   public:
    iterator() : ptr{nullptr} {}
    explicit iterator(pointer p) : ptr{p} {}
    iterator(const iterator& iter) : ptr{iter.ptr} {}

    iterator& operator=(const iterator& other) {
      ptr = other.ptr;
      return *this;
    }

    bool operator==(const iterator& other) const { return ptr == other.ptr; }
    bool operator!=(const iterator& other) const { return ptr != other.ptr; }

    iterator& operator++() {
      ++ptr;
      return *this;
    }
    iterator& operator--() {
      --ptr;
      return *this;
    }

    iterator operator++(int) {
      iterator tmp{*this};
      ++ptr;
      return tmp;
    }

    iterator operator--(int) {
      iterator tmp{*this};
      --ptr;
      return tmp;
    }

    iterator& operator+=(size_type n) {
      ptr += n;
      return *this;
    }

    iterator operator+(size_type n) const {
      iterator tmp = *this;
      tmp += n;
      return tmp;
    }

    iterator& operator-=(size_type n) {
      ptr -= n;
      return *this;
    }

    iterator operator-(size_type n) const {
      iterator tmp = *this;
      tmp -= n;
      return tmp;
    }

    reference operator*() const { return *ptr; }
    pointer operator->() const { return ptr; }

   private:
    pointer ptr;
  };

  class const_iterator {
   public:
    const_iterator() : ptr{nullptr} {}
    explicit const_iterator(const_pointer p) : ptr{p} {}
    const_iterator(const const_iterator& iter) : ptr{iter.ptr} {}

    const_iterator& operator=(const const_iterator& other) {
      ptr = other.ptr;
      return *this;
    }

    bool operator==(const const_iterator& other) const {
      return ptr == other.ptr;
    }
    bool operator!=(const const_iterator& other) const {
      return ptr != other.ptr;
    }

    const_iterator& operator++() {
      ++ptr;
      return *this;
    }
    const_iterator& operator--() {
      --ptr;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp{*this};
      ++ptr;
      return tmp;
    }

    const_iterator operator--(int) {
      const_iterator tmp{*this};
      --ptr;
      return tmp;
    }

    const_iterator& operator+=(size_type n) {
      ptr += n;
      return *this;
    }

    const_iterator operator+(size_type n) const {
      const_iterator tmp = *this;
      tmp += n;
      return tmp;
    }

    const_iterator& operator-=(size_type n) {
      ptr -= n;
      return *this;
    }

    const_iterator operator-(size_type n) const {
      const_iterator tmp = *this;
      tmp -= n;
      return tmp;
    }

    const_reference operator*() const { return *ptr; }
    const_pointer operator->() const { return ptr; }

   private:
    const_pointer ptr;
  };
};

template <class T, std::size_t N>
bool operator==(const s21::array<T, N>& lhs, const s21::array<T, N>& rhs) {
  for (std::size_t i = 0; i < N; ++i)
    if (lhs[i] != rhs[i]) return false;
  return true;
}

}  // namespace s21

#endif  // _ARRAY_H
