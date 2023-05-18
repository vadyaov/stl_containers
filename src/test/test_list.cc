#include <gtest/gtest.h>

#include <list>

#include "../containers/list.h"

struct B {
 public:
  int s;
  B() : s{-1} {}
  explicit B(int str) : s(std::move(str)) {}
  B(const B &o) : s(o.s) {}
  B(B &&o) : s(std::move(o.s)) {}
  B &operator=(const B &other) {
    s = other.s;
    return *this;
  }
  B &operator=(B &&other) {
    s = std::move(other.s);
    return *this;
  }
};

struct A {
  std::string s;
  A() : s("") {}

  explicit A(std::string str) : s(std::move(str)) {}
  A(const A &o) : s(o.s) {}
  A(A &&o) : s(std::move(o.s)) {}
  A &operator=(const A &other) {
    s = other.s;
    return *this;
  }
  A &operator=(A &&other) {
    s = std::move(other.s);
    return *this;
  }
};

class ListTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  s21::list<int> lst0_{1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::list<int> lst1_{9, 8, 7, 6, 5, 4, 3, 2, 1};
  s21::list<int> lst2_{1};
  s21::list<int> lst3_;
  s21::list<A> lst4_;
  s21::list<std::string> lst5_;
};

TEST_F(ListTest, default_ctor) {
  s21::list<int> s21_l;
  std::list<int> std_l;

  ASSERT_EQ(s21_l.size(), std_l.size());
  ASSERT_EQ(s21_l.empty(), true);
}

TEST_F(ListTest, explicit_ctor1) {
  s21::list<std::string> s21list(5, "hello");
  std::list<std::string> stdlist(5, "hello");

  ASSERT_EQ(s21list.size(), stdlist.size());

  for (auto &i : s21list) ASSERT_EQ(i, "hello");

  s21::list<A> s21_list(5, A("hello"));
  std::list<A> std_list(5, A("hello"));

  ASSERT_EQ(s21_list.size(), std_list.size());

  for (auto &i : s21_list) ASSERT_EQ(i.s, "hello");
}

TEST_F(ListTest, explicit_ctor2) {
  s21::list<B> s21list(10);
  std::list<B> stdlist(10);

  ASSERT_EQ(s21list.size(), stdlist.size());

  for (auto &i : s21list) ASSERT_EQ(i.s, -1);
}

TEST_F(ListTest, copy_ctor) {
  s21::list<int> other{lst0_};
  ASSERT_EQ(other.size(), lst0_.size());
  ASSERT_EQ(other.front(), lst0_.front());
  ASSERT_EQ(other.back(), lst0_.back());
}

TEST_F(ListTest, copy_assignment) {
  s21::list<int> other{0, 1, 2, 3, 4, 5, 6, 7, 8};
  s21::list<int> l;
  l = other;
  ASSERT_EQ(other.size(), l.size());
  ASSERT_EQ(other.front(), l.front());
  ASSERT_EQ(other.back(), l.back());
}

TEST_F(ListTest, move_ctor_assignment) {
  s21::list<int> l1{1, 2, 3, 4};
  s21::list<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8};

  ASSERT_EQ(l1.size(), 4);
  ASSERT_EQ(l2.size(), 8);

  s21::list<int> l3{std::move(l1)};

  ASSERT_EQ(l1.size(), 0);
  ASSERT_EQ(l1.empty(), true);
  ASSERT_EQ(l3.size(), 4);
  ASSERT_EQ(l3.front(), 1);
  ASSERT_EQ(l3.back(), 4);

  l2 = std::move(l3);

  ASSERT_EQ(l3.size(), 0);
  ASSERT_EQ(l3.empty(), true);
  ASSERT_EQ(l2.size(), 4);
  ASSERT_EQ(l2.front(), 1);
  ASSERT_EQ(l2.back(), 4);
}

TEST_F(ListTest, iterator_ctor) {
  s21::list<int> lst(++lst0_.begin(), lst0_.end());

  ASSERT_EQ(lst.size(), lst0_.size() - 1);
  ASSERT_EQ(lst.front(), 2);
  ASSERT_EQ(lst.back(), lst0_.back());
}

TEST_F(ListTest, assign) {
  lst0_.assign(lst1_.begin(), lst1_.end());

  ASSERT_EQ(lst0_.size(), lst1_.size());
  ASSERT_EQ(lst0_.front(), lst1_.front());
  ASSERT_EQ(lst0_.back(), lst1_.back());

  lst0_.assign(20, -1);
  ASSERT_EQ(lst0_.size(), 20);
  ASSERT_EQ(lst0_.front(), -1);
  ASSERT_EQ(lst0_.back(), -1);

  s21::list<std::string> lis;
  lis.assign({"one", "two", "three", "four"});

  ASSERT_EQ(lis.size(), 4);
  ASSERT_EQ(lis.front(), "one");
  ASSERT_EQ(lis.back(), "four");
}

TEST(method, insert) {
  std::list<int> l1;
  s21::list<int> l2;
  l1.insert(l1.begin(), 7);
  l2.insert(l2.begin(), 7);
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l1.empty(), l2.empty());
  EXPECT_EQ(l1.front(), l2.front());
  l1.push_front(2);
  l2.push_front(2);
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l1.front(), l2.front());
  l1.insert(l1.begin(), 7);
  l2.insert(l2.begin(), 7);
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l1.front(), l2.front());
  l1.insert(l1.end(), 7);
  l2.insert(l2.end(), 7);
  auto i2 = l2.begin();
  for (int &i : l1) {
    EXPECT_EQ(i, *i2);
    i2++;
  }
}

TEST(method, insert_1) {
  std::list<int> l1;
  s21::list<int> l2;
  l1.insert(l1.end(), 7);
  l2.insert(l2.end(), 7);
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l1.empty(), l2.empty());
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  l1.clear();
  l2.clear();
  EXPECT_EQ(l1.empty(), l2.empty());
  EXPECT_EQ(l1.size(), l2.size());
  l1.insert(l1.end(), 7);
  l2.insert(l2.end(), 7);
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l1.empty(), l2.empty());
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
}

TEST(method, insert_2) {
  std::list<std::string> l1;
  s21::list<std::string> l2;
  std::string val{"hi"};
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l1.empty(), l2.empty());
  l1.insert(l1.begin(), val);
  l2.insert(l2.begin(), val);
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  val = "";
  l1.insert(l1.begin(), val);
  l2.insert(l2.begin(), val);
  l1.insert(l1.cbegin(), "ddddddddddddddddddhi");
  l2.insert(l2.begin(), "ddddddddddddddddddhi");
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
}

TEST(method, insert_3) {
  std::list<int> l1{1, 2, 3, 4, 5, 6, 7};
  s21::list<int> l2{1, 2, 3, 4, 5, 6, 7};
  auto it1 = ++(l1.cbegin());
  s21::list<int>::iterator it2 = ++(l2.begin());
  it1++;
  ++it2;
  l1.insert(it1, 200);
  l2.insert(it2, 200);
  s21::list<int>::iterator j = l2.begin();
  for (auto i : l1) {
    EXPECT_EQ(*j, i);
    ++j;
  }
}

TEST_F(ListTest, insert_4) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  s21::list<int>::iterator it = lst.begin();
  int value = -1;
  lst.insert(it, 5, value);

  ASSERT_EQ(lst.size(), 10);
  ASSERT_EQ(lst.front(), -1);
  ASSERT_EQ(lst.back(), 5);

  s21::list<int> lst1 = {-1, -2, -3, -4, -5};
  lst1.insert(lst1.end(), lst.begin(), lst.end());

  ASSERT_EQ(lst1.size(), 15);
  ASSERT_EQ(lst1.front(), -1);
  ASSERT_EQ(lst1.back(), 5);

  std::initializer_list<int> ilist = {10, 20, 30};
  lst1.insert(lst1.begin(), ilist);

  ASSERT_EQ(lst1.size(), 18);
  ASSERT_EQ(lst1.front(), 10);
  ASSERT_EQ(lst1.back(), 5);
}

TEST(method, erase_1) {
  std::list<std::string> l1{"hi", "so"};
  s21::list<std::string> l2{"hi", "so"};
  l1.erase(l1.begin());
  l2.erase(l2.begin());
  EXPECT_EQ(*l1.begin(), *l2.begin());
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  l1.erase(l1.begin());
  l2.erase(l2.begin());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(method, erase_2) {
  s21::list<int> a;
  std::list<s21::list<int>> l1{a, a, a, a, a};
  s21::list<s21::list<int>> l2{a, a, a, a, a};
  EXPECT_EQ(l1.size(), l2.size());
  l1.erase(l1.begin());
  l2.erase(l2.begin());
  l1.erase(l1.begin());
  l2.erase(l2.begin());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(method, push_back) {
  s21::list<int> l1;
  s21::list<int> l2(l1);
  std::list<int> test{2, 5, 6, 7, 8, 1, 0, 3};
  EXPECT_EQ(0, l2.size());
  l1.push_back(2);
  l1.push_back(5);
  l1.push_back(6);
  l1.push_back(7);
  l1.push_back(8);
  l1.push_back(1);
  l1.push_back(0);
  l1.push_back(3);
  s21::list<int>::iterator j = l1.begin();
  for (auto i : test) {
    EXPECT_EQ(*j, i);
    ++j;
  }
}

TEST(method, pop_back) {
  s21::list<int> l1;
  s21::list<int> l2{2, 5, 6, 7, 9, 0, 1, 66};
  std::list<int> test{2, 5, 6, 7, 9};
  EXPECT_EQ(*l2.begin(), *test.begin());
  l2.pop_back();
  l2.pop_back();
  l2.pop_back();
  s21::list<int>::iterator j = l2.begin();
  for (auto i : test) {
    EXPECT_EQ(*j, i);
    ++j;
  }
  s21::list<int>::const_iterator j1 = ++(l2.cbegin());
  auto j2 = ++(test.cbegin());
  EXPECT_EQ(*j1, *j2);
}

TEST(method, push_front) {
  s21::list<int> l1;
  s21::list<int> l2(std::move(l1));
  EXPECT_EQ(0, l2.size());
  l2.push_front(2);
  EXPECT_EQ(1, l2.size());
  EXPECT_EQ(2, l2.front());
  EXPECT_EQ(2, l2.back());
  l2.erase(l2.begin());
  EXPECT_EQ(0, l2.size());
  l2.push_front(5);
  EXPECT_EQ(1, l2.size());
  EXPECT_EQ(5, l2.front());
  EXPECT_EQ(5, l2.back());
}

TEST(method, pop_front) {
  s21::list<int> l1{2, 3, 4, 5, 3, 34, 5, 5};
  std::list<int> l2{3, 34, 5, 5};
  l1.pop_front();
  l1.pop_front();
  l1.pop_front();
  l1.pop_front();
  s21::list<int>::iterator j = l1.begin();
  for (auto i : l2) EXPECT_EQ(*j++, i);

  l1.pop_front();
  l1.pop_front();
  l1.pop_front();
  l1.pop_front();
  EXPECT_EQ(0, l1.size());
}

TEST(method, emplace_back) {
  s21::list<int> l1;
  std::list<int> l2;
  l1.emplace_back(1);
  l1.emplace_back(2);
  l1.emplace_back(3);

  l2.emplace_back(1);
  l2.emplace_back(2);
  l2.emplace_back(3);
  auto j = l1.begin();
  for (auto i : l2) EXPECT_EQ(*j++, i);
}

TEST(method, emplace_back1) {
  s21::list<int> l1(0);
  std::list<int> l2(0);
  l1.emplace_back(1);
  l1.emplace_back(2);
  l1.emplace_back(3);

  l2.emplace_back(1);
  l2.emplace_back(2);
  l2.emplace_back(3);
  auto j = l1.begin();
  for (auto i : l2) EXPECT_EQ(*j++, i);
}

TEST(method, emplace_back2) {
  s21::list<int> l1{1, 2, 3, 4, 5, 6, 7};
  std::list<int> l2{1, 2, 3, 4, 5, 6, 7};
  l1.emplace_back(1);
  l1.emplace_back(2);
  l1.emplace_back(3);

  l2.emplace_back(1);
  l2.emplace_back(2);
  l2.emplace_back(3);
  auto j = l1.begin();
  for (auto i : l2) EXPECT_EQ(*j++, i);
}

TEST(method, emplace_front) {
  s21::list<int> l1;
  std::list<int> l2;
  l1.emplace_front(1);
  l1.emplace_front(2);
  l1.emplace_front(3);

  l2.emplace_front(1);
  l2.emplace_front(2);
  l2.emplace_front(3);
  auto j = l1.begin();
  for (auto i : l2) EXPECT_EQ(*j++, i);
}

TEST(method, emplace_front1) {
  s21::list<int> l1(0);
  std::list<int> l2(0);
  l1.emplace_front(1);
  l1.emplace_front(2);
  l1.emplace_front(3);

  l2.emplace_front(1);
  l2.emplace_front(2);
  l2.emplace_front(3);
  auto j = l1.begin();
  EXPECT_EQ((j == l1.begin()), true);
  for (auto i : l2) EXPECT_EQ(*j++, i);
}

TEST(method, emplace_front2) {
  s21::list<int> l1{1, 2, 3, 4, 5, 6};
  std::list<int> l2{1, 2, 3, 4, 5, 6};
  l1.emplace_front(1);
  l1.emplace_front(2);
  l1.emplace_front(3);

  l2.emplace_front(1);
  l2.emplace_front(2);
  l2.emplace_front(3);
  auto j = l1.begin();
  for (auto i : l2) EXPECT_EQ(*j++, i);
}

TEST(method, swap_) {
  s21::list<int> l1;
  s21::list<int> l2;
  s21::list<int> l3{7, 3, 2};
  s21::list<int> l4{9, 4, 5};
  l1.swap(l2);
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(0, l2.size());
  l1.push_front(2);
  l1.push_front(3);
  l1.push_front(7);
  l2.push_front(5);
  l2.push_front(4);
  l2.push_front(9);
  s21::list<int>::iterator j = l1.begin();
  for (auto i : l3) {
    EXPECT_EQ(*j, i);
    ++j;
  }
  s21::list<int>::iterator j1 = l2.begin();
  for (auto i : l4) {
    EXPECT_EQ(*j1, i);
    ++j1;
  }
}

TEST(method, merge_1) {
  s21::list<int> l1;
  s21::list<int> l2;
  l1.merge(std::move(l2));
  EXPECT_EQ(0, l1.size());
  EXPECT_EQ(0, l2.size());
  s21::list<int> l3{1, 2, 3, 5, 6, 7};
  s21::list<int> l4{1, 2, 3, 5, 6, 7};
  std::list<int> test1{1, 2, 3, 5, 6, 7};
  std::list<int> test2{1, 2, 3, 5, 6, 7};
  l3.merge(std::move(l4));
  test1.merge(test2);
  s21::list<int>::iterator j = l3.begin();
  for (auto i : test1) {
    EXPECT_EQ(*j, i);
    ++j;
  }
}

TEST(method, merge_2) {
  s21::list<int> l3{0, 0, 0};
  s21::list<int> l4{-1, -1, -1, -1};
  std::list<int> test1{0, 0, 0};
  std::list<int> test2{-1, -1, -1, -1};
  l3.merge(std::move(l4));
  test1.merge(test2);
  s21::list<int>::iterator j = l3.begin();
  for (auto i : test1) {
    EXPECT_EQ(*j, i);
    ++j;
  }
}

TEST(method, splice_1) {
  s21::list<int> l1;
  s21::list<int> l2{-1, 1, 2, 3, 5, 7};
  std::list<int> test1;
  std::list<int> test2{-1, 1, 2, 3, 5, 7};
  l1.splice(l1.cbegin(), std::move(l2));
  test1.splice(test1.cbegin(), test2);
  s21::list<int>::iterator j = l1.begin();
  for (auto i : test1) {
    EXPECT_EQ(*j, i);
    ++j;
  }
  s21::list<int> l3{-1, 1, 2, 3, 5, 7};
  s21::list<int> l4(l3);
  s21::list<int>::iterator j1 = l3.begin();
  for (auto i = l4.begin(); i != l4.end(); ++i) {
    EXPECT_EQ(*j1, *i);
    ++j1;
  }
}

TEST(method, splice_2) {
  s21::list<int> l1{4, 7, 8, 9, 10};
  s21::list<int> l2{-1, 1, 2, 3, 5, 7};
  std::list<int> test1{4, 7, 8, 9, 10};
  std::list<int> test2{-1, 1, 2, 3, 5, 7};
  l1.splice(l1.cend(), std::move(l2));
  test1.splice(test1.cend(), test2);
  s21::list<int>::iterator j = l1.begin();
  for (auto i : test1) {
    EXPECT_EQ(*j, i);
    ++j;
  }
}

TEST(method, reverse_1) {
  s21::list<int> l1{1, 2, 3, 5, 6, 10};
  std::list<int> test1{10, 6, 5, 3, 2, 1};
  l1.reverse();
  s21::list<int>::iterator j = l1.begin();
  for (auto i : test1) {
    EXPECT_EQ(*j, i);
    ++j;
  }
}

TEST(method, reverse_2) {
  s21::list<int> l1;
  std::list<int> test1{7, 5, 3};
  l1.reverse();
  EXPECT_EQ(0, l1.size());
  l1.push_front(3);
  l1.push_front(5);
  l1.push_front(7);
  l1.reverse();
  l1.reverse();
  s21::list<int>::iterator j = l1.begin();
  for (auto i : test1) {
    EXPECT_EQ(*j, i);
    ++j;
  }
}

TEST(method, unique) {
  s21::list<int> l1;
  l1.unique();
  EXPECT_EQ(0, l1.size());
  s21::list<int> l2{1, 1, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 7, 7, 8};
  std::list<int> test1{1, 2, 3, 4, 5, 7, 8};
  l2.unique();
  EXPECT_EQ(7, l2.size());
  s21::list<int>::iterator j = l2.begin();
  for (auto i : test1) {
    EXPECT_EQ(*j, i);
    ++j;
  }
  s21::list<int> l3{0, 0, 0, 0, 0, 0, 0};
  l3.unique();
  EXPECT_EQ(1, l3.size());
  std::list<int> test2{0};
  s21::list<int>::iterator j1 = l3.begin();
  for (auto i : test2) {
    EXPECT_EQ(*j1, i);
    ++j1;
  }
}

TEST(method, sort_1) {
  s21::list<int> l1;
  l1.sort();
  EXPECT_EQ(0, l1.size());
  s21::list<int> l2{1};
  l1.sort();
  EXPECT_EQ(1, l2.size());
  s21::list<int> l3{1, -123, 3, 0, 5, 1};
  std::list<int> test1{-123, 0, 1, 1, 3, 5};
  l3.sort();
  s21::list<int>::iterator j1 = l3.begin();
  for (auto i : test1) {
    EXPECT_EQ(*j1, i);
    ++j1;
  }
}

TEST(method, sort_2) {
  std::list<int> l1{2, 134, 6, -1, 9, 0, 23, 45, 1, -11, 3, 12};
  s21::list<int> l2{2, 134, 6, -1, 9, 0, 23, 45, 1, -11, 3, 12};
  l1.sort();
  l2.sort();
  EXPECT_EQ(*l1.begin(), *l2.begin());
  auto i2 = l2.begin();
  for (int &i : l1) {
    EXPECT_EQ(i, *i2);
    ++i2;
  }
}

TEST(method, sort_3) {
  std::list<int> l1{1, 1, 2, 3};
  s21::list<int> l2{1, 1, 2, 3};
  l1.sort();
  l2.sort();
  EXPECT_EQ(*l1.begin(), *l2.begin());
  l2.push_back(4);
  l1.push_back(4);
  auto i2 = l2.begin();
  for (int i : l1) {
    EXPECT_EQ(i, *i2);
    ++i2;
  }
}

TEST(method, sort_4) {
  s21::list<int> l1;
  std::list<int> l2{1, 1};
  l1.push_back(1);
  l1.push_back(1);
  l1.sort();
  auto i1 = l1.begin();
  for (int i : l2) {
    EXPECT_EQ(i, *i1);
    ++i1;
  }
  l1.push_back(1);
  l1.push_back(1);
  EXPECT_EQ(4, l1.size());
}

TEST_F(ListTest, remove) {
  s21::list<int> lst{lst0_};
  lst.remove(1);
  lst.remove(9);

  ASSERT_EQ(lst.size(), 7);
  ASSERT_EQ(lst.front(), 2);
  ASSERT_EQ(lst.back(), 8);

  lst.remove(0);

  ASSERT_EQ(lst.size(), 7);
  ASSERT_EQ(lst.front(), 2);
  ASSERT_EQ(lst.back(), 8);
}
