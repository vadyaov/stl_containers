#ifndef _list_
#define _list_

#include <iostream>
#include <memory>

namespace s21 {

  template<typename T, typename A = std::allocator<T>>
    class list_node {
      public:
        list_node* prev;
        list_node* next;
        T key;

        list_node() : prev{nullptr}, next{nullptr}, key{T()} {}
        explicit list_node(const T& val) : prev{nullptr}, next{nullptr}, key{val} {}

        list_node(const list_node* pr, const list_node* nx, const T& val) :
                 prev{pr}, next{nx}, key{val} {std::cout << "i'm here!\b";}
        list_node(const list_node* pr, const list_node* nx, T&& val) :
                 prev{pr}, next{nx}, key{val} {}
    };

  template<typename T, typename A = std::allocator<T>>
    class list {
      public:
        typedef A allocator_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::const_reference const_reference;
        typedef typename A::difference_type difference_type;
        typedef typename A::size_type size_type;
        typedef typename A::template rebind<list_node<T, A>>::other NodeAllocator;

        /* typedef list_node<T, A> node; */
        typedef list_node<T, A>* node_pointer;

        class iterator {
         public:
          typedef typename A::difference_type difference_type;
          typedef typename A::value_type value_type;
          typedef typename A::reference reference;
          typedef typename A::pointer pointer;
          typedef std::bidirectional_iterator_tag iterator_category;

          iterator() : ptr{nullptr} {}
          explicit iterator(node_pointer p) : ptr{p} {}
          iterator(const iterator& iter) : ptr{iter.ptr} {}
          ~iterator() { ptr = nullptr; }

          iterator& operator=(const iterator& other) {
            ptr = other.ptr;
            return *this;
          }

          bool operator==(const iterator& other) const { return ptr == other.ptr; }
          bool operator!=(const iterator& other) const { return ptr != other.ptr; }

          iterator& operator++() {
            ptr = ptr->next;
            return *this;
          }

          iterator operator++(int) {
            iterator tmp = *this;
            ptr = ptr->next;
            return tmp;
          }

          iterator& operator--() {
            ptr = ptr->prev;
            return *this;
          }

          iterator operator--(int) {
            iterator tmp = *this;
            ptr = ptr->prev;
            return tmp;
          }

          reference operator*() const { return ptr->key; }

         private:
          node_pointer ptr;
        };

        class const_iterator {
         public:
          typedef typename A::difference_type difference_type;
          typedef typename A::value_type value_type;
          typedef typename A::const_reference reference;
          typedef typename A::const_pointer pointer;
          typedef std::bidirectional_iterator_tag iterator_category;


          const_iterator() : ptr{nullptr} {}
          explicit const_iterator(node_pointer p) : ptr{p} {}
          const_iterator(const const_iterator& iter) : ptr{iter.ptr} {}
          ~const_iterator() { ptr = nullptr; }

          const_iterator& operator=(const const_iterator& other) {
            ptr = other.ptr;
            return *this;
          }

          bool operator==(const const_iterator& other) const { return ptr == other.ptr; }
          bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }

          const_iterator& operator++() {
            ptr = ptr->next;
            return *this;
          }

          const_iterator operator++(int) {
            const_iterator tmp = *this;
            ptr = ptr->next;
            return tmp;
          }

          const_iterator& operator--() {
            ptr = ptr->prev;
            return *this;
          }

          const_iterator operator--(int) {
            const_iterator tmp = *this;
            ptr = ptr->prev;
            return tmp;
          }

          reference operator*() const { return ptr->key; }

         private:
          node_pointer ptr;
        };

        class reverse_iterator {
         public:
          typedef typename A::difference_type difference_type;
          typedef typename A::value_type value_type;
          typedef typename A::reference reference;
          typedef typename A::pointer pointer;
          typedef std::bidirectional_iterator_tag iterator_category;

          reverse_iterator() : ptr{nullptr} {}
          explicit reverse_iterator(node_pointer p) : ptr{p} {}
          reverse_iterator(const reverse_iterator& iter) : ptr{iter.ptr} {}
          ~reverse_iterator() { ptr = nullptr; }

          reverse_iterator& operator=(const reverse_iterator& other) {
            ptr = other.ptr;
            return *this;
          }

          bool operator==(const reverse_iterator& other) const { return ptr == other.ptr; }
          bool operator!=(const reverse_iterator& other) const { return ptr != other.ptr; }

          reverse_iterator& operator++() {
            ptr = ptr->prev;
            return *this;
          }

          reverse_iterator operator++(int) {
            reverse_iterator tmp = *this;
            ptr = ptr->prev;
            return tmp;
          }

          reverse_iterator& operator--() {
            ptr = ptr->next;
            return *this;
          }

          reverse_iterator operator--(int) {
            reverse_iterator tmp = *this;
            ptr = ptr->next;
            return tmp;
          }

          reference operator*() const { return ptr->key; }

         private:
          node_pointer ptr;
        };

        class const_reverse_iterator {
         public:
          typedef typename A::difference_type difference_type;
          typedef typename A::value_type value_type;
          typedef typename A::const_reference reference;
          typedef typename A::const_pointer pointer;
          typedef std::bidirectional_iterator_tag iterator_category;

          const_reverse_iterator() : ptr{nullptr} {}
          explicit const_reverse_iterator(node_pointer p) : ptr{p} {}
          const_reverse_iterator(const const_reverse_iterator& iter) : ptr{iter.ptr} {}
          ~const_reverse_iterator() { ptr = nullptr; }

          const_reverse_iterator& operator=(const const_reverse_iterator& other) {
            ptr = other.ptr;
            return *this;
          }

          bool operator==(const const_reverse_iterator& other) const { return ptr == other.ptr; }
          bool operator!=(const const_reverse_iterator& other) const { return ptr != other.ptr; }

          const_reverse_iterator& operator++() {
            ptr = ptr->prev;
            return *this;
          }

          const_reverse_iterator operator++(int) {
            const_reverse_iterator tmp = *this;
            ptr = ptr->prev;
            return tmp;
          }

          const_reverse_iterator& operator--() {
            ptr = ptr->next;
            return *this;
          }

          const_reverse_iterator operator--(int) {
            const_reverse_iterator tmp = *this;
            ptr = ptr->next;
            return tmp;
          }

          reference operator*() const { return ptr->key; }

         private:
          node_pointer ptr;
        };

        list() : list(A()) {}
        explicit list( const A& alloc ) : head{nullptr}, tail{nullptr}, allocator{alloc} {}
        explicit list( size_type count, const T& value, const A& alloc = A() ) :
                       head{nullptr}, tail{nullptr}, allocator{alloc} {
          if (count != 0) {
            // mb it should be in private for destructor... or not...
            head = tail = allo.allocate(1);
            allo.construct(head, value);

            for (size_type i = 1; i < count; ++i) {
              node_pointer newNode = allo.allocate(1);
              allo.construct(newNode, value);
              newNode->prev = tail;
              newNode->next = nullptr;
              tail->next = newNode;
              tail = newNode;
            }

          }
          sz = count;
        }

        explicit list( size_type count, const A& alloc = A() ) : list(count, T(), alloc) {}

        template< class InputIt >
          list( InputIt first, InputIt last, const A& alloc ) : list(alloc) {
            if (!(last > first)) throw std::length_error("last <= first");
            head = tail = allo.allocate(1);
            allo.construct(head, *first);

            for (InputIt i = first + 1; i < last; ++i) {
              node_pointer newNode = allo.allocate(1);
              allo.construct(newNode, *i);
              newNode->prev = tail;
              newNode->next = nullptr;
              tail->next = newNode;
              tail = newNode;
            }
            sz = last - first;
          }

        list(const list& other) : list(other, other.allocator) {}

        list(const list& other, const A& alloc) : sz {other.sz}, allocator{alloc} {
          if (sz != 0) {
            head = tail = allo.allocate(1);
            allo.construct(head, other.head->key);

            for(node_pointer i = other.head->next; i != nullptr; i = i->next) {
              node_pointer newNode = allo.allocate(1);
              allo.construct(newNode, i->key);
              newNode->prev = tail;
              newNode->next = nullptr;
              tail->next = newNode;
              tail = newNode;
            }
          }
        }

        list& operator=(const list& other) {
          if (this == &other) return *this;
          list tmp{other};
          std::swap(*this, tmp);
          return *this;
        }

        list(list&& other) noexcept : list(other, other.allocator) {}

        list(list&& other, const A& alloc) noexcept : head{other.head},
                    tail{other.tail}, sz{other.sz}, allocator{alloc}{
          other.head = other.tail = nullptr;
        }

        list& operator=(list&& other) {
          std::swap(*this, other);
          return *this;
        }

        explicit list( std::initializer_list<T> init, const A& alloc = A() ) :
                                        list(init.begin(), init.end(), alloc) {}

        ~list() {
          // think about how to do it better
          if (tail)
            for (node_pointer tmp = tail, pre = tmp->prev; tmp != head; tmp = pre, pre = tmp->prev)
              allo.deallocate(tmp, 1);
          if (head) allo.deallocate(head, 1);
        }

        list& operator=( std::initializer_list<T> ilist ) {
          list tmp{ilist};
          std::swap(*this, tmp);
          return *this;
        }

        void assign( size_type count, const T& value) {
          list tmp{count, value};
          *this = tmp;
        }

        template< class InputIt >
          void assign( InputIt first, InputIt last ) {
            list tmp{first, last};
            *this = tmp;
          }

        void assign( std::initializer_list<T> ilist ) {
          list tmp{ilist};
          *this = tmp;
        }

        allocator_type get_allocator() const noexcept { return allocator; }

        /* Element access */

        reference front() { return head->key; }
        const_reference front() const { return head->key; }

        reference back() { return tail->key; }
        const_reference back() const { return tail->key; }

        /* Iterators */

        iterator begin() noexcept { return iterator{head}; }
        const_iterator begin() const noexcept { return const_iterator(head); }
        const_iterator cbegin() const noexcept { return const_iterator(head); }

        iterator end() noexcept { return iterator{nullptr}; }
        const_iterator end() const noexcept { return const_iterator(nullptr); }
        const_iterator cend() const noexcept { return const_iterator(nullptr); }

        reverse_iterator rbegin() noexcept { return reverse_iterator(tail); }
        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(tail); }
        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(tail); }

        reverse_iterator rend() noexcept { return reverse_iterator(nullptr); }
        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(nullptr); }
        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(nullptr); }

        /* Capacity */

        bool empty() const noexcept { return size() == 0; }
        size_type size() const noexcept { return sz; }
        size_type max_size() const noexcept { return allo.max_size(); }

        /* Modifiers */

        void clear() noexcept { resize(0); }

        /* iterator insert ( const_iterator pos, const T& value ) {} */
        /* iterator insert ( const_iterator pos, T&& value ) {} */
        /* iterator insert ( const_iterator pos, size_type count, const T& value ) {} */
        /* template< class InputIt > */
        /*   iterator insert ( const_iterator pos, InputIt first, InputIt last ) {} */
        /* iterator insert ( const_iterator pos, std::initializer_list<T> ilist ) {} */

        /* template< class... Args > */
        /*   iterator emplace ( const_iterator pos, Args&&... args ) {} */

        /* iterator erase ( const_iterator pos ) {} */
        /* iterator erase ( const_iterator first. const_iterator last ) {} */

        // implement this and then use push_back in other methods for better readability!
        void push_back( const T& value ) {
        }

        /* void push_back( T&& value ); */

        /* template< class... Args > */
        /*   reference emplace_back( Args&&... args ) {} */

        /* void pop_back() {} */

        /* void push_front( const T& value ) {} */
        /* void push_front( T&& value ) {} */

        /* template< class... Args > */
        /*   reference emplace_front( Args&&... args ) {} */

        /* void pop_front() {} */

        void resize( size_type count ) { resize(count, T()); }

        void resize( size_type count, const T& value ) {
          if (sz == count) return;
          if (count > sz) {
            while (sz != count) {
              node_pointer newNode = allo.allocate(1);
              tail->next = newNode;
              newNode->prev = tail;
              newNode->next = nullptr;
              newNode->key = value;
              tail = newNode;
              sz++;
            }
          } else {
            node_pointer tmp = tail, pre = tmp->prev;
            for (; sz != count; tmp = pre, pre = tmp ? tmp->prev : nullptr, --sz)
              allo.deallocate(tmp, 1);
            tail = tmp;
            if (sz == 0) head = tail;
          }
        }

        /* void swap( list& other ) noexcept {} */

        /* /1* Operations *1/ */

        /* void merge( list&& other ) {} */
        /* template< class Compare > */
        /*   void merge( list&& other, Compare comp ) {} */

        /* void splice( const_iterator pos, list&& other ) {} */
        /* void splice( const_iterator pos, list&& other, const_iterator it ) {} */
        /* void splice( const_iterator pos, list&& other, */
        /*              const_iterator first, const_iterator last ) {} */

        /* void remove( const T& value ) {} */

        /* void reverse() noexcept {} */

        /* void unique() {} */

        /* void sort() {} */

      private:
        list_node<T, A>* head;
        list_node<T, A>* tail;
        size_type sz;
        A allocator;
        NodeAllocator allo;
    };
} // namespace s21

#endif  // _list_
