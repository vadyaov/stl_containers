#ifndef _vector_
#define _vector_

#include <memory>

// read about allocator_traits interface and try to use in to allocate memory
// think about what i will implement, i think idw to implement all of these constructors;
// mb just do rule of 5, init_list and explicit one
namespace s21 {
  template<typename T, typename Allocator = std::allocator<T>>
  class vector {
    public:
      using size_type = unsigned int;
      using value_type = T;
      using reference = value_type&;
      // Default constructor. Constructs an empty container with a default-constructed allocator.
      vector() = default;

      // Constructs an empty container with the given allocator alloc.
      explicit vector(const Allocator& alloc) noexcept;

      // Constructs the container with count copies of elements with value value.
      explicit vector(size_type count,
                      const T& value = T(),
                      const Allocator& alloc = Allocator());

      // Constructs the container with count default-inserted instances of T. No copies are made.
      explicit vector(size_type count, const Allocator& alloc = Allocator());

      // Constructs the container with the contents of the range [first, last). 
      template<class InputIt> vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );

      // Copy constructor. Constructs the container with the copy of the contents of other.
      vector(const vector& other);

      // Constructs the container with the copy of the contents of other, using alloc as the allocator.
      vector( const vector& other, const Allocator& alloc );
      vector& operator=(const vector& other);

      // Move constructor. Constructs the container with the contents of other using move semantics.
      // Allocator is obtained by move-construction from the allocator belonging to other.
      // After the move, other is guaranteed to be empty().
      vector(vector&& other) noexcept;

      // Allocator-extended move constructor. Using alloc as the allocator for the new container,
      // moving the contents from other; if alloc != other.get_allocator(), this results in an element-wise move.
      // (In that case, other is not guaranteed to be empty after the move.)
      vector( vector&& other, const Allocator& alloc );
      vector& operator=(vector&& other) noexcept;

      // Constructs the container with the contents of the initializer list init.
      vector(std::initializer_list<T> init, const Allocator& alloc = Allocator());

      ~vector();


      size_type size() const {return space - elem;}
    private:
      T* elem; // начало выделяемой памяти
      T* space; // начало области памяти для расширения, конец последовательности элементов
      T* last; // конец выделенной памяти
      Allocator alloc; // аллокаторб для запрашивания памяти под элементы
  };
} // namespace s21

#endif  // _vector_
