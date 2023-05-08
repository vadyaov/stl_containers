#include <vector>
#include <string>
#include <iostream>
#include "../containers/vector.h"

using std::string;

int main() {
  std::vector<string> v(3, "hello"); 
  for (int i = 0; i < 3; ++i)
    std::cout << v[i] << " ";
  std::cout << v.size() << " " << v.capacity() << "\n";

  std::vector<string> vcpy{"one", "two", "tree", "four"};
  vcpy = v;
  for (int i = 0; i < vcpy.size(); ++i)
    std::cout << vcpy[i] << " ";
  std::cout << vcpy.size() << " " << vcpy.capacity() << "\n";

  /* v.insert(v.begin() + 10, "one"); */
  /* for (auto i : v) */
  /*   std::cout << " " << i; */
  /* std::cout << std::endl; */

  /* v.insert(v.begin(), "two"); */

  /* for (auto i : v) */
  /*   std::cout << " " << i; */
  /* std::cout << std::endl; */

  /* v.insert(v.begin(), "tree"); */
  /* for (auto i : v) */
  /*   std::cout << " " << i; */
  /* std::cout << std::endl; */

  /* v.insert(v.begin(), "four"); */
  /* for (auto i : v) */
  /*   std::cout << " " << i; */
  /* std::cout << std::endl; */

  return 0;
}

