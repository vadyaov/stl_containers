#include "../rb_tree.h"
#include <map>

int main() {

  typedef typename std::pair<int, int> pair;

  RBTree<int, int> tree; //{pair(20, 0), pair(10, 1), pair(25, 3), pair(4,4)};
  tree.insert(pair(20, 0));
  tree.insert(pair(10, 1));
  tree.insert(pair(25, 2));
  tree.insert(pair(4, 3));
  tree.insert(pair(16, 4));
  tree.insert(pair(23, 5));
  tree.insert(pair(30, 5));
  tree.insert(pair(21, 5));
  tree.insert(pair(24, 5));
  tree.insert(pair(31, 5));
  tree.insert(pair(48, 5));
  tree.insert(pair(2, -10));
  tree.insert(pair(-1, -10));
  tree.insert(pair(9, 5));
  tree.insert(pair(14, -1));
  tree.insert(pair(17, 15));
  tree.insert(pair(1, 15));
  tree.insert(pair(12, 15));
  tree.insert(pair(15, 15));
  tree.insert(pair(19, 15));
  tree.insert(pair(-10, 15));
  tree.insert(pair(7, 15));
  tree.insert(pair(8, 15));
  tree.insert(pair(13, 15));

  /* tree.remove(30); */
  /* tree.remove(48); */
  /* tree.remove(24); */
  tree.printTree();
  std::cout << std::endl;

  tree.printSimmetric(tree.get_root());
  std::cout << std::endl;

  std::cout << "ASSERT: " << tree.rb_assert(tree.get_root(), true) << std::endl;

  std::cout << tree.size() << std::endl;

  tree.emplace(std::make_pair(-4, -4));

  /* RBTree<int, int>::iterator it = tree.begin(); */
  /* std::cout << (*it).first << std::endl; */
  /* RBTree<int, int> treecpy =tree; */

  tree.printTree();
  std::cout << std::endl;

  tree.printSimmetric(tree.get_root());
  std::cout << std::endl;

  /* std::cout << "ASSERT: " << tree.rb_assert(tree.get_root()); */



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
