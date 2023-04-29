#include "rb_tree.h"

int main() {
  RBTree<int, int> tree;
  tree.insert(10, 0);
  tree.insert(6, 1);
  tree.insert(3, 2);
  tree.insert(8, 3);
  tree.insert(45, 4);
  tree.insert(4, 5);
  tree.insert(0, 5);
  tree.insert(-3, -10);
  tree.insert(5, 5);

  tree.printTree();
  std::cout << std::endl;

  std::cout << "ASSERT: " << tree.rb_assert(tree.get_root());
  /* tree.remove(4); */

  /* tree.printTree(); */

  return 0;
}
