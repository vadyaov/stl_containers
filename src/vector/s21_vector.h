#ifndef _vector_
#define _vector_

#include <memory>
#include <exception>
#include <iostream>

namespace s21 {

  template<typename T, typename A = std::allocator<T>>
    class vector_base {
      public:
        T* elem;
        T* space;
        T* last;
        A alloc;

        vector_base() : elem{nullptr},
                        space{nullptr},
                        last{nullptr},
                        alloc{A()} {}

        explicit vector_base(const A& a) noexcept : elem{nullptr},
                                                    space{nullptr},
                                                    last{nullptr},
                                                    alloc{a} {}

        vector_base(const A& a, typename A::size_type n) : alloc{a} {
          elem = alloc.allocate(n);
          space = last = elem + n;
        }
        
        vector_base(const vector_base&) = delete;
        vector_base& operator=(const vector_base&) = delete;

        vector_base(vector_base&& other) noexcept : vector_base() {
          swap(*this, other);
        }

        vector_base(vector_base&& other, const A& a) noexcept : vector_base() {
          swap(*this, other);
          alloc = a;
        }

        /* vector_base& operator=(vector_base&& other) noexcept { */
        /*   std::swap(*this, other); */
        /*   return *this; */
        /* } */

        ~vector_base() { alloc.deallocate(elem, last - elem); }

        friend void swap(vector_base<T, A>& first, vector_base<T, A>& second) {
          std::swap(first.elem, second.elem);
          std::swap(first.space, second.space);
          std::swap(first.last, second.last);
        }
    };

  template<typename T, typename A = std::allocator<T>>
  class vector {
      vector_base<T, A> vb;
    public:
      using size_type = std::size_t;
      using value_type = T;
      using allocator_type = A;

      using reference = value_type&;
      using const_reference = const value_type&;

      using pointer = typename std::allocator_traits<A>::pointer;
      using const_pointer = typename std::allocator_traits<A>::const_pointer;

      using iterator = value_type*;
      using const_iterator = const value_type*;

      /* using reverse_iterator = std::reverse_iterator<iterator>; */

      using difference_type = std::ptrdiff_t;

/*1*/ vector() : vb{} {}
/*2*/ explicit vector(const A& a) noexcept : vb{a} {} // +
/*3*/ explicit vector(size_type count, const T& value = T(),
                      const A& a = A()) : vb{a, count}{
        std::uninitialized_fill(vb.elem, vb.elem + count, value);
      }
/*4*/ explicit vector(size_type count, const A& a) : vb{a, count} {
        std::uninitialized_fill(vb.elem, vb.elem + count, value_type());
      }
/*5*/ /* template<class InputIt> vector( InputIt first, InputIt last, const A& alloc = A() ); */

      // Copy constructor. Constructs the container with the copy of the contents of other.
/*6*/ vector(const vector<value_type, allocator_type>& other) : vb{other.vb.alloc, other.size()} {
        std::uninitialized_copy(other.begin(), other.end(), vb.elem);
      }

      // Constructs the container with the copy of the contents of other, using alloc as the allocator.
/*7*/ vector(const vector& other, const allocator_type& alloc) : vb{alloc, other.size()} {
        std::uninitialized_copy(other.begin(), other.end(), vb.elem);
      }

      // Move constructor. Constructs the container with the contents of other using move semantics.
      // A is obtained by move-construction from the allocator belonging to other.
      // After the move, other is guaranteed to be empty().
/*8*/ vector(vector&& other) noexcept : vb{std::move(other.vb)} {}

/*       // A-extended move constructor. Using alloc as the allocator for the new container, */
/*       // moving the contents from other; if alloc != other.get_allocator(), this results in an element-wise move. */
/*       // (In that case, other is not guaranteed to be empty after the move.) */
/*9*/ vector(vector&& other, const A& alloc) : vb{std::move(other.vb), alloc} {}

      // Constructs the container with the contents of the initializer list init.
/*10*/vector(std::initializer_list<T> init, const A& alloc = A()) : vb {alloc, init.size()} {
        std::uninitialized_copy(init.begin(), init.end(), vb.elem);
      }

      ~vector() {
        for (pointer p = vb.elem; p != vb.space; ++p)
          vb.alloc.destroy(p);
      }

      vector& operator=(const vector& other) {
        if (capacity() < other.size()) {
          vector tmp{other};
          std::swap(*this, tmp);
          return *this;
        }

        if (this == &other) return *this;

        size_type sz = size();
        size_type osz = other.size();
        vb.alloc = other.vb.alloc;
        if (osz <= sz) {
          std::copy(other.begin(), other.begin() + osz, vb.elem);
          for (pointer p = vb.elem + osz; p != vb.space; ++p)
            vb.alloc.destroy(p);
        } else {
          std::copy(other.begin(), other.begin() + sz, vb.elem);
          std::uninitialized_copy(other.begin() + sz, other.end(), vb.space);
        }
        vb.space = vb.elem + osz;
        return *this;
      }

      vector& operator=(vector&& other) noexcept {
        clear();
        swap(vb, other.vb);
        other.vb.elem = other.vb.space = other.vb.last = nullptr; // idk about this line, did it for zero capacity after swap
        return *this;
      }

      vector& operator=(std::initializer_list<T> ilist) {
        vector<T, A> tmp{ilist};
        *this = tmp;
        return *this;
      }

      void assign(size_type count, const T& value) {
        vector b {count, value, vb.alloc};
        *this = b;
      }

      /* template<typename InputIt> */
      /* void assign(InputIt first, InputIt last) { */
      /* } */

      size_type size() const { return vb.space - vb.elem; }
      size_type capacity() const { return vb.last - vb.elem; }

      iterator begin() const { return vb.elem; }
      iterator end() const { return vb.space; }

      void reserve(size_type newalloc) {
        if (newalloc <= capacity()) return;

        vector_base<T, A> b {vb.alloc, newalloc};
        std::uninitialized_copy(vb.elem, vb.elem + size(), b.elem);
        b.space = b.elem + size();
        swap(vb, b);
      }

      void resize(size_type newsize, const_reference value = T()) {
        reserve(newsize > capacity() && capacity() ? capacity() * 2 : newsize);
        if (size() < newsize) {
          std::uninitialized_fill(vb.elem + size(), vb.elem + newsize, value);
        } else {
          for (pointer p = vb.elem + newsize; p != vb.elem + size(); ++p)
            vb.alloc.destroy(p);
        }
        vb.space = vb.elem + newsize;
      }

      void clear() { resize(0); }

      void push_back(const T& value) {
        if (capacity() == size())
          reserve(size() ? size() * 2 : 1);
        vb.alloc.construct(&vb.elem[size()], value);
        ++vb.space;
      }

      void pop_back() {
        if (size())
          vb.alloc.destroy(&vb.elem[size() - 1]);
        if (vb.space != nullptr)
          --vb.space;
      }


  };

} // namespace s21

#endif  // _vector_
