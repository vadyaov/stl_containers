#ifndef _MULTISET_H_
#define _MULTISET_H_

#include "../containers/rb_tree.h"

namespace s21 {

  template<class Key, class Compare = std::less<Key>>
    class multiset {
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

      multiset() : tree{} {} 

      multiset(const multiset& other) : tree{other.tree} {}

      multiset& operator=(const multiset& other) {
        tree = other.tree;
        return *this;
      }

      multiset(multiset&& other) noexcept : tree{std::move(other.tree)} {}

      multiset& operator=(multiset&& other) noexcept {
        tree = std::move(other.tree);
        return *this;
      }

      multiset(std::initializer_list<value_type> init) : tree{} {
        for (auto i : init)
          tree.insert(std::make_pair(i, T()), false);
      }

      multiset& operator=(std::initializer_list<value_type> init)  {
        multiset tmp{init};
        std::swap(*this, tmp);
        return *this;
      }

      ~multiset() = default;


      /* Iterators */

      iterator begin() noexcept {
        return tree.begin();
      }

      const_iterator begin() const noexcept {
        return tree.begin();
      }

      const_iterator cbegin() const noexcept {
        return tree.cbegin();
      }

      iterator end() noexcept {
        return tree.end();
      }

      const_iterator end() const noexcept {
        return tree.end();
      }

      const_iterator cend() const noexcept {
        return tree.cend();
      }

      /* Capacity */

      bool empty() const noexcept {
        return tree.empty();
      }

      size_type size() const noexcept {
        return tree.size();
      }

      void clear() noexcept {
        tree.clear();
      }

      std::pair<iterator, iterator> equal_range(const Key& key) {
        return std::pair<iterator, iterator>(tree.lower_bound(key), tree.upper_bound(key));
      }

      size_type count(const Key& key) const {
        size_type n = 0;
        for (iterator it = tree.lower_bound(key); it != tree.upper_bound(key); ++it)
          if (*it == key) ++n;
        return n;
      }

      std::pair<iterator, bool> insert(const value_type& value) {
        return tree.insert(std::make_pair(value, T()), false);
      }

      template<class... Args>
        std::vector<std::pair<iterator, bool>> emplace(Args&&... args) {
          return tree.emplace(args...);
        }

      size_type erase(const Key& key) {
        size_type tmp = tree.erase(key);
        while (tree.erase(key))
          tmp += 1;
        return tmp;
      }

      void swap(multiset& other) noexcept {
        return tree.swap(other.tree);
      }

      iterator find(const Key& key) {
        return tree.find(key);
      }

      const_iterator find(const Key& key) const {
        return tree.find(key);
      }

    private:
      rb_tree tree;
    };

} // namespace s21

#endif // _MULTISET_H_

