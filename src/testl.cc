#include <iostream>
#include <list>
#include <vector>
#include "s21_list.h"

int main() {
  /* std::vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; */
  std::list<int> a (10, -1);
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "a.size = " << a.size() << std::endl;
  a.resize(9);
  a.push_front(11);
  a.pop_back();
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "a.size = " << a.size() << std::endl;
  return 0;
}
