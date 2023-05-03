#include <map>
#include "../map.h"

template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, std::map<Key, Value> const& m)
{
   os << "{ ";
   for(auto const& p: m)
        os << '(' << p.first << ':' << p.second << ") ";
   return os << "}\n";
}

template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, s21::map<Key, Value> const& m)
{
   os << "{ ";
  typename RBTree<Key, Value>::const_iterator p;
   for(p = m.cbegin(); p != m.cend(); ++p)
        os << '(' << p.get_ptr()->key << ':' << p.get_ptr()->value << ") ";
   return os << "}\n";
}

int main() {

  s21::map<std::string, int> map1;
  map1["something"] = 69;
  map1["anything"] = 199;
  map1["that thing"] = 50;
  std::cout << "map1 = " << map1;

  const std::map<std::string, int> init {
    {"this", 100},
    {"can", 100},
    {"be", 100},
    {"const", 100},
  };
  std::cout << "\ninit = " << init;

  map1["something"] = 1; 
  std::cout << map1["something"] << std::endl;

  return 0;
}
