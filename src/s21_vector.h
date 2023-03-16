#ifndef _vector_
#define _vector_

#include <memory>
#include <stdexcept>
#include <iterator>
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

        friend void swap_vb(vector_base<T, A>& first, vector_base<T, A>& second) {
          std::swap(first.elem, second.elem);
          std::swap(first.space, second.space);
          std::swap(first.last, second.last);
        }
    };

  template<typename T, typename A = std::allocator<T>>
  class vector {
      vector_base<T, A> vb;
    public:
      typedef A allocator_type;
      typedef typename A::value_type value_type;
      typedef typename A::reference reference;
      typedef typename A::const_reference const_reference;
      typedef typename A::difference_type difference_type;
      typedef typename A::size_type size_type;

      // how to implement it?
      class iterator {
        public:
          typedef typename A::difference_type difference_type;
          typedef typename A::value_type value_type;
          typedef typename A::reference reference;
          typedef typename A::pointer pointer;
          typedef std::random_access_iterator_tag iterator_category;

          iterator();
          iterator(const iterator&);
          ~iterator();

          iterator& operator=(const iterator&);
          bool operator==(const iterator&) const;
          bool operator!=(const iterator&) const;
          bool operator<(const iterator&) const; // +-
          bool operator>(const iterator&) const; // +-
          bool operator<=(const iterator&) const; // +-
          bool operator>=(const iterator&) const; // +-

          iterator& operator++();
          iterator operator++(int); // +-
          iterator& operator--(); // +-
          iterator operator--(int); // +-
          iterator& operator+=(size_type); // +-
          iterator operator+(size_type); // +-
          friend iterator operator+(size_type, const iterator&); // +-
          iterator& operator-=(size_type); // +-
          iterator operator-(size_type) const; // +-
          difference_type operator-(iterator); // +-

          reference operator*() const;
          pointer operator->() const;
          reference operator[](size_type) const; // +-
      };
      class const_iterator {
        public:
          typedef typename A::difference_type difference_type;
          typedef typename A::value_type value_type;
          typedef typename A::const_reference reference;
          typedef typename A::const_pointer pointer;
          typedef std::random_access_iterator_tag iterator_category;

          const_iterator();
          const_iterator(const const_iterator&);
          const_iterator(const iterator&);
          ~const_iterator();

          const_iterator& operator=(const const_iterator&);
          bool operator==(const const_iterator&) const;
          bool operator!=(const const_iterator&) const;
          bool operator<(const const_iterator&) const; // +-
          bool operator>(const const_iterator&) const; // +-
          bool operator<=(const const_iterator&) const; // +-
          bool operator>=(const const_iterator&) const; // +-

          const_iterator& operator++();
          const_iterator operator++(int);
          const_iterator operator--(int); // +-
          const_iterator& operator+=(size_type); // +-
          const_iterator operator+(size_type); // +-
          friend const_iterator operator+(size_type, const const_iterator&); // +-
          const_iterator& operator-=(size_type); // +-
          const_iterator operator-(size_type) const; // +-
          difference_type operator-(const_iterator); // +-

          reference operator*() const;
          pointer operator->() const;
          reference operator[](size_type) const; // +-

      };

      typedef typename iterator::pointer pointer;
      typename const_iterator::pointer const_pointer;

      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

/*1*/ vector() : vb() {}
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
        swap_vb(vb, other.vb);
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

      // Maybe i should think about iterators to do this

      /* template<typename InputIt> */
      /* void assign(InputIt first, InputIt last) { */
      /*   std::cout << "ASDASDD"; */ 
      /* } */

      void assign (std::initializer_list<T> ilist) { *this = ilist; }

      allocator_type get_allocator() const noexcept { return vb.alloc; }

      reference at(size_type pos) {
        if (!(pos < size())) throw std::out_of_range("argument is out of vector range");
        return vb.elem[pos];
      }

      const_reference at(size_type pos) const {
        if (!(pos < size())) throw std::out_of_range("argument is out of vector range");
        return vb.elem[pos];
      }

      reference operator[](size_type pos) { return vb.elem[pos]; }

      const_reference operator[](size_type pos) const { return vb.elem[pos]; }

      reference front() { return *vb.elem; }

      const reference front() const { return *vb.elem; }

      reference back() { return *(vb.space - 1); }

      const_reference back() const { return *(vb.space - 1); }

      pointer data() noexcept { return vb.elem; }

      const_pointer data() const noexcept { return vb.elem; }

      // need to rework this totally!!!!
      // need class iterator inside vector because i.g, when i work with reverse
      // iterators ++operation means --operation !!
      iterator begin() noexcept { return vb.elem; }
      const_iterator begin() const noexcept { return vb.elem; }
      const_iterator cbegin() const noexcept { return vb.elem; }

      iterator end() noexcept { return vb.space; }
      const_iterator end() const noexcept { return vb.space; }
      const_iterator cend() const noexcept { return vb.space; }

      iterator rbegin() noexcept { return vb.space - 1; }

      const_iterator rbegin() const { return vb.space - 1; }

      const_iterator crbegin() const noexcept { return vb.space - 1; }

      iterator rend() noexcept { return vb.elem - 1; }

      const_iterator rend() const { return vb.elem - 1; }

      const_iterator crend() const noexcept { return vb.elem - 1; }
      // REWORK ITERATORS //




      bool empty() const noexcept {return !size();};

      size_type size() const noexcept { return vb.space - vb.elem; }

      size_type max_size() const { return vb.alloc.max_size();}

      void reserve(size_type newalloc) {
        if (newalloc <= capacity()) return;

        vector_base<T, A> b {vb.alloc, newalloc};
        std::uninitialized_copy(vb.elem, vb.elem + size(), b.elem);
        b.space = b.elem + size();
        swap_vb(vb, b);
      }

      size_type capacity() const noexcept { return vb.last - vb.elem; }

      void shrink_to_fit() {
        if (!(vb.last > vb.space)) return;

        vector_base<T, A> tmp (vb.alloc, size());
        std::uninitialized_copy(vb.elem, vb.space, tmp.elem);
        swap_vb(vb, tmp);
      }

      void clear() noexcept { resize(0); }

      // IMPLEMENT THIS AFTER CORRECT ITERATORS
                // inserts value before pos
      /* iterator insert(const_iterator pos, const_reference value) { */
      /* } */

                // inserts value before pos
      /* iterator insert(const_iterator pos, T&& value) { */
      /* } */

            //  inserts count copies of the value before pos.
      /* iterator insert(const_iterator pos, size_type count, const_reference value) { */
      /* } */

          // inserts elements from range [first, last) before pos. 
      /* template<class InputIt> */
      /*   iterator insert(const_iterator pos, InputIt first, InputIt last) { */
      /*   } */

          // inserts elements from initializer list ilist before pos.
      /* iterator insert(const_iterator pos, std::initializer_list<T> ilist) { */
      /* } */
/* Causes reallocation if the new size() is greater than the old capacity(). */
/* If the new size() is greater than capacity(), all iterators and references */
/* are invalidated. Otherwise, only the iterators and references before the insertion */
/* point remain valid. The end() iterator is also invalidated. */ 


      /* template<class... Args> */
      /*   iterator emplace(const_iterator pos, Args&&... args) { */
      /*   } */

      // removes the element at pos
      /* iterator erase(const_iterator pos) { */
      /* } */

      // removes the elements in the range [first, last)
      /* iterator erase (const_iterator first, const_iterator last) { */
      /* } */

      void push_back(const T& value) {
        if (capacity() == size())
          reserve(size() ? size() * 2 : 1);
        vb.alloc.construct(&vb.elem[size()], value);
        ++vb.space;
      }

      // code duplication, how to do it correctly ? 
      void push_back(T&& value) {
        /* std::cout << "!\n"; */
        if (capacity() == size())
          reserve(size() ? size() * 2 : 1);
        vb.alloc.construct(&vb.elem[size()], value);
        ++vb.space;
      }

      /* template<class... Args> */
      /*   reference emplace_back(Args&&... args); */

      void pop_back() {
        if (size())
          vb.alloc.destroy(&vb.elem[size() - 1]);
        if (vb.space != nullptr)
          --vb.space;
      }

      void resize(size_type newsize) {
        resize(newsize, T());
      }

      void resize(size_type newsize, const_reference value) {
        // thow length_error is newsize > max_size()
        // what to do with -1 ? 
        reserve(newsize > capacity() && capacity() ? capacity() * 2 : newsize);
        if (size() < newsize) {
          std::uninitialized_fill(vb.elem + size(), vb.elem + newsize, value);
        } else {
          for (pointer p = vb.elem + newsize; p != vb.elem + size(); ++p)
            vb.alloc.destroy(p);
        }
        vb.space = vb.elem + newsize;
      }

      // it can be incorrect, because of:
      // Если get_allocator() == other.get_allocator(), то она выполняется за
      // постоянное время, в противном случае она выполняет большое число присвоений
      // элементов, а конструктор вызывается количество раз, пропорциональное числу
      // элементов в двух управляемых последовательностях
      void swap(vector& other) noexcept {
        swap_vb(vb, other.vb);
        std::swap(vb.alloc, other.vb.alloc);
      }


  };

} // namespace s21

#endif  // _vector_
