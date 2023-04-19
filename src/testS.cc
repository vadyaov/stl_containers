#include <iostream>
#include "stack.h"

int main() {
  s21::vector<int> v {1, 2, 3, 4, 5, 6};
  s21::stack<int> s {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
  s21::stack<int> c = s;

  s.print();
  c.print();
  return 0;
}
