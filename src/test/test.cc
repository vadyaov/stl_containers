/* #include <iostream> */
#include "../vector.h"
#include <vector>

int main() {

  s21::vector<int> a{-1, -2, -3, -4, -5, -6};
  /* s21::vector<int> b{1, 2, 3, 4, 5, 6}; */

  std::cout << "a.size = " << a.size() << std::endl;
  std::cout << "a.capacity = " << a.capacity() << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;

  a.emplace_back(1);

  std::cout << "a.size = " << a.size() << std::endl;
  std::cout << "a.capacity = " << a.capacity() << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;
  /* std::cout << "b.size = " << b.size() << std::endl; */
  /* std::cout << "b.capacity = " << b.capacity() << std::endl; */
  /* for (auto i : b) */
  /*   std::cout << i << " "; */
  /* std::cout << std::endl; */

    return 0;
}
