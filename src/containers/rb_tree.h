#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include <iostream>
#include <string>
#include <memory>

/* Красно-чёрным называется бинарное поисковое дерево, у которого каждому узлу
 * сопоставлен дополнительный атрибут — цвет и для которого выполняются
 * следующие свойства:

    1) Каждый узел промаркирован красным или чёрным цветом
    2) Корень и конечные узлы (листья) дерева — чёрные
    3) У красного узла родительский узел — чёрный
    4) Все простые пути из любого узла x до листьев содержат одинаковое
       количество чёрных узлов
    5) Чёрный узел может иметь чёрного родителя
*/

enum class Color { RED, BLACK };

template <typename K, typename V>
struct RBNode {
  K key;
  V value;
  RBNode* left;
  RBNode* right;
  RBNode* parent;
  Color color;
  explicit RBNode(K k, V v, Color c = Color::RED) :
    key{k}, value{v}, left{nullptr}, right{nullptr}, parent {nullptr}, color{c} {}
  explicit RBNode(std::pair<K, V> p, Color c = Color::RED) :
    key{p.first}, value{p.second}, left{nullptr}, right{nullptr}, parent {nullptr}, color{c} {}

  void printData() {
    std::cout << "\naddressNode = " << this << "\nkey = " << key << "\nvalue = " << value
              << "\nright* = " << right << "\nleft* = " << left
              << "\nparent* = " << parent;
    std::cout << "\ncolor = ";
    if (color == Color::RED)
      std::cout << "RED\n";
    else if (color == Color::BLACK)
      std::cout << "BLACK\n";
  }

  RBNode* min() {
    return left == nullptr ? this : left->min();
  }

  RBNode* max() {
    return right == nullptr ? this : right->max();
  }

  RBNode* successor() {
    RBNode* succ = this;
    if (succ != nullptr) {

      if (succ->right != nullptr) {
        succ = succ->right;
        while (succ->left != nullptr)
          succ = succ->left;
      } else if (succ->parent != nullptr && succ == succ->parent->left) {
        succ = succ->parent;
      } else {
        while (succ->parent != nullptr && succ == succ->parent->right)
          succ = succ->parent;
        succ = succ->parent;
      }

    }
    return succ;
  }

  RBNode* predesessor() {
    RBNode *pred = this;

    if (pred != nullptr) {

      if (pred->left != nullptr) {
        pred = pred->left;
        while (pred->right != nullptr)
          pred = pred->right;
      } else if (pred->parent != nullptr && pred == pred->parent->right) {
        pred = pred->parent;
      } else {
        while (pred->parent != nullptr && pred == pred->parent->left)
          pred = pred->parent;
        pred = pred->parent;
      }

    }

    return pred;
  }
};

template<
  typename K,
  typename V,
  class Compare = std::less<K>,
  class Allocator = std::allocator<RBNode<K, V>>
> class RBTree {
    typedef RBNode<K, V>* node_ptr;
    node_ptr root;
    Allocator alloc;
    Compare comp;

  public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<const K, V> value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename std::allocator_traits<Allocator>::pointer pointer;
    typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;
    typedef RBNode<K, V> node_type;

    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    RBTree() : root{nullptr}, alloc{}, comp{} {}

    RBTree(const RBTree& other) : root{nullptr}, alloc{other.alloc}, comp{other.comp} {
      if (other.root != nullptr)
        root = copy_node(other.root, nullptr);
    }

    RBTree(const std::initializer_list<value_type>& ilist) :
                                                root{nullptr}, alloc{}, comp{} {
      for (auto i : ilist) insert(i);
    }

    RBTree(RBTree&& other) noexcept : root{std::move(other.root)},
                                      alloc{std::move(other.alloc)},
                                      comp{std::move(other.comp)} {
      other.root = nullptr;
    }

    RBTree& operator=(const RBTree& other) {
      RBTree tmp{other};
      std::swap(*this, tmp);
      return *this;
    }

    RBTree& operator=(RBTree&& other) noexcept {
      root = other.root;
      alloc = other.alloc;
      comp = other.comp;
      other.root = nullptr;
      return *this;
    }

    RBTree& operator=(const std::initializer_list<value_type>& ilist) {
      RBTree tmp{ilist};
      std::swap(*this, tmp);
      return *this;
    }

    ~RBTree() {
      clear();
    }

    void printTree() {
      if (root)
        printHelper(root, "", true);
    }

    void printSimmetric(node_ptr node) {
      if (node == nullptr) return;

      printSimmetric(node->left);
      std::cout << " " << node->key;
      printSimmetric(node->right);

    }

    V& at(const K& key) {
      node_ptr node = findNode(key);
      if (node == nullptr)
        throw std::out_of_range("map::at");
      return node->value;
    }

    const V& at(const K& key) const {
      node_ptr node = findNode(key);
      if (node == nullptr)
        throw std::out_of_range("map::at");
      return node->value;
    }

    V& operator[](const K& key) {
      node_ptr node = findNode(key);
      if (node == nullptr) {
        std::pair<iterator, bool> p = insert(value_type(key, V()));
        node = p.first.get_ptr();
      }
      return node->value;
    }

    iterator begin() noexcept {
      if (root == nullptr)
        return iterator(nullptr);
      return iterator(root->min());
    }

    const_iterator begin() const noexcept {
      if (root == nullptr)
        return const_iterator(nullptr);
      return const_iterator(root->min());
    }

    const_iterator cbegin() const noexcept {
      if (root == nullptr)
        return const_iterator(nullptr);
      return const_iterator(root->min());
    }

    iterator end() noexcept {
      return iterator();
    }

    const_iterator end() const noexcept {
      return const_iterator();
    }

    const_iterator cend() const noexcept {
      return const_iterator();
    }

    reverse_iterator rbegin() noexcept {
      return reverse_iterator(root->max());
    }

    reverse_iterator rend() noexcept {
      return reverse_iterator();
    }

    std::pair<iterator, bool> insert(const std::pair<const K, V>& value, bool unique = true) {
      /* std::cout << value.first << ' ' << value.second << std::endl; */
      node_ptr t = alloc.allocate(1);
      alloc.construct(t, RBNode<K, V>(value));
      if (empty()) {
        t->color = Color::BLACK;
        root = t;
        return std::pair<iterator, bool>(iterator(t), true);
      }
        node_ptr p = root;
        node_ptr q = nullptr; // future parent

        while (p != nullptr) {
          q = p;

          if (q->key == t->key && unique == true) {
            alloc.deallocate(t, 1);
            return std::pair<iterator, bool>(iterator(q), false);
          }

          if (comp(p->key, t->key))
            p = p->right;
          else
            p = p->left;
        }

        t->parent = q;
        if (comp(q->key, t->key))
          q->right = t;
        else
          q->left = t;
      fixInsertion(t);
      return std::pair<iterator, bool>(iterator(t), true);
    }

    template< class... Args >
      std::pair<iterator,bool> unique_emplace( Args&&... args ) {
        RBNode<K,V>* newNode = alloc.allocate(1);
        alloc.construct(newNode, RBNode<K,V>(std::forward<Args>(args)..., V()));

        if (empty()) {
          newNode->color = Color::BLACK;
          root = newNode;
          return std::make_pair(iterator(newNode), true);
        }
        
        node_ptr parent = nullptr;
        node_ptr curr = root;
        while (curr != nullptr) {
            parent = curr;
            if (comp(newNode->key, curr->key)) {
                curr = curr->left;
            } else if (comp(curr->key, newNode->key)) {
                curr = curr->right;
            } else {
                alloc.deallocate(newNode, 1);
                return std::make_pair(iterator(curr), false);
            }
        }
        
        newNode->parent = parent;
        if (!parent) {
            root = newNode;
        } else if (comp(newNode->key, parent->key)) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        fixInsertion(newNode);
        
        return std::make_pair(iterator(newNode), true);
    }

    template< class... Args >
      std::pair<iterator,bool> nounique_emplace( Args&&... args ) {
        RBNode<K,V>* newNode = alloc.allocate(1);
        alloc.construct(newNode, RBNode<K,V>(std::forward<Args>(args)..., V()));

        if (empty()) {
          newNode->color = Color::BLACK;
          root = newNode;
          return std::make_pair(iterator(newNode), true);
        }
        
        node_ptr parent = nullptr;
        node_ptr curr = root;
        while (curr != nullptr) {
            parent = curr;
            if (comp(newNode->key, curr->key))
                curr = curr->left;
            else
                curr = curr->right;
        }
        
        newNode->parent = parent;
        if (!parent) {
            root = newNode;
        } else if (comp(newNode->key, parent->key)) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        fixInsertion(newNode);
        
        return std::make_pair(iterator(newNode), true);
    }

    size_type erase(const K& key) {
      if (empty()) return 0;
      node_ptr tmp = root;

      while (tmp != nullptr && tmp->key != key) {
        if (comp(key, tmp->key))
          tmp = tmp->left;
        else
          tmp = tmp->right;
      }

      if (tmp == nullptr) return 0;

      /* std::cout << "Key to delete: " << tmp->key << std::endl; */
      std::cout << "deleting node: " << tmp->key << std::endl;
      removeNode(tmp);

      return 1;
    }

    void swap(RBTree& other) noexcept {
      std::swap(root, other.root);
      std::swap(alloc, other.alloc);
      std::swap(comp, other.comp);
    }

    iterator find(const K& key) {
      return iterator(findNode(key));
    }

    const_iterator find(const K& key) const {
      return const_iterator(findNode(key));
    }

    bool empty() const noexcept {
      return root == nullptr;
    }

    size_type size() const noexcept {
      return count_size(root);
    }

    void clear() noexcept {
      delete_node(root);
      root = nullptr;
    }

    node_ptr get_root() { return root; }

    int rb_assert (node_ptr rut, bool unique = true) {

       if (rut == NULL)
              return 1;
       else {
          int lh, rh;
          node_ptr ln = rut->left;
          node_ptr rn = rut->right;

          /* Consecutive red links */
          if (isRed(rut)) {
                 if (isRed(ln) || isRed(ln)) {
                   std::cout << "Red violation";
                   return 0;
                 }
          }

          lh = rb_assert (ln, unique);
          rh = rb_assert (rn, unique);

          /* Invalid binary search tree */
          if (unique == true) {
            if ((ln != nullptr && ln->key >= rut->key)
                   || (rn != nullptr && rn->key <= rut->key))
            {
              std::cout << "Binary tree violation";
                   return 0;
            }
          } else {
            if ((ln != nullptr && ln->key > rut->key)
                   || (rn != nullptr && rn->key < rut->key))
            {
              std::cout << "Binary tree violation";
                   return 0;
            }
          }
          

          /* Black height mismatch */
          if (lh != 0 && rh != 0 && lh != rh) {
            std::cout << "Black violation";
                 return 0;
          }

          /* Only count black links */
          if (lh != 0 && rh != 0)
                 return isRed(rut) ? lh : lh + 1;
          else
                 return 0;
       }
 } 
    
  private:

    // implement this for correct fixInsertion
    void rotateLeft(node_ptr node) {
      node_ptr base = node->right;

      base->parent = node->parent; // base can be the root
      if (node->parent != nullptr) {
        if (node->parent->left == node)
          node->parent->left = base;
        else
          node->parent->right = base;
      }

      node->right = base->left;
      if (base->left != nullptr)
        base->left->parent = node;
      
      node->parent = base;
      base->left = node;

      if (node == root) root = base;
    }

    void rotateRight(node_ptr node) {
      node_ptr base = node->left;

      base->parent = node->parent;
      if (node->parent != nullptr) {
        if (node->parent->left == node)
          node->parent->left = base;
        else
          node->parent->right = base;
      }

      node->left = base->right;
      if (base->right != nullptr)
        base->right->parent = node;

      node->parent = base;
      base->right = node;

      if (node == root) root = base;
    }

    // balance checking after tree changed
    void fixInsertion(node_ptr node) {
      if (node == root) {
        node->color = Color::BLACK;
        /* node->printData(); */
        return;
      }

      // если отец node - черный, никакое свойство дерева не нарушено
      // если красный - нарушается (3)
      while (node->parent && node->parent->color == Color::RED) {

        node_ptr gran = grandparent(node);
        node_ptr uncl = uncle(node);

        // достаточно рассмотреть 2 случая
        // 1: дядя node тоже красный
        if (gran) {
          // если отец - левый ребенок
          if (gran->left == node->parent) {

              // если есть красный дядя справа
            if (uncl != nullptr && uncl->color == Color::RED) {
              // перекрашиваем отца и дядю в черный цвет, а деда - в красный, node переносим на деда
              node->parent->color = Color::BLACK;
              uncl->color = Color::BLACK;
              gran->color = Color::RED;
              node = gran;
            } else { // нет дяди
              // если node - правый сын
              if (node->parent->right == node) {
                node = node->parent;
                rotateLeft(node);
              }
              node->parent->color = Color::BLACK;
              gran->color = Color::RED;
              rotateRight(gran);
            }
            // отец - правый ребенок
          } else {
            // если есть красный дядя слева
            if (uncl && uncl->color == Color::RED) {
              node->parent->color = Color::BLACK;
              uncl->color = Color::BLACK;
              gran->color = Color::RED;
              node = gran;
            } else { // нет дяди
              // если node - левый сын
              if (node->parent->left == node) {
                node = node->parent;
                rotateRight(node);
              }
              node->parent->color = Color::BLACK;
              gran->color = Color::RED;
              rotateLeft(gran);
            }
          }
        }
      }
      // корень всегда черный; если node был корнем, то в цикл не зашли и сразу попали сюда
      root->color = Color::BLACK;
    }

    /* 1. RED node, 2 children --> RED node, 0||1 child
     * 2. BLACK node, 2 children --> BLACK node, 0||1 child
     * 3. RED node, 1 child --> doesn't exist
     * 4. BLACK node, 1 child --> свапаем с красным ребенком и удаляем ребенка
     * 5. RED node, 0 child --> удаляем node, указатель у родителя - nullptr
     * 6. BLACK node, 0 child --> удаляем node, указатель у родителя - nullptr
     * 
     *  Если удаляемый элемент был черным - нужна балансировка
     */
    void removeNode(node_ptr node) {
      // case 5 && 6
      if (noChildren(node)) {

        if (node->color == Color::BLACK)
          fixDeleting(node);

        if (node->parent == nullptr)
          root = nullptr;
        else
          if (node->parent->left == node) {
            node->parent->left = nullptr;
          } else {
            node->parent->right = nullptr;
          }

        alloc.deallocate(node, 1);

      }

      // case 3 && 4
      else if (oneChild(node)) {
        // это может быть только черный элемент с красным ребенком без детей
        node_ptr child = node->left == nullptr ? node->right : node->left;

        node->key = child->key;
        node->value = child->value;

        if (child == node->left) node->left = nullptr;
        else node->right = nullptr;

        alloc.deallocate(child, 1);
        // балансировку делать не нужно, т.к. child точно красный
      }

      // case 1 && 2
      else {
        node_ptr rMin = rightMin(node);

        node->key = rMin->key;
        node->value = rMin->value;

        removeNode(rMin);
      }

    }

    void fixDeleting(node_ptr x) {
      node_ptr sibling;
      while (x != root && isBlack(x)) {
        if (x == x->parent->left) {
          sibling = x->parent->right;
          if (isRed(sibling)) {
            // case 3.1
            sibling->color = Color::BLACK;
            x->parent->color = Color::RED;
            rotateLeft(x->parent);
            sibling = x->parent->right;
          }

          if (isBlack(sibling) && isBlack(sibling->left) && isBlack(sibling->right)) {
            // case 3.2
            sibling->color = Color::RED;
            x = x->parent;
          } else {
            if (isBlack(sibling->right)) {
              // case 3.3
              sibling->left->color = Color::BLACK;
              sibling->color = Color::RED;
              rotateRight(sibling);
              sibling = x->parent->right;
            }

            // case 3.4
            sibling->color = x->parent->color;
            x->parent->color = Color::BLACK;
            sibling->right->color = Color::BLACK;
            rotateLeft(x->parent);
            x = root;
          }
        } else {
          sibling = x->parent->left;
          if (isRed(sibling)) {
            // case 3.1
            sibling->color = Color::BLACK;
            x->parent->color = Color::RED;
            rotateRight(x->parent);
            sibling = x->parent->left;
          }

          if (isBlack(sibling) && isBlack(sibling->left) && isBlack(sibling->right)) {
            // case 3.2
            sibling->color = Color::RED;
            x = x->parent;
          } else {
            if (isBlack(sibling->left)) {
              // case 3.3
              sibling->right->color = Color::BLACK;
              sibling->color = Color::RED;
              rotateLeft(sibling);
              sibling = x->parent->left;
            }

            // case 3.4
            sibling->color = x->parent->color;
            x->parent->color = Color::BLACK;
            sibling->left->color = Color::BLACK;
            rotateRight(x->parent);
            x = root;
          }
        }
      }
      x->color = Color::BLACK;
    }

    node_ptr grandparent(node_ptr n) {
      if (n != nullptr && n->parent != nullptr)
        return n->parent->parent;

      return nullptr;
    }

    node_ptr uncle(node_ptr n) {
      node_ptr grandpa = grandparent(n);
      if (nullptr == grandpa) // no grandparent = no uncle
        return nullptr;
      if (n->parent == grandpa->left)
        return grandpa->right;
      else
        return grandpa->left;
    }

    bool noChildren(node_ptr node) {
      return node->left == nullptr && node->right == nullptr;
    }

    bool oneChild(node_ptr node) {
      return (node->left == nullptr && node->right != nullptr) ||
             (node->left != nullptr && node->right == nullptr);
    }

    node_ptr rightMin(node_ptr node) {
      node_ptr tmp = node->right;
      node_ptr ret = nullptr;

      while (tmp != nullptr) {
        ret = tmp;
        tmp = tmp->left;
      }

      return ret;
    }

    bool isRed(node_ptr node) {
      return node != nullptr && node->color == Color::RED;
    }

    bool isBlack(node_ptr node) {
      return node == nullptr || node->color == Color::BLACK;
    }

    bool oneChildRed(node_ptr node) {
      return isRed(node->left) || isRed(node->right);
    }

    void printHelper(node_ptr root, std::string indent, bool last) {
      if (root != nullptr) {
      std::cout << indent;
        if (last) {
          std::cout << "R----";
          indent += "   ";
        } else {
          std::cout << "L----";
          indent += "|  ";
        }

        std::string sColor = root->color == Color::RED ? "RED" : "BLACK";
        std::cout << root->key << "(" << sColor << ")" << std::endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
      }
    }

    node_ptr copy_node(node_ptr src_node, node_ptr parent) {
      if (src_node == nullptr) return nullptr;

      node_ptr new_node = alloc.allocate(1);
      alloc.construct(new_node, RBNode<K, V>{src_node->key, src_node->value, src_node->color});
      new_node->parent = parent;
      new_node->left = copy_node(src_node->left, new_node);
      new_node->right = copy_node(src_node->right, new_node);
      return new_node;
    }

    void delete_node(node_ptr start) {
      if (start == nullptr) return;

      delete_node(start->left);
      delete_node(start->right);

      alloc.deallocate(start, 1);
    }

    size_type count_size(node_ptr rut) const {
      if (rut == nullptr) return 0;

      size_type sz = 1;
      sz += count_size(rut->left);
      sz += count_size(rut->right);

      return sz;
    }

    // iterator here and return end() if no key found
    node_ptr findNode(const K& key) {
      if (empty()) return nullptr;

      node_ptr tmp = root;
      while (tmp != nullptr && tmp->key != key) {
        if (comp(key, tmp->key))
          tmp = tmp->left;
        else
          tmp = tmp->right;
      }

      return tmp;
    }
    
  public:
    class iterator {
   public:
    iterator() : ptr{nullptr} {}
    explicit iterator(node_ptr p) : ptr{p} {}
    iterator(const iterator &iter) : ptr{iter.ptr} {}
    ~iterator() { ptr = nullptr; }

    iterator &operator=(const iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    bool operator==(const iterator &other) const { return ptr == other.ptr; }
    bool operator!=(const iterator &other) const { return ptr != other.ptr; }

    iterator &operator++() {
      ptr = ptr->successor();
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      ptr = ptr->successor();
      return tmp;
    }

    iterator &operator--() {
      ptr = ptr->predesessor();
      return *this;
    }

    iterator operator--(int) {
      iterator tmp = *this;
      ptr = ptr->predesessor();
      return tmp;
    }

    K& operator*() const {
      return ptr->key;
    }

    node_ptr get_ptr() const { return ptr; }

   private:
    node_ptr ptr;
    };

    class const_iterator {
   public:
    const_iterator() : ptr{nullptr} {}
    explicit const_iterator(node_ptr p) : ptr{p} {
    }

    explicit const_iterator(const const_iterator &iter) : ptr{iter.ptr} {}

    ~const_iterator() { ptr = nullptr; }

    const_iterator &operator=(const const_iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    bool operator==(const const_iterator &other) const { return ptr == other.ptr; }
    bool operator!=(const const_iterator &other) const { return ptr != other.ptr; }

    const_iterator &operator++() {
      ptr = ptr->successor();
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp = *this;
      ptr = ptr->successor();
      return tmp;
    }

    const_iterator &operator--() {
      ptr = ptr->predesessor();
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator tmp = *this;
      ptr = ptr->predesessor();
      return tmp;
    }

    const K& operator*() const {
      node_ptr tmp = const_cast<node_ptr>(ptr);
      return tmp->key;
    }

    node_ptr get_ptr() const { return ptr; }

   private:
    node_ptr ptr;
    };

    class reverse_iterator {
   public:
    reverse_iterator() : ptr{nullptr} {}
    explicit reverse_iterator(node_ptr p) : ptr{p} {}
    reverse_iterator(const reverse_iterator &iter) : ptr{iter.ptr} {}
    ~reverse_iterator() { ptr = nullptr; }

    reverse_iterator &operator=(const reverse_iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    bool operator==(const reverse_iterator &other) const { return ptr == other.ptr; }
    bool operator!=(const reverse_iterator &other) const { return ptr != other.ptr; }

    reverse_iterator &operator++() {
      ptr = ptr->predesessor();
      return *this;
    }

    reverse_iterator operator++(int) {
      reverse_iterator tmp = *this;
      ptr = ptr->predesessor();
      return tmp;
    }

    reverse_iterator &operator--() {
      ptr = ptr->successor();
      return *this;
    }

    reverse_iterator operator--(int) {
      reverse_iterator tmp = *this;
      ptr = ptr->successor();
      return tmp;
    }

    K& operator*() const {
      return ptr->key;
    }

    node_ptr get_ptr() const { return ptr; }

   private:
    node_ptr ptr;
    };

};

#endif // _RB_TREE_H_
