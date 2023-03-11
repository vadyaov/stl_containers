#include <iostream>
#include "s21_vector.h"
#include <vector>

int main() {

  s21::vector<int> a{1, 2, 3, 4, 5, 6};
  std::cout << "size = " << a.size() << std::endl;
  std::cout << "capacity = " << a.capacity() << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;

  a.resize(3);
  /* a.shrink_to_fit(); */

  std::cout << "size = " << a.size() << std::endl;
  std::cout << "capacity = " << a.capacity() << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;

  /* std::cout << "size = " << b.size() << std::endl; */
  /* std::cout << "capacity = " << b.capacity() << std::endl; */
  /* for (auto i : b) */
  /*   std::cout << i << " "; */
  /* std::cout << std::endl; */

/*   a.pop_back(); */

/*   std::cout << "size = " << a.size() << std::endl; */
/*   std::cout << "capacity = " << a.capacity() << std::endl; */
/*   for (auto i : a) */
/*     std::cout << i << " "; */
/*   std::cout << std::endl; */

  return 0;
}
