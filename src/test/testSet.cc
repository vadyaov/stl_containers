#include <iostream>
#include <set>

#include "../set.h"

int main() {

  // default ctor
  s21::set<std::string> a;
  a.insert("cat");
  a.insert("dog");
  a.insert("horse");

  for (auto& str : a)
    std::cout << str << ' ';

  std::cout << std::endl;

  // copy ctor
  s21::set<std::string> c(a);
  c.insert("another horse");
  for(auto& str: c) std::cout << str << ' ';
  std::cout << '\n';

  // move ctor
  s21::set<std::string> d(std::move(a));
  for(auto& str: d) std::cout << str << ' ';
  std::cout << '\n';
  std::cout << "moved-from set is ";
  for(auto& str: a) std::cout << str << ' ';
  std::cout << '\n';

  // init list ctor
  s21::set<std::string> e = {"one", "two", "three", "five", "eight"};
  for(auto& str: e) std::cout << str << ' ';
  std::cout << '\n';

  return 0;
}
