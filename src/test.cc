#include <iostream>
#include "vector.h"
#include <vector>

int main() {

  s21::vector<int> a{-1, -2, -3, -4, -5, -6};
  s21::vector<int> b{1, 2, 3, 4, 5, 6};

  /* s21::vector<int>::const_iterator k(a.cbegin()); */
  /* s21::vector<int>::const_iterator l(a.cend() - 2); */

  /* std::cout << *k << " " << *l << " " << *(k + l); */

  std::cout << "a.size = " << a.size() << std::endl;
  std::cout << "a.capacity = " << a.capacity() << std::endl;
  for (auto i = a.begin(); i != a.end(); ++i)
    std::cout << *i << " ";
  std::cout << std::endl;
  /* a.emplace(a.begin() + 2, 30, 11, 8, -10); */
  std::cout << "b.size = " << b.size() << std::endl;
  std::cout << "b.capacity = " << b.capacity() << std::endl;
  for (auto i : b)
    std::cout << i << " ";
  std::cout << std::endl;

  s21::vector<int>::iterator it = --a.end();
  std::cout << *it << std::endl;
  a.swap(b);
  std::cout << *it << std::endl;

  /* a.pop_back(); */
  /* std::cout << *a.erase(a.begin() + 2, a.begin() + 10) << std::endl;; */
  /* a.insert(a.end(), 1); */
  /* std::cout << *(a.insert(a.begin() + 2, 10, 0)) << std::endl; */

  std::cout << "a.size = " << a.size() << std::endl;
  std::cout << "a.capacity = " << a.capacity() << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;

  std::cout << "b.size = " << b.size() << std::endl;
  std::cout << "b.capacity = " << b.capacity() << std::endl;
  for (auto i : b)
    std::cout << i << " ";
  std::cout << std::endl;

    return 0;
}
