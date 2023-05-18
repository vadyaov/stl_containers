#include <set>

#include "../containers_plus/multiset.h"
#include "gtest/gtest.h"

TEST(method, constructor) {
  s21::multiset<int> a{1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
  s21::multiset<int> b(a);
  s21::multiset<int> c{1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
  auto it1 = b.begin();
  EXPECT_EQ(b.size(), c.size());
  for (auto it = c.cbegin(); it != c.cend(); ++it) {
    EXPECT_EQ(*it, *it1);
    ++it1;
  }
  s21::multiset<int> d;
  d = a;
  auto it2 = d.begin();
  for (auto it = c.cbegin(); it != c.cend(); ++it) {
    EXPECT_EQ(*it, *it2);
    it2++;
  }
}

TEST(method, constructor2) {
  s21::multiset<int> a{1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
  s21::multiset<int> b(std::move(a));
  s21::multiset<int> c{1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
  auto it1 = b.begin();
  EXPECT_EQ(b.size(), c.size());
  for (auto it = c.cbegin(); it != c.cend(); ++it) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
  s21::multiset<int> d;
  d = b;
  auto it2 = d.begin();
  for (auto it = c.cbegin(); it != c.cend(); ++it) {
    EXPECT_EQ(*it, *it2);
    it2++;
  }
}

TEST(method, clear) {
  s21::multiset<int> a;
  std::multiset<int> b;
  a.clear();
  b.clear();
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
  a.insert(1);
  a.insert(1);
  a.insert(1);
  b.insert(1);
  b.insert(1);
  b.insert(1);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(*a.begin(), *b.begin());
  EXPECT_EQ(*a.cbegin(), *b.cbegin());
}

TEST(method, insert0) {
  s21::multiset<std::string> a{"clean", "add", "add", "is", "cat", "fox"};
  std::multiset<std::string> b{"clean", "add", "add", "is", "cat", "fox"};
  auto it1 = b.begin();
  for (auto it = a.cbegin(); it != a.cend(); ++it) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
}

TEST(method, insert1) {
  s21::multiset<double> a{1.223, 32.234, 3.2, 1.2, 34.123, 3.908, 4.23};
  std::multiset<double> b{1.223, 32.234, 3.2, 1.2, 34.123, 3.908, 4.23};
  auto it1 = b.begin();
  for (auto it = a.cbegin(); it != a.cend(); ++it) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
  a.insert(123.3);
  b.insert(123.3);
  auto it2 = b.begin();
  for (auto it = a.cbegin(); it != a.cend(); ++it) {
    EXPECT_EQ(*it, *it2);
    it2++;
  }
}

TEST(method, insert2) {
  std::multiset<int> d;
  s21::multiset<std::multiset<int>> a1{d, d};
  std::multiset<std::multiset<int>> b1{d, d};
  auto it2 = a1.begin();
  for (auto it = b1.cbegin(); it != b1.cend(); ++it) {
    EXPECT_EQ(*it, *it2);
    it2++;
  }
}

TEST(method, emplace) {
  s21::multiset<int> a;
  std::multiset<int> b;
  a.emplace(1);
  a.emplace(1);
  a.emplace(2);
  a.emplace(3);
  a.emplace(4);
  a.emplace(5);

  b.emplace(1);
  b.emplace(1);
  b.emplace(2);
  b.emplace(3);
  b.emplace(4);
  b.emplace(5);
  EXPECT_EQ(a.size(), b.size());
  auto it1 = a.begin();
  for (auto it = b.begin(); it != b.end(); ++it) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
}

TEST(method, emplace1) {
  s21::multiset<int> a{1, 2, 3, 40, 60};
  std::multiset<int> b{1, 2, 3, 40, 60};
  a.emplace(1);
  a.emplace(1);
  a.emplace(2);
  a.emplace(3);
  a.emplace(4);
  a.emplace(5);

  b.emplace(1);
  b.emplace(1);
  b.emplace(2);
  b.emplace(3);
  b.emplace(4);
  b.emplace(5);
  EXPECT_EQ(a.size(), b.size());
  auto it1 = a.begin();
  for (auto it = b.begin(); it != b.end(); ++it) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
}

TEST(method, emplace3) {
  s21::multiset<int> a{1, 2, 3, 40, 60};
  std::multiset<int> b{1, 2, 3, 40, 60};
  a.emplace(1, 1, 2, 3, 4, 5);
  b.emplace(1);
  b.emplace(1);
  b.emplace(2);
  b.emplace(3);
  b.emplace(4);
  b.emplace(5);
  EXPECT_EQ(a.size(), b.size());
  auto it1 = a.begin();
  for (auto it = b.begin(); it != b.end(); ++it) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
}

TEST(method, emplace4) {
  s21::multiset<int> a;
  std::multiset<int> b;
  a.emplace(1, 1, 2, 3, 4, 5);
  b.emplace(1);
  b.emplace(1);
  b.emplace(2);
  b.emplace(3);
  b.emplace(4);
  b.emplace(5);
  EXPECT_EQ(a.size(), b.size());
  auto it1 = a.begin();
  for (auto it = b.begin(); it != b.end(); ++it) {
    EXPECT_EQ(*it, *it1);
    it1++;
  }
}

TEST(method, erase_) {
  s21::multiset<int> a;
  std::multiset<int> b;
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
  s21::multiset<int> c{1, 2, 3, 4, 4, 4, 4, 4};
  a = c;
  EXPECT_EQ(a.size(), 8);
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(*a.begin(), 1);
  EXPECT_EQ(*a.cbegin(), 1);
}

TEST(method, swap__) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  s21::multiset<int> b{1, 2, 2};
  std::multiset<int> c{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  std::multiset<int> d{1, 2, 2};
  a.swap(b);
  c.swap(d);
  auto it1 = a.begin();
  for (auto it = c.begin(); it != c.end(); ++it) {
    EXPECT_EQ(*it, *it1);
    ++it1;
  }
  auto it2 = b.cbegin();
  for (auto it3 = d.begin(); it3 != d.end(); ++it3) {
    EXPECT_EQ(*it2, *it3);
    ++it2;
  }
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(b.size(), d.size());
}

TEST(method, Find_) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  std::multiset<int> c{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  EXPECT_EQ(*a.find(2), *c.find(2));
  EXPECT_EQ(a.find(10).get_ptr(), nullptr);
  EXPECT_EQ(*a.find(5), *c.find(5));
}

TEST(method, equal_range) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  std::multiset<int> c{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5};
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> b0 =
      a.equal_range(2);
  std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> d0 =
      c.equal_range(2);
  EXPECT_EQ(*b0.first, *d0.first);
  EXPECT_EQ(*b0.second, *d0.second);
  while (b0.first != b0.second && d0.first != d0.second) {
    EXPECT_EQ(*b0.first, *d0.first);
    b0.first++;
    d0.first++;
  }
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> b1 =
      a.equal_range(4);
  std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> d1 =
      c.equal_range(4);
  EXPECT_EQ(*b1.first, *d1.first);
  EXPECT_EQ(*b1.second, *d1.second);
  while (b1.first != b1.second && d1.first != d1.second) {
    EXPECT_EQ(*b1.first, *d1.first);
    b1.first++;
    d1.first++;
  }
}

TEST(method, count) {
  s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5};
  std::multiset<int> c{1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5};
  a.count(1);
  EXPECT_EQ(a.count(1), c.count(1));
  EXPECT_EQ(a.count(2), c.count(2));
  EXPECT_EQ(a.count(3), c.count(3));
  EXPECT_EQ(a.count(4), c.count(4));
  EXPECT_EQ(a.count(5), c.count(5));
}

TEST(method, count2) {
  const s21::multiset<int> a{1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5};
  const std::multiset<int> c{1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5};
  a.count(1);
  EXPECT_EQ(a.count(1), c.count(1));
  EXPECT_EQ(a.count(2), c.count(2));
  EXPECT_EQ(a.count(3), c.count(3));
  EXPECT_EQ(a.count(4), c.count(4));
  EXPECT_EQ(a.count(5), c.count(5));
}
