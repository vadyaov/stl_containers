#include <iostream>
#include <list>
#include "s21_list.h"

int main() {
  std::list<int> a;
  auto al = a.get_allocator();
  std::cout << a.size() << std::endl;
  return 0;
}
