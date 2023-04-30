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

    void printSimmetric(node_ptr node) {
      if (node == nullptr) return;

      printSimmetric(node->left);
      std::cout << " " << node->key;
      printSimmetric(node->right);

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

    /* void removeNode(node_ptr node) { */
    /*   // если у node нет детей, изменяем указатель на node у родителя на nullptr */
    /*   if (node->left == nullptr && node->right == nullptr) { */
    /*     if (node == root) { */
    /*       root = nullptr; */
    /*     } else { */
    /*       if (node->parent->left == node) */
    /*         node->parent->left = nullptr; */
    /*       else */
    /*         node->parent->right = nullptr; */
    /*     } */
    /*     alloc.deallocate(node, 1); */
    /*     return; */
    /*   } */

    /*   node_ptr y = node; */
    /*   node_ptr q = y->parent; */

    /*   // если у 'y' один ребенок -> указатель на 'y' у родителя меняем на ребенка */
    /*   if (oneChild(node)) { */

    /*       if (y->parent->left == node) */
    /*         y->parent->left = y->left == nullptr ? y->right : y->left; */
    /*       else */
    /*         y->parent->right = y->left == nullptr ? y->right : y->left; */
        
    /*     alloc.deallocate(node, 1); */
    /*   } else { // имеются оба ребенка */
    /*     // находим либо наибольший элемент в левом поддереве, либо наименьший в правом. */
    /*     // я буду искать наименьший в правом */
    /*     y = rightMin(node); // у 'y' нем может быть левого ребенка! */
    /*     q = y->parent; */
    /*     if (y->right != nullptr) */
    /*       y->right->parent = y->parent; */
    /*     if (y == root) // не представляю ситуацию в которой 'y' оказывается корнем */
    /*       root = y->right; */
    /*     else { // у родителя указатель на 'y' меняем на указатель на правого ребенка 'y'(мб null) */
    /*       if (y->parent->left == y) */
    /*         y->parent->left = y->right; */
    /*       else */
    /*         y->parent->right = y->right; */
    /*     } */
    /*   } */
      
    /*   if (y != node) { */
    /*     node->color = y->color; */
    /*     node->key = y->key; */
    /*     node->value = y->value; */
    /*   } */

    /*   // запомниаем цвет удаляемого узла и его родителя */
    /*   Color y_color = y->color; */
    /*   alloc.deallocate(y, 1); */
    /*   // при удалении черной вершины могла быть нарушена балансировка */
    /*   if (y_color == Color::BLACK) */
    /*     fixDeleting(q); */

    /* } */

    // node - parent удаленного узла
    void fixDeleting(node_ptr node, node_ptr brother) {
      std::cout << "\nInside FixDeleting...\n";

/*       node_ptr bro = node->left == nullptr ? node->right : node->left; */

/*       std::cout << "BRO:\n"; */
/*       bro->printData(); */

/*       std::cout << "BROTHER:\n"; */
/*       brother->printData(); */

      // case 1: node RED (получается один из потомков обязательно nullptr,
      //                         оставшийся потомок - брат удаленного узла)
      //         brother BLACK with BLACK childrens
      if (isRed(node) && isBlack(brother) && isBlack(brother->left) &&
          isBlack(brother->right)) {
        node->color = Color::BLACK;
        brother->color = Color::RED;
      } else if (isRed(node) && isBlack(brother) && oneChildRed(brother)) {
        if (brother == node->left && isRed(brother->left)) {
            std::cout << "KCH2 for x right\n";
            node->color = Color::BLACK;
            brother->color = Color::RED;
            brother->left->color = Color::BLACK;
            rotateRight(node);
        } else if (brother == node->right && isRed(brother->right)) {
            std::cout << "KCH2 for x left\n";
            node->color = Color::BLACK;
            brother->color = Color::RED;
            brother->right->color = Color::BLACK;
            rotateLeft(node);
        }
      } else if (node->color == Color::BLACK && isRed(brother)) {
        // ЧК3
        if (brother == node->left && brother->right != nullptr &&
            isBlack(brother->right->left) && isBlack(brother->right->right)) {
          std::cout << "!!!!\n";
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
        }
      } else if (isBlack(node) && isBlack(brother) &&
                 isBlack(brother->left) && isBlack(brother->right)) {
        brother->color = Color::RED;
        std::cout << "\nRecursion....\n";
        if (node->parent != nullptr) {
          node_ptr node_brother = node->parent->right == node ?
                                  node->parent->left : node->parent->right;
          fixDeleting(node->parent, node_brother);
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


};



#endif // _RB_TREE_H_
