#include <iostream>
#include <list>
#include <vector>
#include "s21_list.h"

int main() {
  s21::list<int> v {1, 0, -19, 5, -6, -7, -8, -9, -10};
  s21::list<int> a {1, 1, 1, 1, 1, -11, 85, 1, 43, 500, -6, 500, 7, 7, 7, 8, 9, 10};
  std::cout << "a:" << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "a.size = " << a.size() << std::endl;

  std::cout << "v:" << std::endl;
  for (auto i : v)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "v.size = " << a.size() << std::endl;

  a.splice(a.cbegin(), std::move(v), ++v.cbegin());

  std::cout << "a:" << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "a.size = " << a.size() << std::endl;

  std::cout << "v:" << std::endl;
  for (auto i : v)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "v.size = " << v.size() << std::endl;
  return 0;
}
