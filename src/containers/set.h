#ifndef _STL_CONTAINERS_CONTAINERS_SET_H_
#define _STL_CONTAINERS_CONTAINERS_SET_H_

#include "rb_tree.h"

namespace s21 {

template <class Key, class Compare = std::less<Key>>
class set {
 public:
  typedef char T;
  typedef RBTree<Key, T, Compare> rb_tree;
  typedef typename RBTree<Key, T, Compare>::key_type key_type;
  typedef typename RBTree<Key, T, Compare>::key_type value_type;
  typedef typename RBTree<Key, T, Compare>::size_type size_type;
  typedef typename RBTree<Key, T, Compare>::key_compare key_compare;
  typedef typename RBTree<Key, T, Compare>::allocator_type allocator_type;
  typedef typename RBTree<Key, T, Compare>::reference reference;
  typedef typename RBTree<Key, T, Compare>::const_reference const_reference;
  typedef typename RBTree<Key, T, Compare>::iterator iterator;
  typedef typename RBTree<Key, T, Compare>::const_iterator const_iterator;

  /* Member functions */

  set() : tree{} {}

  set(const set& other) : tree{other.tree} {}

  set& operator=(const set& other) {
    tree = other.tree;
    return *this;
  }

  set(set&& other) noexcept : tree{std::move(other.tree)} {}

  set& operator=(set&& other) noexcept {
    tree = std::move(other.tree);
    return *this;
  }

  set(std::initializer_list<value_type> init) : tree{} {
    for (auto i : init) tree.insert(std::make_pair(i, T()));
  }

  set& operator=(std::initializer_list<value_type> init) {
    set tmp{init};
    std::swap(*this, tmp);
    return *this;
  }

  ~set() = default;

  /* Iterators */

  iterator begin() noexcept { return tree.begin(); }

  const_iterator begin() const noexcept { return tree.begin(); }

  const_iterator cbegin() const noexcept { return tree.cbegin(); }

  iterator end() noexcept { return tree.end(); }

  const_iterator end() const noexcept { return tree.end(); }

  const_iterator cend() const noexcept { return tree.cend(); }

  /* Capacity */

  bool empty() const noexcept { return tree.empty(); }

  size_type size() const noexcept { return tree.size(); }

  void clear() noexcept { tree.clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    return tree.insert(std::make_pair(value, T()));
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    return tree.unique_emplace_s(std::forward<Args>(args)...);
  }

  size_type erase(const Key& key) { return tree.erase(key); }

  void swap(set& other) noexcept { return tree.swap(other.tree); }

  iterator find(const Key& key) { return tree.find(key); }

  const_iterator find(const Key& key) const { return tree.find(key); }

 private:
  rb_tree tree;
};

}  // namespace s21

#endif  // _STL_CONTAINERS_CONTAINERS_SET_H_
