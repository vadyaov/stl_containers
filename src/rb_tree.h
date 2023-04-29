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
};

template<
  typename K,
  typename V,
  class Compare = std::less<K>,
  class Allocator = std::allocator<RBNode<K, V>>
> class RBTree {
  public:
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

    void printTree() {
      if (root)
        printHelper(root, "", true);
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

    void insert(const K& key, const V& value) {
      node_ptr t = alloc.allocate(1);
      alloc.construct(t, RBNode<K, V>(key, value));
      if (empty()) {
        t->color = Color::BLACK;
        root = t;
        return;
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
        if (q->key == t->key) {
          std::cout << "Not unique key. Skip\n";
          t->printData();
          alloc.deallocate(t, 1);
          return;
        }

        t->parent = q;
        if (comp(q->key, t->key))
          q->right = t;
        else
          q->left = t;
      fixInsertion(t);
    }

    void remove(const K& key) {
      if (empty()) return;
      node_ptr tmp = root;

      while (tmp->key != key) {
        if (comp(key, tmp->key))
          tmp = tmp->left;
        else
          tmp = tmp->right;
      }

      /* tmp->printData(); */
      removeNode(tmp);

    }

    V find(const K& key);
    
    bool empty() {
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
        node->printData();
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

    void removeNode(node_ptr node) {
      // если у node нет детей
      if (node->left == nullptr && node->right == nullptr) {
        if (node == root) {
          root = nullptr;
        } else {
          if (node->parent->left == node)
            node->parent->left = nullptr;
          else
            node->parent->right = nullptr;
        }
        alloc.deallocate(node, 1);
        return;
      }

      node_ptr y = nullptr;
      node_ptr q = nullptr;

      // если у node один ребенок
      if (oneChild(node)) {

          if (node->parent->left == node)
            node->parent->left = node->left == nullptr ? node->right : node->left;
          else
            node->parent->right = node->left == nullptr ? node->right : node->left;
        
      alloc.deallocate(node, 1);
      } else { // имеются оба ребенка
        // находим либо наибольший элемент в левом поддереве, либо наименьший в правом.
        // я буду искать наименьший в правом
        y = rightMin(node); // нет левого ребенка!
        if (y->right != nullptr)
          y->right->parent = y->parent;
        if (y == root) // не представляю ситуацию в которой y оказывается корнем
          root = y->right;
        else {
          if (y->parent->left == y)
            y->parent->left = y->right;
          else
            y->parent->right = y->right;
        }
      }
      
      if (y != node) {
        node->color = y->color;
        node->key = y->key;
        node->value = y->value;
      }
      Color y_color = y->color;
      alloc.deallocate(y, 1);
      /* if (y_color == Color::BLACK) */
        /* fixDeleting(); */

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


};



#endif // _RB_TREE_H_
