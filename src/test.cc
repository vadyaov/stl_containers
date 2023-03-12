#include <iostream>
#include "s21_vector.h"
#include <vector>

int main() {

  std::vector<int> a{1, 2, 3, 4, 5, 6};
  std::vector<int> b{0, 0, 1, 1, 2, 2, 3, 4};
  std::cout << "size = " << a.size() << std::endl;
  std::cout << "capacity = " << a.capacity() << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;

  a.swap(b);
  std::cout << a.max_size() << std::endl;

  std::cout << "size = " << a.size() << std::endl;
  std::cout << "capacity = " << a.capacity() << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;

  std::cout << "size = " << b.size() << std::endl;
  std::cout << "capacity = " << b.capacity() << std::endl;
  for (auto i : b)
    std::cout << i << " ";
  std::cout << std::endl;

/*   a.pop_back(); */

/*   std::cout << "size = " << a.size() << std::endl; */
/*   std::cout << "capacity = " << a.capacity() << std::endl; */
/*   for (auto i : a) */
/*     std::cout << i << " "; */
/*   std::cout << std::endl; */

  return 0;
}
