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
    if (left == nullptr) return this;
    return left->min();
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

    std::pair<K, V>& operator*() const {
      return std::pair<K, V>(ptr->key, ptr->value);
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

    std::pair<K, V>& operator*() const {
      return std::pair<K, V>(ptr->key, ptr->value);
    }

    node_ptr get_ptr() const { return ptr; }

   private:
    node_ptr ptr;
    };

    RBTree() : root{nullptr}, alloc{}, comp{} {}

    RBTree(const RBTree& other) : root{nullptr}, alloc{other.alloc}, comp{other.comp} {
      if (other.root != nullptr)
        root = copy_node(other.root, nullptr);
    }

    explicit RBTree(const std::initializer_list<value_type>& ilist) :
                                                root{nullptr}, alloc{}, comp{} {
      for (auto i : ilist) insert(i);
    }

    RBTree(RBTree&& other) noexcept : root{other.root},
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

    ~RBTree() {
      delete_node(root);
      root = nullptr;
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
      node_ptr node = find(key);
      if (node == nullptr)
        throw std::out_of_range("Can't find node with 'key'");
      return node->value;
    }

    const V& at(const K& key) const {
      node_ptr node = find(key);
      if (node == nullptr)
        throw std::out_of_range("Can't find node with 'key'");
      return node->value;
    }

    V& operator[](const K& key) {
      node_ptr node = find(key);
      if (node == nullptr) {
        std::pair<iterator, bool> p = insert(value_type(key, V()));
        node = p.first.get_ptr();
      }
      return node->value;
    }

    iterator begin() noexcept {
      return iterator(root->min());
    }

    const_iterator begin() const noexcept {
      return const_iterator(root->min());
    }

    iterator end() noexcept {
      return iterator();
    }

    const_iterator end() const noexcept {
      return const_iterator();
    }

    std::pair<iterator, bool> insert(const std::pair<const K, V>& value, bool unique = true) {
      node_ptr t = alloc.allocate(1);
      alloc.construct(t, RBNode<K, V>(value.first, value.second));
      if (empty()) {
        t->color = Color::BLACK;
        root = t;
        return std::pair<iterator, bool>(iterator(t), true);
      }
        node_ptr p = root;
        node_ptr q = nullptr; // future parent

        while (p != nullptr) {
          q = p;
          if (comp(p->key, t->key))
            p = p->right;
          else
            p = p->left;
        }
        // checking for unique
        if (q->key == t->key && unique == true) {
          std::cout << "Not unique key. Skip\n";
          t->printData();
          alloc.deallocate(t, 1);
          return std::pair<iterator, bool>(iterator(q), false);
        }

        t->parent = q;
        if (comp(q->key, t->key))
          q->right = t;
        else
          q->left = t;
      fixInsertion(t);
      return std::pair<iterator, bool>(iterator(t), true);
    }

    void remove(const K& key) {
      if (empty()) return;
      node_ptr tmp = root;

      while (tmp != nullptr && tmp->key != key) {
        if (comp(key, tmp->key))
          tmp = tmp->left;
        else
          tmp = tmp->right;
      }

      if (tmp == nullptr) {
        std::cout << "Can't find Node with key " << key << std::endl;
        return;
      }

      removeNode(tmp);

    }

    // iterator here and return end() if no key found
    node_ptr find(const K& key) {
      if (empty()) throw std::runtime_error("RBTree is empty");

      node_ptr tmp = root;
      while (tmp != nullptr && tmp->key != key) {
        if (comp(key, tmp->key))
          tmp = tmp->left;
        else
          tmp = tmp->right;
      }

      return tmp;
    }
    
    bool empty() const {
      return root == nullptr;
    }

    node_ptr get_root() { return root; }

    int rb_assert (node_ptr rut) {

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

          lh = rb_assert (ln);
          rh = rb_assert (rn);

          /* Invalid binary search tree */
          if ((ln != nullptr && ln->key >= rut->key)
                 || (rn != nullptr && rn->key <= rut->key))
          {
            std::cout << "Binary tree violation";
                 return 0;
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
        node_ptr node_brother = nullptr;
        if (node->parent == nullptr)
          root = nullptr;
        else
          if (node->parent->left == node) {
            node->parent->left = nullptr;
            node_brother = node->parent->right;
          } else {
            node->parent->right = nullptr;
            node_brother = node->parent->left;
          }

        Color node_color = node->color;
        alloc.deallocate(node, 1);
        if (root != nullptr && node_color == Color::BLACK) {
          fixDeleting(node->parent, node_brother);
        }
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
        std::cout << "\nNode have 2 children.\n";
        node_ptr rMin = rightMin(node);

        node->key = rMin->key;
        node->value = rMin->value;

        removeNode(rMin);
      }

    }

    bool noChildren(node_ptr node) {
      return node->left == nullptr && node->right == nullptr;
    }

    // node - parent удаленного узла
    void fixDeleting(node_ptr node, node_ptr brother) {
      std::cout << "\nInside FixDeleting...\n";

/*       node_ptr bro = node->left == nullptr ? node->right : node->left; */

/*       std::cout << "BRO:\n"; */
/*       bro->printData(); */

/*       std::cout << "BROTHER:\n"; */
/*       brother->printData(); */

      if (isRed(node) && isBlack(brother) && isBlack(brother->left) &&
          isBlack(brother->right)) {
        node->color = Color::BLACK;
        brother->color = Color::RED;
      } else if (isRed(node) && isBlack(brother) && oneChildRed(brother)) {
        if (brother == node->left && isRed(brother->left)) {
            node->color = Color::BLACK;
            brother->color = Color::RED;
            brother->left->color = Color::BLACK;
            rotateRight(node);
        } else if (brother == node->right && isRed(brother->right)) {
            node->color = Color::BLACK;
            brother->color = Color::RED;
            brother->right->color = Color::BLACK;
            rotateLeft(node);
        }
      } else if (node->color == Color::BLACK && isRed(brother)) {
        // ЧК3
        if (brother == node->left && brother->right != nullptr &&
            isBlack(brother->right->left) && isBlack(brother->right->right)) {
          brother->color = Color::BLACK;
          brother->right->color = Color::RED;
          rotateRight(node);
        } else if (brother == node->right && brother->left != nullptr &&
            isBlack(brother->left->left) && isBlack(brother->left->right)) {
          brother->color = Color::BLACK;
          brother->left->color = Color::RED;
          rotateLeft(node);
          // ЧК4
        } else if (brother == node->left && brother->right != nullptr &&
            isRed(brother->right->left)) {
            brother->right->left->color = Color::BLACK;
            rotateLeft(brother);
            rotateRight(node);
        } else if (brother == node->right && brother->left != nullptr &&
            isRed(brother->left->right)) {
            brother->left->right->color = Color::BLACK;
            rotateRight(brother);
            rotateLeft(node);
        }
      } else if (isBlack(node) && isBlack(brother)) {
        if (brother == node->left && isRed(brother->right)) {
          brother->right->color = Color::BLACK;
          rotateLeft(brother);
          rotateRight(node);
        } else if (brother == node->right && isRed(brother->left)) {
          brother->left->color = Color::BLACK;
          rotateRight(brother);
          rotateLeft(node);
        } else if (isBlack(brother->left) && isBlack(brother->right)) {
          brother->color = Color::RED;
          std::cout << "\nRecursion....\n";
          if (node->parent != nullptr) {
            node_ptr node_brother = node->parent->right == node ?
                                    node->parent->left : node->parent->right;
            fixDeleting(node->parent, node_brother);
          }
        }
      } 
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
      // because list node is always black
      return node == nullptr || node->color == Color::BLACK;
      /* return node != nullptr && node->color == Color::BLACK; */
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
};



#endif // _RB_TREE_H_
