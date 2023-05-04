#include <map>
#include "../map.h"

template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, s21::map<Key, Value> const& m)
{
   os << "{ ";
   typename s21::map<Key, Value>::const_iterator it;
   for(it = m.begin(); it != m.end(); ++it)
        os << '(' << it.get_ptr()->key << ':' << it.get_ptr()->value << ") ";
   return os << "}\n";
}

int main() {

  s21::map<std::string, int> map1;
  map1["something"] = 69;
  map1["anything"] = 199;
  map1["that thing"] = 50;
  std::cout << "map1 = " << map1;

  auto iter = map1.begin();
  std::cout << "map1 = " << map1;

  return 0;
}
