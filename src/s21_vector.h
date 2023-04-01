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

        vector_base(vector_base&& other) noexcept : elem{other.elem}, space{other.space}, last{other.last}, alloc{other.alloc} {
          other.elem = nullptr;
          other.space = nullptr;
          other.last = nullptr;
        }

        vector_base(vector_base&& other, const A& a) noexcept : elem{other.elem}, space{other.space}, last{other.last}, alloc{a} {
          other.elem = nullptr;
          other.space = nullptr;
          other.last = nullptr;
        }

        vector_base& operator=(vector_base&& other) noexcept {
          elem = other.elem;
          space = other.space;
          last = other.last;
          alloc = other.alloc;

          other.elem = nullptr;
          other.space = nullptr;
          other.last = nullptr;

          return *this;
        }

        ~vector_base() { alloc.deallocate(elem, last - elem); }
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

      class iterator {
        public:
          typedef typename A::difference_type difference_type;
          typedef typename A::value_type value_type;
          typedef typename A::reference reference;
          typedef typename A::pointer pointer;
          typedef std::random_access_iterator_tag iterator_category;

          iterator() : ptr{nullptr} {}
          explicit iterator(pointer p) : ptr {p} {}
          iterator(const iterator& iter) : ptr{iter.ptr} {}
          ~iterator() { ptr = nullptr; }

          iterator& operator=(const iterator& other) { ptr = other.ptr; return *this; }
          bool operator==(const iterator& other) const { return ptr == other.ptr; }
          bool operator!=(const iterator& other) const { return ptr != other.ptr; }
          bool operator<(const iterator& other) const { return ptr < other.ptr; }
          bool operator>(const iterator& other) const { return ptr > other.ptr; }
          bool operator<=(const iterator& other) const { return ptr <= other.ptr; }
          bool operator>=(const iterator& other) const { return ptr >= other.ptr; }

          iterator& operator++() { ++ptr; return *this; }
          iterator operator++(int) { iterator tmp = *this; ++ptr; return tmp; }
          iterator& operator--() { --ptr; return *this; }
          iterator operator--(int) { iterator tmp = *this; --ptr; return tmp; }
          iterator& operator+=(size_type n) { ptr += n; return *this; }
          iterator operator+(size_type n) const { iterator tmp = *this; tmp += n; return tmp; }

          iterator& operator-=(size_type n) { ptr -= n; return *this; }
          iterator operator-(size_type n) const { iterator tmp = *this; tmp -= n; return tmp; }
          difference_type operator-(iterator other) { return ptr - other.ptr; }
          reference operator*() const { return *ptr; }
          pointer operator->() const { return ptr; }

          reference operator[](size_type n) const { return *(ptr + n); }
        private:
          pointer ptr;
      };

      class const_iterator {
        public:
          typedef typename A::difference_type difference_type;
          typedef typename A::value_type value_type;
          typedef typename A::const_reference reference;
          typedef typename A::const_pointer pointer;
          typedef std::random_access_iterator_tag iterator_category;

          const_iterator() : ptr {nullptr} {}
          explicit const_iterator(pointer p) : ptr{p} {}
          const_iterator(const const_iterator& other) : ptr{other.ptr} {}
          explicit const_iterator(const iterator& other) : ptr{other.ptr} {}
          ~const_iterator() { ptr = nullptr; }

          const_iterator& operator=(const const_iterator& other) { ptr = other.ptr; return *this; }
          bool operator==(const const_iterator& other) const { return ptr == other.ptr; }
          bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }
          bool operator<(const const_iterator& other) const { return ptr < other.ptr; }
          bool operator>(const const_iterator& other) const { return ptr > other.ptr; }
          bool operator<=(const const_iterator& other) const { return ptr <= other.ptr; }
          bool operator>=(const const_iterator& other) const { return ptr >= other.ptr; }

          const_iterator& operator++() { ++ptr; return *this; }
          const_iterator operator++(int) { const_iterator tmp{*this}; ++ptr; return tmp; }
          const_iterator& operator--() { --ptr; return *this; }
          const_iterator operator--(int) { const_iterator tmp{*this}; --ptr; return tmp; }
          const_iterator& operator+=(size_type n) { ptr += n; return *this; }
          const_iterator operator+(size_type n) { const_iterator tmp{*this}; tmp += n; return tmp; }

          const_iterator& operator-=(size_type n) { ptr -= n; return *this; }
          const_iterator operator-(size_type n) const { const_iterator tmp{*this}; tmp -= n; return tmp; }
          difference_type operator-(const_iterator other) { return ptr - other.ptr; }
          reference operator*() const { return *ptr; }
          pointer operator->() const { return ptr; }
          reference operator[](size_type n ) const { return *(ptr + n); }
        private:
          pointer ptr;
      };

      class reverse_iterator {
        public:
          typedef typename A::difference_type difference_type;
          typedef typename A::value_type value_type;
          typedef typename A::reference reference;
          typedef typename A::pointer pointer;
          typedef std::random_access_iterator_tag iterator_category;

          reverse_iterator() : ptr {nullptr} {}
          explicit reverse_iterator(pointer p) : ptr{p} {}
          reverse_iterator(const reverse_iterator& other) : ptr{other.ptr} {}
          explicit reverse_iterator(const iterator& other) : ptr{other.ptr} {}
          ~reverse_iterator() { ptr = nullptr; }

          reverse_iterator& operator=(const reverse_iterator& other) { ptr = other.ptr; return *this; }
          bool operator==(const reverse_iterator& other) const { return ptr == other.ptr; }
          bool operator!=(const reverse_iterator& other) const { return ptr != other.ptr; }
          bool operator<(const reverse_iterator& other) const { return ptr > other.ptr; }
          bool operator>(const reverse_iterator& other) const { return ptr < other.ptr; }
          bool operator<=(const reverse_iterator& other) const { return ptr >= other.ptr; }
          bool operator>=(const reverse_iterator& other) const { return ptr <= other.ptr; }

          reverse_iterator& operator++() { --ptr; return *this; }
          reverse_iterator operator++(int) { reverse_iterator tmp{*this}; --ptr; return tmp; }
          reverse_iterator& operator--() { ++ptr; return *this; }
          reverse_iterator operator--(int) { reverse_iterator tmp{*this}; ++ptr; return tmp; }
          reverse_iterator& operator+=(size_type n) { ptr -= n; return *this; }
          reverse_iterator operator+(size_type n) { reverse_iterator tmp{*this}; tmp += n; return tmp; }

          reverse_iterator& operator-=(size_type n) { ptr += n; return *this; }
          reverse_iterator operator-(size_type n) const { reverse_iterator tmp{*this}; tmp -= n; return tmp; }
          difference_type operator-(reverse_iterator other) { return other.ptr - ptr; }
          reference operator*() const { return *ptr; }
          pointer operator->() const { return ptr; }
          reference operator[](size_type n) const { return *(ptr + n); }
        private:
          pointer ptr;
      };

      class const_reverse_iterator {
        public:
          typedef typename A::difference_type difference_type;
          typedef typename A::value_type value_type;
          typedef typename A::const_reference reference;
          typedef typename A::const_pointer pointer;
          typedef std::random_access_iterator_tag iterator_category;

          const_reverse_iterator() : ptr {nullptr} {}
          explicit const_reverse_iterator(pointer p) : ptr{p} {}
          const_reverse_iterator(const const_reverse_iterator& other) : ptr{other.ptr} {}
          explicit const_reverse_iterator(const iterator& other) : ptr{other.ptr} {}
          ~const_reverse_iterator() { ptr = nullptr; }

          const_reverse_iterator& operator=(const const_reverse_iterator& other) { ptr = other.ptr; return *this; }
          bool operator==(const const_reverse_iterator& other) const { return ptr == other.ptr; }
          bool operator!=(const const_reverse_iterator& other) const { return ptr != other.ptr; }
          bool operator<(const const_reverse_iterator& other) const { return ptr > other.ptr; }
          bool operator>(const const_reverse_iterator& other) const { return ptr < other.ptr; }
          bool operator<=(const const_reverse_iterator& other) const { return ptr >= other.ptr; }
          bool operator>=(const const_reverse_iterator& other) const { return ptr <= other.ptr; }

          const_reverse_iterator& operator++() { --ptr; return *this; }
          const_reverse_iterator operator++(int) { const_reverse_iterator tmp{*this}; --ptr; return tmp; }
          const_reverse_iterator& operator--() { ++ptr; return *this; }
          const_reverse_iterator operator--(int) { const_reverse_iterator tmp{*this}; ++ptr; return tmp; }
          const_reverse_iterator& operator+=(size_type n) { ptr -= n; return *this; }
          const_reverse_iterator operator+(size_type n) { const_reverse_iterator tmp{*this}; tmp += n; return tmp; }

          const_reverse_iterator& operator-=(size_type n) { ptr += n; return *this; }
          const_reverse_iterator operator-(size_type n) const { const_reverse_iterator tmp{*this}; tmp -= n; return tmp; }
          difference_type operator-(const_reverse_iterator other) { return other.ptr - ptr; }
          reference operator*() const { return *ptr; }
          pointer operator->() const { return ptr; }
          reference operator[](size_type n) const {return *(ptr + n); }
        private:
          pointer ptr;
      };

      typedef typename iterator::pointer pointer;
      typedef typename const_iterator::pointer const_pointer;

       vector() : vb() {}
       explicit vector(const A& a) noexcept : vb{a} {}
       explicit vector(size_type count, const T& value = T(),
                       const A& a = A()) : vb{a, count}{
         std::uninitialized_fill(vb.elem, vb.elem + count, value);
       }

       explicit vector(size_type count, const A& a) : vb{a, count} {
         std::uninitialized_fill(vb.elem, vb.elem + count, value_type());
       }

       template<class InputIt>
         vector(InputIt first, InputIt last, const A& alloc = A()) : vb {alloc, (size_type)(last - first)} {
           std::uninitialized_copy(first, last, vb.elem);
         }

       vector(const vector& other) : vb{other.vb.alloc, other.size()} {
         std::uninitialized_copy(other.begin(), other.end(), vb.elem);
       }

       vector(const vector& other, const allocator_type& alloc) : vb{alloc, other.size()} {
         std::uninitialized_copy(other.begin(), other.end(), vb.elem);
       }

       vector(vector&& other) noexcept : vb{std::move(other.vb)} {}

       vector(vector&& other, const A& alloc) : vb{std::move(other.vb), alloc} {}

       explicit vector(std::initializer_list<T> init, const A& alloc = A()) : vb {alloc, init.size()} {
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

        const size_type sz = size();
        const size_type osz = other.size();
        vb.alloc = other.vb.alloc;
        if (osz <= sz) {
          std::copy<iterator, pointer>(other.begin(), other.begin() + osz, vb.elem);
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
        shrink_to_fit();
        std::swap(vb, other.vb);
        return *this;
      }

      vector& operator=(std::initializer_list<T> ilist) {
        vector tmp{ilist};
        *this = tmp;
        return *this;
      }

      void assign(size_type count, const T& value) {
        vector tmp {count, value};
        *this = tmp;
      }

      template<typename InputIt>
      void assign(InputIt first, InputIt last) {
        vector tmp {first, last};
        *this = tmp;
      }

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

      reference front() { return iterator(vb.elem)[0]; }
      const_reference front() const { return const_iterator(vb.elem)[0]; }

      reference back() { return iterator(vb.space - 1)[size()]; }
      const_reference back() const { return const_iterator(vb.space - 1)[size()]; }

      pointer data() noexcept { return vb.elem; }
      const_pointer data() const noexcept { return vb.elem; }

      iterator begin() noexcept { return iterator(vb.elem); }
      const_iterator begin() const noexcept { return const_iterator(vb.elem); }
      const_iterator cbegin() const noexcept { return const_iterator(vb.elem); }

      iterator end() noexcept { return iterator(vb.space); }
      const_iterator end() const noexcept { return const_iterator(vb.space); }
      const_iterator cend() const noexcept { return const_iterator(vb.space); }

      reverse_iterator rbegin() noexcept { return reverse_iterator(vb.space - 1); }
      const_reverse_iterator rbegin() const { return const_reverse_iterator(vb.space - 1); }
      const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(vb.space - 1); }

      reverse_iterator rend() noexcept { return reverse_iterator(vb.elem - 1); }
      const_reverse_iterator rend() const { return const_reverse_iterator(vb.elem - 1); }
      const_reverse_iterator crend() const noexcept { return const_reverse_iterator(vb.elem - 1); }

      bool empty() const noexcept {return !size();};

      size_type size() const noexcept { return vb.space - vb.elem; }
      size_type max_size() const { return vb.alloc.max_size();}

      void reserve(size_type newalloc) {
        if (newalloc <= capacity()) return;

        vector_base<T, A> b {vb.alloc, newalloc};
        std::uninitialized_copy(vb.elem, vb.elem + size(), b.elem);
        b.space = b.elem + size();
        std::swap(vb, b);
      }

      size_type capacity() const noexcept { return vb.last - vb.elem; }

      void shrink_to_fit() {
        if (!(vb.last > vb.space)) return;

        vector_base<T, A> tmp (vb.alloc, size());
        std::uninitialized_copy(vb.elem, vb.space, tmp.elem);
        std::swap(vb, tmp);
      }

      void clear() noexcept { resize(0); }

      iterator insert(iterator pos, const_reference value) { return insert(pos, 1, value); }

      iterator insert(iterator pos, size_type count, const_reference value) {
        if (count == 0) return pos;
        if (pos >= end()) throw std::out_of_range("position is out of range");
        if (size() + count > max_size()) throw std::length_error("size is too large");

        const difference_type index = pos - begin();

        if (size() + count > capacity()) {
          size_type new_cap = std::max(2 * capacity(), size() + count);
          vector_base<T, A> new_vb (vb.alloc, new_cap);
          new_vb.space = std::uninitialized_copy(begin(), /*begin() +*/ pos, new_vb.elem);
          std::uninitialized_fill_n(new_vb.space, count, value);
          std::uninitialized_copy(/*begin() + */pos, end(), new_vb.space + count);
          new_vb.space += count + (end() - pos);
          new_vb.last = new_vb.elem + new_cap;
          std::swap(vb, new_vb);
        } else {
          std::move_backward(begin() + index, end(), end() + count);
          std::uninitialized_fill_n(/*begin() + */pos, count, value);
          vb.space += count;
        }
        return begin() + index;
     }

      iterator insert(iterator pos, iterator first, iterator last) {
        if (first >= last) return pos;
        if (pos >= end()) throw std::out_of_range("position is out of range");
        if (size() + (last - first) > max_size()) throw std::length_error("size is too large");

        const difference_type sz = last - first;
        const difference_type index = pos - begin();

        if (size() + sz > capacity()) {
          size_type new_cap = std::max(2 * capacity(), size() + sz);
          vector_base<T, A> new_vb (vb.alloc, new_cap);
          std::uninitialized_copy(vb.elem, vb.elem + index, new_vb.elem);
          std::uninitialized_copy(first, last, new_vb.elem + index);
          std::uninitialized_copy(vb.elem + index, vb.space, new_vb.elem + index + sz);
          new_vb.space = new_vb.elem + size() + sz;
          for (pointer p = vb.elem; p != vb.space; ++p)
            vb.alloc.destroy(p);
          vb.alloc.deallocate(vb.elem, vb.last - vb.elem);
          vb = std::move(new_vb);
        } else {
          std::move_backward(begin() + index, end(), end() + sz);
          std::uninitialized_copy(first, last, /*begin() + */pos);
          vb.space += sz;
        }
        return begin() + index;
      }

      iterator insert(iterator pos, std::initializer_list<T> ilist) {
        vector tmp (ilist);
        return insert(pos, tmp.begin(), tmp.end());
      }

      template<class... Args>
        iterator emplace(iterator pos, Args&&... args) {
          if (pos > end()) throw std::out_of_range("emplace");

          const difference_type index = pos - begin();
          if (capacity() == size())
            reserve(2 * capacity());
          std::move_backward(pos, end(), end() + 1);
          vb.alloc.construct(vb.elem + index, std::forward<Args>(args)...);
          vb.space++;
          return begin() + index;
        }

        // removes the element at pos
      iterator erase(iterator pos) {
        if (pos >= end()) throw std::out_of_range("pos is out of range in erase");
        const difference_type index = pos - begin();
        vb.alloc.destroy(vb.elem + index);
        for (auto it = pos; it < end() - 1; ++it)
          vb.alloc.construct(it.operator->(), *(it + 1));
        vb.alloc.destroy(vb.space - 1);
        vb.space--;
        return begin() + index;
      }

      // 1 2 3 4 5 6 7 8
      // 1 . . . 5 6 7 8
      //   ^
      // 1 5 6 7 8 . . .
      // removes the elements in the range [first, last)
      iterator erase (iterator first, iterator last) {
        if (first >= last) throw std::length_error("incorrect range [first; last)");
        if (first >= end() || last > end() || first < begin()) throw std::out_of_range("out_of_range in erase()");

        const difference_type index = first - begin();
        const size_type sz = last - first;

        for (iterator it = first; it < last; ++it)
          vb.alloc.destroy(it.operator->());
        for (iterator it = first; it < last && it + sz < end(); ++it)
          vb.alloc.construct(it.operator->(), *(it + sz));
        for (iterator it = last; it + sz < end(); ++it)
          *(it - sz) = std::move(*it);
        for (pointer p = vb.space - sz; p < vb.space; ++p)
          vb.alloc.destroy(p);

        vb.space -= sz;

        return begin() + index;
      }

      void push_back(const T& value) {
        if (capacity() == size())
          reserve(size() ? size() * 2 : 1);
        vb.alloc.construct(&vb.elem[size()], value);
        ++vb.space;
      }

      void push_back(T&& value) {
        if (capacity() == size())
          reserve(size() ? size() * 2 : 1);
        vb.alloc.construct(&vb.elem[size()], value);
        ++vb.space;
      }

      void pop_back() {
        if (size() && vb.space) {
          vb.alloc.destroy(vb.space - 1);
          --vb.space;
        }
      }

      void resize(size_type newsize) { resize(newsize, T()); }

      void resize(size_type newsize, const_reference value) {
        if (newsize < max_size()) {
          reserve(newsize > capacity() && capacity() ? capacity() * 2 : newsize);
          if (size() < newsize) {
            std::uninitialized_fill(vb.elem + size(), vb.elem + newsize, value);
          } else {
            for (pointer p = vb.elem + newsize; p != vb.elem + size(); ++p)
              vb.alloc.destroy(p);
          }
          vb.space = vb.elem + newsize;
        }
      }

      void swap(vector& other) noexcept {std::swap(vb, other.vb);}
  };

} // namespace s21

#endif  // _vector_
