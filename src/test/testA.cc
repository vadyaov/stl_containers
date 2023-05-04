#include <iostream>
#include <array>

#include "../array.h"

int main() {
  s21::array<int, 4> a1 {1, 2, 3, 4};
  s21::array<int, 4> a2 {-1, -2, -3, -4};

  std::cout << a1.at(3) << std::endl;
  std::cout << a2.at(3) << std::endl;

  a1.swap(a2);

  std::cout << a1.at(3) << std::endl;
  std::cout << a2.at(3) << std::endl;

  a1.fill(100);
  /* s21::array<int, 4>::iterator it; */
  /* std::cout << *it; */

  for (auto i = a1.rbegin(); i != a1.rend(); ++i)
    std::cout << " " << *i;
  std::cout << std::endl;

  return 0;
}
