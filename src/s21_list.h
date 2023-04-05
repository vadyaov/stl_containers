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

        typedef list_node<T, A> node;
        typedef list_node<T, A>* node_pointer;


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

        /* list& operator=(const list& other) { */
        /* } */

        /* list(list&& other) noexcept { */
        /* } */

        /* list(list&& other, const A& alloc) noexcept { */
        /* } */

        /* list& operator=(list&& other) { */
        /* } */

        /* list( std::initializer_list<T> init, const A& alloc = A() ) { */
        /* } */

        ~list() {
          // think about how to do it better
          if (tail)
            for (node_pointer tmp = tail, pre = tmp->prev; tmp != head; tmp = pre, pre = tmp->prev)
              allo.deallocate(tmp, 1);
          if (head) allo.deallocate(head, 1);
        }

        /* list& operator=( std::initializer_list<T> ilist ) { */
        /* } */

        /* void assign( size_type count, const T& value) {} */

        /* template< class InputIt > */
        /*   void assign( InputIt first, InputIt last ) {} */

        /* void assign( std::initializer_list<T> ilist ) {} */

        /* allocator_type get_allocator() const noexcept {} */

        /* /1* Element access *1/ */

        /* reference front() {} */
        /* const_reference front() {} */

        /* reference back() {} */
        /* const_reference back() {} */

        /* /1* Iterators *1/ */

        /* iterator begin() noexcept {} */
        /* const_iterator begin() const noexcept {} */
        /* const_iterator cbegin() const noexcept {} */

        /* iterator end() noexcept {} */
        /* const_iterator end() const noexcept {} */
        /* const_iterator cend() const noexcept {} */

        /* reverse_iterator rbegin() noexcept {} */
        /* const_reverse_iterator rbegin() const noexcept {} */
        /* const_reverse_iterator crbegin() const noexcept {} */

        /* reverse_iterator rend() noexcept {} */
        /* const_reverse_iterator rend() const noexcept {} */
        /* const_reverse_iterator crend() const noexcept {} */

        /* /1* Capacity *1/ */

        /* bool empty() const noexcept {} */

        size_type size() const noexcept { return sz; }

        /* size_type max_size() const noexcept {} */

        /* /1* Modifiers *1/ */

        /* void clear() noexcept {} */

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

        /* void push_back( const T& value ); */
        /* void push_back( T&& value ); */

        /* template< class... Args > */
        /*   reference emplace_back( Args&&... args ) {} */

        /* void pop_back() {} */

        /* void push_front( const T& value ) {} */
        /* void push_front( T&& value ) {} */

        /* template< class... Args > */
        /*   reference emplace_front( Args&&... args ) {} */

        /* void pop_front() {} */

        /* void resize( size_type count ) {} */
        /* void resize( size_type count, const T& value ) {} */

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

        void printList() {
          std::cout << "HEAD:";
          /* std::cout << head << std::endl; */
          list_node<T, A>* tmp = head;
          while (tmp != tail) {
            std::cout << tmp->key << std::endl;
            tmp = tmp->next;
          }
          std::cout << "TAIL:";
          std::cout << tmp->key << std::endl;
        }

      private:
        list_node<T, A>* head;
        list_node<T, A>* tail;
        size_type sz;
        A allocator;
        NodeAllocator allo;
    };
} // namespace s21

#endif  // _list_
