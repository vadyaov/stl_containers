#include <gtest/gtest.h>
#include <queue>

#include "../containers/queue.h"

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

class QueueTest: public ::testing::Test {
  protected:
    void SetUp() override {
    }

    s21::queue<int> q0 {};
    s21::queue<int> q1 {1, 2, 3, 4, 5};
    s21::queue<std::string> q2 {"one", "two", "three"};
    s21::queue<A> q3 {A("hello"), A("world")};
};

bool operator==(const A &lhs, const A &rhs) {
  return rhs.s == lhs.s;
}

TEST_F(QueueTest, default_ctor) {
  ASSERT_EQ(q0.size(), 0);
  ASSERT_EQ(q0.empty(), true);
}

TEST_F(QueueTest, copy_ctor) {
  s21::queue<int> q {q0};

  ASSERT_EQ(q.size(), 0);
  ASSERT_EQ(q.empty(), true);

  s21::queue<int> qq {q1};

  ASSERT_EQ(qq.size(), q1.size());
  ASSERT_EQ(qq.empty(), false);
  ASSERT_EQ(qq.front(), q1.front());
  ASSERT_EQ(qq.back(), q1.back());
}

TEST_F(QueueTest, copy_assignment) {
  s21::queue<int> q = q0;

  ASSERT_EQ(q.size(), 0);
  ASSERT_EQ(q.empty(), true);

  s21::queue<int> qq {q1};

  ASSERT_EQ(qq.size(), q1.size());
  ASSERT_EQ(qq.empty(), false);
  ASSERT_EQ(qq.front(), q1.front());
  ASSERT_EQ(qq.back(), q1.back());
}

TEST_F(QueueTest, move_assignment) {
  const s21::queue<int> q {q1};

  size_t sz = q1.size();
  int fr = q1.front();
  int bk = q1.back();
  s21::queue<int> qq  = std::move(q1);

  ASSERT_EQ(q1.size(), 0);
  ASSERT_EQ(q1.empty(), true);

  ASSERT_EQ(qq.size(), sz);
  ASSERT_EQ(qq.empty(), false);
  ASSERT_EQ(qq.front(), fr);
  ASSERT_EQ(qq.back(), bk);
}

TEST_F(QueueTest, ilist_ctor) {
  s21::queue<std::string> s21_q {"one", "two", "three", "four"};

  ASSERT_EQ(s21_q.size(), 4);
  ASSERT_EQ(s21_q.front(), "one");
  ASSERT_EQ(s21_q.back(), "four");
}

TEST_F(QueueTest, list_ctor) {
  s21::list<int> lst {1, 2, 3};
  s21::queue<int> que {lst};

  ASSERT_EQ(lst.size(), que.size());
  ASSERT_EQ(1, que.front());
  ASSERT_EQ(3, que.back());
}

TEST_F(QueueTest, move_ctor) {
  s21::queue<int> other {-1, -2, -3, -4};
  s21::queue<int> q {std::move(other)};

  ASSERT_EQ(q.size(), 4);
  ASSERT_EQ(q.front(), -1);
  ASSERT_EQ(q.back(), -4);
  ASSERT_EQ(other.size(), 0);
  ASSERT_EQ(other.empty(), true);
}

TEST_F(QueueTest, push) {
  std::string str = "boba";
  q2.push(str);
  q2.push("zero");
  q3.push(A("!"));

  ASSERT_EQ(q2.size(), 5);
  ASSERT_EQ(q2.front(), "one");
  ASSERT_EQ(q2.back(), "zero");

  ASSERT_EQ(q3.size(), 3);
  ASSERT_EQ(q3.front(), A("hello"));
  ASSERT_EQ(q3.back(), A("!"));
}

TEST_F(QueueTest, const_queue) {
  const s21::queue<int> q { 11, 12, 13, 14, 15};

  ASSERT_EQ(q.size(), 5);
  ASSERT_EQ(q.front(), 11);
  ASSERT_EQ(q.back(), 15);
}

TEST_F(QueueTest, Emplace) {
      s21::queue<char> A;
      std::queue<char> B;
      for (int i = 0; i < 666; i++) {
        A.emplace(i);
        B.emplace(i);
      }
      for (int i = 0; i < 666; i++) {
        EXPECT_EQ(A.front(), B.front());
        EXPECT_EQ(A.back(), B.back());
        A.pop();
        B.pop();
      }
}

TEST_F(QueueTest, CapacityTest) {
    s21::queue<double> A;
    std::queue<double> B;
    EXPECT_EQ(A.size(), B.size());
    EXPECT_EQ(A.empty(), B.empty());
    for (int i = 0; i < 666; i++) {
        A.push(i * 0.12345);
        B.push(i * 0.12345);
    }
    EXPECT_EQ(A.size(), B.size());
    EXPECT_EQ(A.empty(), B.empty());
    for (int i = 0; i < 66; i++) {
        A.pop();
        B.pop();
    }

    EXPECT_EQ(A.size(), B.size());
    EXPECT_EQ(A.empty(), B.empty());
}

TEST_F(QueueTest, Swap) {
    s21::queue<double> A;
    s21::queue<double> B;
    std::queue<double> AA;
    std::queue<double> BB;
    for (int i = 0; i < 666; i++) {
        A.push(i * 0.23456 + i);
        B.push(i * 0.98764 + i);

        AA.push(i * 0.23456 + i);
        BB.push(i * 0.98764 + i);
    }

    A.swap(B);
    AA.swap(BB);
    EXPECT_EQ(A.size(), AA.size());
    EXPECT_EQ(A.size(), 666);
    while (!A.empty()) {
        EXPECT_EQ(A.back(), AA.back());
        A.pop();
        AA.pop();
    }
    EXPECT_EQ(A.size(), 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
