#include <iostream>
#include "queue.h"



int main() {
  s21::list<int> l {1, 2, 3, 4, 5, 6};
  s21::queue<int> s {1, 1, 2, 2, 3, 3, 4, 4, 5, 0};
  s21::queue<int> c = std::move(s);

  c.pop();
  /* std::cout << c.front() << std:: endl; */

  s.print();
  c.print();
  return 0;
}
