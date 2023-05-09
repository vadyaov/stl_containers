#include <gtest/gtest.h>
#include <list>
#include "../containers/list.h"

struct B {
  public:
    int s;
    B() : s{-1} {
    }
    explicit B(int str) : s(std::move(str)) {
    }
    B(const B &o) : s(o.s) {
    }
    B(B &&o) : s(std::move(o.s)) {
    }
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
    A() : s("") {
    }

    explicit A(std::string str) : s(std::move(str)) {
    }
    A(const A &o) : s(o.s) {
    }
    A(A &&o) : s(std::move(o.s)) {
    }
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
    void SetUp() override {
    }

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

  for (auto &i : s21list)
    ASSERT_EQ(i, "hello");

  s21::list<A> s21_list(5, A("hello"));
  std::list<A> std_list(5, A("hello"));

  ASSERT_EQ(s21_list.size(), std_list.size());

  for (auto &i : s21_list)
    ASSERT_EQ(i.s, "hello");
}

TEST_F(ListTest, explicit_ctor2) {
  s21::list<B> s21list(10);
  std::list<B> stdlist(10);

  ASSERT_EQ(s21list.size(), stdlist.size());
  
  for (auto &i : s21list)
    ASSERT_EQ(i.s, -1);
}

TEST_F(ListTest, copy_ctor) {
  s21::list<int> other {lst0_};
  ASSERT_EQ(other.size(), lst0_.size());
  ASSERT_EQ(other.front(), lst0_.front());
  ASSERT_EQ(other.back(), lst0_.back());
}

TEST_F(ListTest, copy_assignment) {
  s21::list<int> other {0, 1, 2, 3, 4, 5, 6, 7, 8};
  s21::list<int> l;
  l = other;
  ASSERT_EQ(other.size(), l.size());
  ASSERT_EQ(other.front(), l.front());
  ASSERT_EQ(other.back(), l.back());
}

TEST_F(ListTest, move_ctor_assignment) {
  s21::list<int> l1 {1, 2, 3, 4};
  s21::list<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8};

  ASSERT_EQ(l1.size(), 4);
  ASSERT_EQ(l2.size(), 8);

  s21::list<int> l3 {std::move(l1)};

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
  s21::list<int> lst (++lst0_.begin(), lst0_.end());
  
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

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
