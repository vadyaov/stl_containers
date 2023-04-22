#include <iostream>
#include "stack.h"



int main() {
  s21::vector<int> v {1, 2, 3, 4, 5, 6};
  std::cout << v.back() << std::endl;
  s21::stack<int> s {1, 1, 2, 2, 3, 3, 4, 4, 5, 0};
  s21::stack<int> c = s;

  c.pop();

  s.print();
  c.print();
  return 0;
}
