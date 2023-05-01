#include "rb_tree.h"
#include <map>

int main() {
  RBTree<int, int> tree;
  tree.insert(std::pair<int, int>(20, 0));
  tree.insert(std::pair<int, int>(10, 1));
  tree.insert(std::pair<int, int>(25, 2));
  tree.insert(std::pair<int, int>(4, 3));
  tree.insert(std::pair<int, int>(16, 4));
  /* tree.insert(23, 5); */
  tree.insert(std::pair<int, int>(30, 5));
  tree.insert(std::pair<int, int>(21, 5));
  tree.insert(std::pair<int, int>(24, 5));
  tree.insert(std::pair<int, int>(31, 5));
  tree.insert(std::pair<int, int>(48, 5));
  tree.insert(std::pair<int, int>(2, -10));
  tree.insert(std::pair<int, int>(-1, -10));
  tree.insert(std::pair<int, int>(9, 5));
  tree.insert(std::pair<int, int>(14, -1));
  tree.insert(std::pair<int, int>(17, 15));
  tree.insert(std::pair<int, int>(1, 15));
  tree.insert(std::pair<int, int>(12, 15));
  tree.insert(std::pair<int, int>(15, 15));
  tree.insert(std::pair<int, int>(19, 15));
  tree.insert(std::pair<int, int>(-10, 15));
  tree.insert(std::pair<int, int>(7, 15));
  tree.insert(std::pair<int, int>(8, 15));
  tree.insert(std::pair<int, int>(13, 15));

  /* tree.remove(30); */
  /* tree.remove(48); */
  /* tree.remove(24); */
  tree.printTree();
  std::cout << std::endl;

  tree.printSimmetric(tree.get_root());
  std::cout << std::endl;

  std::cout << "ASSERT: " << tree.rb_assert(tree.get_root());

  /* RBTree<int, int>::iterator it = tree.begin(); */
  /* std::cout << (*it).first << std::endl; */
  RBTree<int, int> treecpy{tree};

  /* treecpy.printTree(); */
  /* std::cout << std::endl; */

  /* treecpy.printSimmetric(tree.get_root()); */
  /* std::cout << std::endl; */

  /* std::cout << "ASSERT: " << treecpy.rb_assert(tree.get_root()); */



  /* std::cout << "\nAFTER REMOVE\n"; */
  /* tree.printTree(); */
  /* std::cout << std::endl; */

  /* tree.printSimmetric(tree.get_root()); */
  /* std::cout << std::endl; */

  /* std::cout << "ASSERT: " << tree.rb_assert(tree.get_root()); */

  /* std::map<int, int> mymap; */
  /* mymap.insert(std::pair<int, int>(20, 1)); */
  /* mymap.insert(std::pair<int, int>(10, 2)); */
  /* mymap.insert(std::pair<int, int>(25, 3)); */

  /* auto it = ++mymap.begin(); */
  /* std::cout << (*++it).first; */

  return 0;
}
