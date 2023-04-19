#ifndef _stack_
#define _stack_

#include <iostream>
#include "vector.h"

namespace s21 {

  // LIFO - Last In First Out
  template<class T, class Container = vector<T>>
    class stack {
      public:
        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

        stack() : c{} {}

        explicit stack( const Container& cont ) : c{cont} {}

        explicit stack( std::initializer_list<value_type> init ) : c{init} {}

        stack( const stack& other ) : c{other.c} {}

        stack& operator=( const stack& other ) {
          c = other.c;
          return *this;
        }

        stack( stack&& other ) noexcept : c{std::move(other.c)} {
        }

        stack& operator=( stack&& other ) {
          c = std::move(other.c);
          return *this;
        }

        ~stack() = default;

        reference top() {
        }

        const_reference top() const {
        }

        bool empty() const {
        }

        size_type size() const {
        }

        void push( const value_type& value ) {
        }

        void push( value_type&& value ) {
        }

        template< class... Args >
          void emplace( Args&&... args ) {
          }

        void pop() {
        }

        void swap( stack& other ) noexcept {
        }
	
        void print() {
          for (auto i : c)
            std::cout << " " << i;
          std::cout << std::endl;
        }


      private:
        Container c;
    };
}

#endif // _stack_
