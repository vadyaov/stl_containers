#include <list>
#include <iostream>
#include <string>

#include "../containers/list.h"

using std::string;

int main() {
  s21::list<int> l1 {1, 2, 3, 4};
  s21::list<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8};

  /* s21::list<int> l3 {std::move(l1)}; */
  /* std::cout << l3.size() << std::endl; */

  l2 = std::move(l1);
  std::cout << l2.size() << std::endl;
  std::cout << l1.size() << std::endl;

  return 0;
}
