#ifndef _vector_
#define _vector_

#include <memory>
#include <iostream>

namespace s21 {

  template<typename T, typename A = std::allocator<T>>
    class vector_base {
      public:
        T* elem;  // начало выделяемой памяти
        T* space; // начало области памяти для расширения, конец последовательности элементов
        T* last;  // конец выделенной памяти
        A alloc;  // аллокатор для запрашивания памяти под элементы

        vector_base() : elem{nullptr}, space{nullptr}, last{nullptr}, alloc{A()} {}

        explicit vector_base(const A& a) noexcept : elem{nullptr}, space{nullptr}, last{nullptr}, alloc{a} {}

        vector_base(const A& a, typename A::size_type n) : alloc{a} {
          elem = alloc.allocate(n);
          space = elem + n;
          last = elem + n;
        }

        ~vector_base() {alloc.deallocate(elem, last - elem);}
        
        vector_base(const vector_base&) = delete; // no copy operations
        vector_base& operator=(const vector_base&) = delete;

        vector_base(vector_base&& other) noexcept : alloc{other.alloc}, elem{other.elem}, space{other.space}, last{other.last} {
          other.elem = other.last = other.space = nullptr;
        }

        vector_base& operator=(vector_base&& other) noexcept {
          std::swap(*this, other);
          return *this;
        }
    };

  template<typename T, typename A = std::allocator<T>>
  class vector {
      vector_base<T, A> vb;
      void destroy_elements() {
        for (T* p = vb.elem; p != vb.space; ++p)
          p->~T();
      }
    public:
      using size_type = unsigned int;
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
      // Default constructor. Constructs an empty container with a default-constructed allocator.
      vector() : vb{} {}

      // Constructs an empty container with the given allocator alloc.
      explicit vector(const A& a) noexcept : vb{a} {} // +

/*       // Constructs the container with count copies of elements with value value. */
      explicit vector(size_type count, const T& value = T(), const A& a = A()) : vb{a, count} {
        std::uninitialized_fill(vb.elem, vb.elem + count, value);
      }

      // Constructs the container with count default-inserted instances of T. No copies are made.
      explicit vector(size_type count, const A& a) : vb{a, count} {
        std::uninitialized_fill(vb.elem, vb.elem + count, T());
      }

/*       // Constructs the container with the contents of the range [first, last). */ 
/*       template<class InputIt> vector( InputIt first, InputIt last, const A& alloc = A() ); */

      // Copy constructor. Constructs the container with the copy of the contents of other.
      vector(const vector<T, A>& other) : vb{other.alloc, other.size()} {
        std::uninitialized_copy(other.begin(), other.end(), vb.elem);
      }

      // Constructs the container with the copy of the contents of other, using alloc as the allocator.
      vector(const vector& other, const A& alloc) : vb{alloc, other.size()} {
        std::uninitialized_copy(other.begin(), other.end(), vb.elem);
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
          for (T* p = vb.elem + osz; p != vb.space; ++p)
            p->~T();
        } else {
          std::copy(other.begin(), other.begin() + sz, vb.elem);
          std::uninitialized_copy(other.begin() + sz, other.end(), vb.space);
        }
        vb.space = vb.elem + osz;
        return *this;
      }

      // Move constructor. Constructs the container with the contents of other using move semantics.
      // A is obtained by move-construction from the allocator belonging to other.
      // After the move, other is guaranteed to be empty().
      vector(vector&& other) noexcept : vb{std::move(other.vb)} {} // +

/*       // A-extended move constructor. Using alloc as the allocator for the new container, */
/*       // moving the contents from other; if alloc != other.get_allocator(), this results in an element-wise move. */
/*       // (In that case, other is not guaranteed to be empty after the move.) */
/*       vector(vector&& other, const A& alloc); */

      vector& operator=(vector&& other) noexcept {
        // clear(); // need to implement
        /* vb = std::move(other.vb); */
        std::swap(*this, other); // this mb instead of previous line
        return *this;
      }

/*       // Constructs the container with the contents of the initializer list init. */
/*       vector(std::initializer_list<T> init, const A& alloc = A()); */

      ~vector() {destroy_elements();}

      size_type size() const { return vb.space - vb.elem; }
      size_type capacity() const { return vb.last - vb.elem; }

      iterator begin() { return vb.elem; }
      iterator end() { return vb.space; }

      void reserve(size_type newalloc) {
        if (newalloc <= capacity()) return;

        vector_base<T, A> b {vb.alloc, newalloc};
        std::uninitialized_copy(vb.elem, vb.elem + size(), b.elem);
        b.space = b.elem + size();
        std::swap(vb.elem, b.elem);
        std::swap(vb.space, b.space);
        std::swap(vb.last, b.last);
      }
/*       void resize(size_type, T = {}); // изменяем число элементов */
/*       void clear(){resize(0);} // опустошаем вектор */
/*       void push_back(const T&); // добавляем элемент в конец */
/*       void pop_back(); // удаляем элемент с конца */

  };

} // namespace s21

#endif  // _vector_
