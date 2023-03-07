#include <iostream>
#include "vector/s21_vector.h"
#include <vector>

int main() {

  std::vector<int> a(11, 3);
  std::cout << "size = " << a.size() << std::endl;
  std::cout << "capacity = " << a.capacity() << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;
  a.resize(15);
  /* a.push_back(10); */
  std::cout << "size = " << a.size() << std::endl;
  std::cout << "capacity = " << a.capacity() << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;

  return 0;
}
