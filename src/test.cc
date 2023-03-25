#include <iostream>
#include "s21_vector.h"
#include <vector>

int main() {

  std::vector<int> a{1, 2, 3, 4, 5, 6};
  std::vector<int> b{0, 0, 1, 1, 2, 2, 3, 4};

  std::cout << "a.size = " << a.size() << std::endl;
  std::cout << "a.capacity = " << a.capacity() << std::endl;
  for (const auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;

  a = b;

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
