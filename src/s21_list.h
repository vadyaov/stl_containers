#ifndef _list_
#define _list_

#include <memory>

namespace s21 {

  template<typename T, typename A = std::allocator<T>>
    class list_node {
      public:
        list_node* prev;
        list_node* next;
        T key;

        list_node() : prev{nullptr}, next{nullptr}, key{T()} {}
        list_node(const list_node* pr, const list_node* nx, const T& val) :
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
        typedef typename A::template rebind<list_node> NodeAllocator;


        list() : head{nullptr}, tail{nullptr}, allocator{A()} {}
        explicit list( const A& alloc ) : head{nullptr}, tail{nullptr}, allocator{alloc} {}
        explicit list( size_type count, const T& value, const A& alloc = A() ) {
        }

        explicit list( size_type count, const A& alloc = A() ) {
        }

        template< class InputIt >
          list( InputIt first, InputIt last, const A& alloc ) {
          }

        list(const list& other) {
        }

        /* list(const list& other, const A& alloc) { */
        /* } */

        list& operator=(const list& other) {
        }

        list(list&& other) noexcept {
        }

        list(list&& other, const A& alloc) noexcept {
        }

        list& operator=(list&& other) {
        }

        list( std::initializer_list<T> init, const A& alloc = A() ) {
        }

        ~list() {
        }

        list& operator=( std::initializer_list<T> ilist ) {
        }

        void assign( size_type count, const T& value) {}

        template< class InputIt >
          void assign( InputIt first, InputIt last ) {}

        void assign( std::initializer_list<T> ilist ) {}

        allocator_type get_allocator() const noexcept {}

        /* Element access */

        reference front() {}
        const_reference front() {}

        reference back() {}
        const_reference back() {}

        /* Iterators */

        iterator begin() noexcept {}
        const_iterator begin() const noexcept {}
        const_iterator cbegin() const noexcept {}

        iterator end() noexcept {}
        const_iterator end() const noexcept {}
        const_iterator cend() const noexcept {}

        reverse_iterator rbegin() noexcept {}
        const_reverse_iterator rbegin() const noexcept {}
        const_reverse_iterator crbegin() const noexcept {}

        reverse_iterator rend() noexcept {}
        const_reverse_iterator rend() const noexcept {}
        const_reverse_iterator crend() const noexcept {}

        /* Capacity */

        bool empty() const noexcept {}

        size_type size() const noexcept {}

        size_type max_size() const noexcept {}

        /* Modifiers */

        void clear() noexcept {}

        iterator insert ( const_iterator pos, const T& value ) {}
        iterator insert ( const_iterator pos, T&& value ) {}
        iterator insert ( const_iterator pos, size_type count, const T& value ) {}
        template< class InputIt >
          iterator insert ( const_iterator pos, InputIt first, InputIt last ) {}
        iterator insert ( const_iterator pos, std::initializer_list<T> ilist ) {}

        template< class... Args >
          iterator emplace ( const_iterator pos, Args&&... args ) {}

        iterator erase ( const_iterator pos ) {}
        iterator erase ( const_iterator first. const_iterator last ) {}

        void push_back( const T& value );
        void push_back( T&& value );

        template< class... Args >
          reference emplace_back( Args&&... args ) {}

        void pop_back() {}

        void push_front( const T& value ) {}
        void push_front( T&& value ) {}

        template< class... Args >
          reference emplace_front( Args&&... args ) {}

        void pop_front() {}

        void resize( size_type count ) {}
        void resize( size_type count, const T& value ) {}

        void swap( list& other ) noexcept {}

        /* Operations */

        void merge( list&& other ) {}
        template< class Compare >
          void merge( list&& other, Compare comp ) {}

        void splice( const_iterator pos, list&& other ) {}
        void splice( const_iterator pos, list&& other, const_iterator it ) {}
        void splice( const_iterator pos, list&& other,
                     const_iterator first, const_iterator last ) {}

        void remove( const T& value ) {}

        void reverse() noexcept {}

        void unique() {}

        void sort() {}

      private:
        list_node<T, A>* head;
        list_node<T, A>* tail;
        size_type sz;
        A allocator;
    };
} // namespace s21

#endif  // _list_
