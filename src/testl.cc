#include <iostream>
#include <list>
#include <vector>
#include "s21_list.h"

int main() {
  s21::list<int> v {1, 3, 3, 5, -6, -7, -8, -9, -10};
  s21::list<int> a {1, -11, 85, 43, 500, -6, 7 ,8, 9, 10};
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "a.size = " << a.size() << std::endl;

  for (auto i : v)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "v.size = " << a.size() << std::endl;
  /* std::cout << *a.emplace(a.cbegin(), 3) << std::endl; */
  /* std::cout << *a.erase(a.cbegin()) << std::endl; */
  /* std::cout << *a.insert(a.cend(), {-5, -1, -1, -1, -1, -1, -1}) << std::endl; */
  /* v.sort(); */
  a.sort();
  a.merge(std::move(v));
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "a.size = " << a.size() << std::endl;

  for (auto i : v)
    std::cout << i << " ";
  std::cout << std::endl;
  std::cout << "v.size = " << v.size() << std::endl;
  return 0;
}
