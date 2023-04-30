#include "rb_tree.h"

int main() {
  RBTree<int, int> tree;
  tree.insert(20, 0);
  tree.insert(10, 1);
  tree.insert(25, 2);
  tree.insert(4, 3);
  tree.insert(16, 4);
  /* tree.insert(23, 5); */
  /* tree.insert(30, 5); */
  tree.insert(2, -10);
  /* tree.insert(9, 5); */
  /* tree.insert(14, -1); */
  /* tree.insert(17, 15); */
  /* tree.insert(1, 15); */
  /* tree.insert(12, 15); */
  /* tree.insert(15, 15); */
  /* tree.insert(19, 15); */
  /* tree.insert(-10, 15); */
  /* tree.insert(7, 15); */
  /* tree.insert(8, 15); */
  /* tree.insert(13, 15); */

  tree.printTree();
  std::cout << std::endl;

  tree.printSimmetric(tree.get_root());
  std::cout << std::endl;

  std::cout << "ASSERT: " << tree.rb_assert(tree.get_root());

  tree.remove(25);

  std::cout << "\nAFTER REMOVE\n";
  tree.printTree();
  std::cout << std::endl;

  tree.printSimmetric(tree.get_root());
  std::cout << std::endl;

  std::cout << "ASSERT: " << tree.rb_assert(tree.get_root());

  return 0;
}
