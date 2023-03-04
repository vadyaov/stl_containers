#include "s21_vector.h"

using namespace s21;

/* ------------------------------vector_base----------------------------------*/
template<typename T, typename A>
vector_base<T, A>::vector_base() : elem{nullptr}, space{nullptr}, last{nullptr}, alloc{A()} {}

template<typename T, typename A>
vector_base<T, A>::vector_base(const A& a) noexcept : elem{nullptr}, space{nullptr}, last{nullptr}, alloc{a} {}

template<typename T, typename A>
vector_base<T, A>::vector_base(const A& a, typename A::size_type n)
  :alloc{a}, elem{alloc.allocate(n)}, space{elem + n}, last{elem + n} {}

template <typename T, typename A>
vector_base<T, A>::vector_base(vector_base&& other) noexcept : elem{other.elem}, space{other.space}, last{other.last}, alloc{other.alloc} {
  other.elem = other.last = other.space = nullptr;
}

template<typename T, typename A>
vector_base<T, A>& vector_base<T, A>::operator=(vector_base&& other) noexcept {
  std::swap(*this, other);
  return *this;
}

template<typename T, typename A>
vector_base<T, A>::~vector_base() {alloc.deallocate(elem, last - elem);}

/* -------------------------------------------------------------------------- */


template <typename T, typename A>
vector<T, A>::vector() : vb{} {}

template <typename T, typename A>
vector<T, A>::vector(const A& a) noexcept : vb{a} {}

template <typename T, typename A>
vector<T,A>::vector(size_type count, const T& value, const A& a) : vb{a, count} {
  std::uninitialized_fill(vb.elem, vb.elem + count, value);
}

template <typename T, typename A>
vector<T, A>::vector(size_type count, const A& a) : vb{a, count} {
  std::uninitialized_fill(vb.elem, vb.elem + count, T());
}

template<typename T, typename A>
vector<T, A>::vector(const vector<T, A>& other) : vb{other.alloc, other.size()} {
  std::uninitialized_copy(other.begin(), other.end(), vb.elem);
}

// 1.если емкость вектора, в который производим присванивание, больше размера other,
// то выделять память (создавать  tmp нет необходимости)
// 2.присваниванеие элементов может быть более эффективным, чем уничтожение элементов с последующим конструированием
template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(const vector<T, A>& other) {
  vector<T, A> tmp{other};
  std::swap(*this, tmp);
  return *this;
}

template<typename T, typename A>
vector<T, A>::vector(const vector& other, const A& alloc) : vb{alloc, other.size()} {
  std::uninitialized_copy(other.begin(), other.end(), vb.elem);
}

template<typename T, typename A>
vector<T, A>::vector(vector<T, A>&& other) noexcept : vb{std::move(other.vb)} {}

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(vector&& other) noexcept {
  clear(); // need to implement
  /* vb = std::move(other.vb); */
  std::swap(*this, other); // this mb instead of previous line
  return *this;
}

template<typename T, typename A>
void vector<T, A>::destroy_elements() {
  for (T* p = vb.elem; p != vb.space; ++p)
    p->~T();
}

template<typename T, typename A>
vector<T, A>::~vector() {destroy_elements();}
