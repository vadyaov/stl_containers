#include <iostream>
#include <list>
#include <vector>
#include "s21_list.h"

int main() {
  std::vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> a(v.begin(), v.end(), v.get_allocator());
  a.printList();
  std::cout << a.size() << std::endl;
  s21::list<int> b {a};
  b.printList();
  std::cout << b.size() << std::endl;
  return 0;
}
