#include <iostream>
#include "vector/s21_vector.h"
#include <vector>

int main() {

  std::vector<int> a{1, 2, 3, 4, 5};
  std::cout << "size = " << a.size() << std::endl;
  std::cout << "capacity = " << a.capacity() << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;

  /* const std::vector<int> extra (1, -3); */
  /* a.assign(extra.begin(), extra.end()); */
  a.assign(3, -1);

  std::cout << "size = " << a.size() << std::endl;
  std::cout << "capacity = " << a.capacity() << std::endl;
  for (auto i : a)
    std::cout << i << " ";
  std::cout << std::endl;

  /* s21::vector<int> b{std::move(a)}; */


  /* std::cout << "size = " << a.size() << std::endl; */
  /* std::cout << "capacity = " << a.capacity() << std::endl; */
  /* for (auto i : a) */
  /*   std::cout << i << " "; */
  /* std::cout << std::endl; */

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
