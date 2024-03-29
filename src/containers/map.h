#ifndef _STL_CONTAINERS_CONTAINERS_MAP_H_
#define _STL_CONTAINERS_CONTAINERS_MAP_H_

#include "rb_tree.h"

namespace s21 {

template <class Key, class T, class Compare = std::less<Key>>
class map {
 public:
  typedef RBTree<Key, T, Compare> rb_tree;
  typedef typename RBTree<Key, T, Compare>::key_type key_type;
  typedef typename RBTree<Key, T, Compare>::mapped_type mapped_type;
  typedef typename RBTree<Key, T, Compare>::value_type value_type;
  typedef typename RBTree<Key, T, Compare>::size_type size_type;
  typedef typename RBTree<Key, T, Compare>::key_compare key_compare;
  typedef typename RBTree<Key, T, Compare>::allocator_type allocator_type;
  typedef typename RBTree<Key, T, Compare>::reference reference;
  typedef typename RBTree<Key, T, Compare>::const_reference const_reference;
  typedef typename RBTree<Key, T, Compare>::iterator iterator;
  typedef typename RBTree<Key, T, Compare>::const_iterator const_iterator;

  map() : tree{} {}

  map(const map& other) : tree{other.tree} {}

  map& operator=(const map& other) {
    tree = other.tree;
    return *this;
  }

  map(map&& other) noexcept : tree{std::move(other.tree)} {}

  map& operator=(map&& other) noexcept {
    tree = std::move(other.tree);
    return *this;
  }

  map(std::initializer_list<value_type> init) : tree{init} {}

  map& operator=(std::initializer_list<value_type> init) {
    tree = init;
    return *this;
  }

  ~map() = default;

  T& at(const Key& key) { return tree.at(key); }

  const T& at(const Key& key) const { return tree.at(key); }

  T& operator[](const Key& key) { return tree[key]; }

  iterator begin() noexcept { return tree.begin(); }

  const_iterator begin() const noexcept { return tree.begin(); }

  const_iterator cbegin() const noexcept { return tree.cbegin(); }

  iterator end() noexcept { return tree.end(); }

  const_iterator end() const noexcept { return tree.end(); }

  const_iterator cend() const noexcept { return tree.cend(); }

  bool empty() const noexcept { return tree.empty(); }

  size_type size() const noexcept { return tree.size(); }

  void clear() noexcept { tree.clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    return tree.insert(value);
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    return tree.unique_emplace_m(args...);
  }

  size_type erase(const Key& key) { return tree.erase(key); }

  void swap(map& other) noexcept { return tree.swap(other.tree); }

  iterator find(const Key& key) { return tree.find(key); }

  const_iterator find(const Key& key) const { return tree.find(key); }

 private:
  rb_tree tree;
};

}  // namespace s21

#endif  // _STL_CONTAINERS_CONTAINERS_MAP_H_
