#ifndef _vector_
#define _vector_

#include <memory>

namespace s21 {

  template<typename T, typename A = std::allocator<T>>
    struct vector_base {
      T* elem;  // начало выделяемой памяти
      T* space; // начало области памяти для расширения, конец последовательности элементов
      T* last;  // конец выделенной памяти
      A alloc;  // аллокаторб для запрашивания памяти под элементы

      vector_base();

      explicit vector_base(const A&) noexcept;

      vector_base(const A&, typename A::size_type);

      ~vector_base();
      
      vector_base(const vector_base&) = delete; // no copy operations
      vector_base& operator=(const vector_base&) = delete;

      vector_base(vector_base&&) noexcept; // move operations
      vector_base& operator=(vector_base&&) noexcept;
    };

  template<typename T, typename A = std::allocator<T>>
  class vector {
    public:
      using size_type = unsigned int;
      using value_type = T;
      using reference = value_type&;
      using const_reference = const value_type&;
      /* using iterator = /1* зависит от реализации *1/; */
      /* using const_iterator = /1* зависит от реализации *1/; */
      /* using allocator_type = A; */
      /* using pointer = typename std::allocator_traits<A>::pointer; */
      /* using const_pointer = typename std::allocator_traits<A>::const_pointer; */
      /* using reverse_iterator = std::reverse_iterator<iterator>; */
      // Default constructor. Constructs an empty container with a default-constructed allocator.
      vector(); // +

      // Constructs an empty container with the given allocator alloc.
      explicit vector(const A&) noexcept; // +

      // Constructs the container with count copies of elements with value value.
      explicit vector(size_type count,
                      const T& value = T(),
                      const A& alloc = A()); // +

      // Constructs the container with count default-inserted instances of T. No copies are made.
      explicit vector(size_type count, const A& alloc = A()); // +

      // Constructs the container with the contents of the range [first, last). 
      template<class InputIt> vector( InputIt first, InputIt last, const A& alloc = A() );

      // Copy constructor. Constructs the container with the copy of the contents of other.
      vector(const vector& other); // + !!! need to implement 'begin' and 'end' !!!

      // Constructs the container with the copy of the contents of other, using alloc as the allocator.
      vector( const vector& other, const A& alloc ); // + !!! begin() + end() !!!

      vector& operator=(const vector& other); // +-

      // Move constructor. Constructs the container with the contents of other using move semantics.
      // A is obtained by move-construction from the allocator belonging to other.
      // After the move, other is guaranteed to be empty().
      vector(vector&& other) noexcept; // +

      // A-extended move constructor. Using alloc as the allocator for the new container,
      // moving the contents from other; if alloc != other.get_allocator(), this results in an element-wise move.
      // (In that case, other is not guaranteed to be empty after the move.)
      vector( vector&& other, const A& alloc );

      vector& operator=(vector&& other) noexcept; // +

      // Constructs the container with the contents of the initializer list init.
      vector(std::initializer_list<T> init, const A& alloc = A());

      ~vector(); // +

      size_type size() const {return vb.space - vb.elem;}
      size_type capacity() const {return vb.last - vb.elem;}

      void reserve(size_type); // увеличиваем емкость

      void resize(size_type, T = {}); // изменяем число элементов
      void clear(){resize(0);} // опустошаем вектор
      void push_back(const T&); // добавляем элемент в конец
      void pop_back(); // удаляем элемент с конца

    private:
      vector_base<T, A> vb;
      void destroy_elements();
  };

} // namespace s21

#endif  // _vector_
