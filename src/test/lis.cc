#include <queue>
#include <iostream>
#include <string>

#include "../containers/queue.h"

using std::string;

int main() {
  s21::queue<int> l1;

  l1.push(1);
  l1.push(2);
  l1.push(3);
  l1.push(4);

  std::cout << l1.front() << " " << l1.back() << std::endl;

  return 0;
}
