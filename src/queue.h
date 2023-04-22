#ifndef _queue_
#define _queue_

#include "list.h"

namespace s21 {

  template<class T>
    class queue {
      public:
        typedef list<T> Container;
        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

        queue() : q{} {}

        explicit queue( const Container& cont ) : q{cont} {}

        explicit queue( std::initializer_list<value_type> init ) : q{init} {}

        queue( const queue& other ) : q{other.q} {}

        queue& operator=( const queue& other ) {
          q = other.q;
          return *this;
        }

        queue( queue&& other ) noexcept : q{std::move(other.q)} {}

        queue& operator=( queue&& other ) {
          q = std::move(other.q);
          return *this;
        }

        ~queue() = default;

        reference front() { return q.front(); }
		
        const_reference front() const { return q.front(); }

        reference back() { return q.back(); }
		
        const_reference back() const { return q.back(); }

        bool empty() const { return q.empty(); }
	
        size_type size() const { return q.size(); }

        void push( const value_type& value ) { q.push_back(value); }
		
        void push( value_type&& value ) { q.push_back(std::move(value)); }

        template< class... Args >
          void emplace( Args&&... args ) {
            q.emplace_back(std::forward<Args>(args)...);
          }

        void pop() { q.pop_front(); }

        void swap( queue& other ) noexcept { std::swap(q, other.q); }

        void print() {
          q.print();
        }

      private:
       Container q; 
    };

} // namespace s21


#endif // _queue_
