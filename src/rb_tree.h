#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include <iostream>
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
    std::cout << "\nkey = " << key << "\nvalue = " << value
              << "\nright* = " << right << "\nleft* = " << left
              << "\nparent* = " << parent;
    std::cout << "\ncolor = ";
    if (color == Color::RED)
      std::cout << "RED\n";
    else if (color == Color::BLACK)
      std::cout << "BLACK\n";
  }
};

template<
  typename K,
  typename V,
  class Compare = std::less<K>,
  class Allocator = std::allocator<RBNode<K, V>>
> class RBTree {
  public:
    typedef RBNode<K, V> node_;
    typedef RBNode<K, V>* node_ptr;

    RBTree() : root{nullptr}, alloc{}, comp{} {}

    /* RBTree(const RBTree& other) {} */

    /* RBTree(RBTree&& other) noexcept {} */

    /* RBTree& operator=(const RBTree& other) { */
    /* } */

    /* RBTree& operator=(RBTree&& other) { */
    /* } */

    ~RBTree() {
    }

    void insert(const K& key, const V& value) {
      node_ptr t = alloc.allocate(1);
      alloc.construct(t, RBNode<K, V>(key, value));
      t->printData();
      if (empty()) {
        root = t;
      } else {
        node_ptr p = root;
        node_ptr q = nullptr; // future parent

        while (p != nullptr) {
          q = p;
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
      }
      fixTree(t);
    }

    void remove(const K& key);
    V find(const K& key);
    
    bool empty() {
      return root == nullptr;
    }
    
  private:
    node_ptr root;
    Allocator alloc;
    Compare comp;

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

    // implement this for correct fixTree
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
    }

    // balance checking after tree changed
    void fixTree(node_ptr node) {
      // если отец node - черный, никакое свойство дерева не нарушено
      // если красный - нарушается (3)
      while (node->parent && node->parent->color == Color::RED) {

        // достаточно рассмотреть 2 случая
        // 1: дядя node тоже красный

        if (node->parent->parent) {
          // если отец - левый ребенок
          if (node->parent->parent->left == node->parent) {

              // если есть красный дядя справа
            if (node->parent->parent->right && node->parent->parent->right->color == Color::RED) {
              // перекрашиваем отца и дядю в черный цвет, а деда - в красный, node переносим на деда
              node->parent->color = node->parent->parent->right->color = Color::BLACK;
              node->parent->parent->color = Color::RED;
              node = node->parent->parent;
            } else { // нет дяди
              // если node - правый сын
              if (node->parent->right == node) {
                node = node->parent;
                rotateLeft(node);
              }
              node->parent->color = Color::BLACK;
              node->parent->parent->color = Color::RED;
              rotateRight(node->parent->parent);
            }
            // отец - правый ребенок
          } else {

            // если есть красный дядя слева
            if (node->parent->parent->left && node->parent->parent->left->color == Color::RED) {
              node->parent->color = node->parent->parent->left->color = Color::BLACK;
              node->parent->parent->color = Color::RED;
              node = node->parent->parent;
            } else { // нет дяди
              // если node - левый сын
              if (node->parent->left == node) {
                node = node->parent;
                rotateRight(node);
              }
              node->parent->color = Color::BLACK;
              node->parent->parent->color = Color::RED;
              rotateLeft(node->parent->parent);
            }

          }
        }
      }
      // корень всегда черный; если node был корнем, то в цикл не зашли и сразу попали сюда
      root->color = Color::BLACK;
    }
};



#endif // _RB_TREE_H_
