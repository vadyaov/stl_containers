#include <iostream>
#include <list>
#include <vector>
#include "s21_list.h"

int main() {
  std::vector<int> v {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
  s21::list<int> a {1, 2, 3, 4, 5, 6, 7 ,8, 9, 10};
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "a.size = " << a.size() << std::endl;
  a.erase(++a.cbegin());
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "b.size = " << a.size() << std::endl;
  return 0;
}
