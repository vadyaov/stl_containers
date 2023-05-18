#include <gtest/gtest.h>

#include <stack>

#include "../containers/stack.h"

template <class T>
using stack = s21::stack<T>;

template <class T>
using og_stack = std::stack<T>;

using std::pair;

class StackTest : public ::testing::Test {};

TEST(StackTest, DefaultConstructor) {
  stack<int> A;
  const stack<int> AA;
  stack<char> C{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'};
  og_stack<char> C_OG({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'});

  stack<char> B;
  std::stack<char> B_OG;
  for (int i = 48; i < 100; i++) {
    B.push(char(i));
    B_OG.push(char(i));
  }

  for (int i = 48; i < 100; i++) {
    EXPECT_EQ(B.top(), B_OG.top());
    B.pop();
    B_OG.pop();
  }

  for (int i = 0; i < 9; i++) {
    EXPECT_EQ(C.top(), C_OG.top());
    C.pop();
    C_OG.pop();
  }
}

TEST(StackTest, Constructors) {
  stack<double> A;
  og_stack<double> B;
  for (int i = 0; i < 100; i++) {
    A.push(i * 0.2345);
    B.push(i * 0.2345);
  }
  stack<double> A_copy(A);
  stack<double> A_move(std::move(A));
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(A_copy.top(), A_move.top());
    A_copy.pop();
    A_move.pop();
  }
}

TEST(StackTest, InitializerConstructor) {
  stack<char> A({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'});
  og_stack<char> B({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'});
  while (!B.empty()) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
}

TEST(StackTest, AssignmentOperators) {
  stack<char> A({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'});
  stack<char> AA({0, 0, 0});
  AA = A;
  og_stack<char> B({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'});
  og_stack<char> BB({0, 0, 0});
  BB = B;
  while (!BB.empty()) {
    EXPECT_EQ(AA.top(), BB.top());
    AA.pop();
    BB.pop();
  }
}

TEST(StackTest, PushAndPop) {
  stack<double> A;
  og_stack<double> B;
  for (int i = 0; i < 100; i++) {
    A.push(8 * i + 3.0);
    B.push(8 * i + 3.0);
  }
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
}
TEST(StackTest, PushPop2) {
  stack<char> A;
  og_stack<char> B;
  for (int i = 0; i < 25; i++) {
    A.push(char(i));
    B.push(char(i));
  }
  for (int i = 0; i < 25; i++) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
}

TEST(StackTest, CapacityTest) {
  stack<double> A;
  og_stack<double> B;
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

TEST(StackTest, Swap) {
  stack<int> A({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  stack<int> B({11, 12, 13, 14, 15, 16, 17, 18, 19, 20});
  A.swap(B);
  EXPECT_EQ(A.top(), 20);
  EXPECT_EQ(B.top(), 10);
  for (int i = 10; i > 0; i--) {
    EXPECT_EQ(B.top(), i);
    EXPECT_EQ(A.top(), i + 10);
    B.pop();
    A.pop();
  }
}

TEST(StackTest, Emplace) {
  stack<int> A({1, 2, 3});
  A.emplace(4);
  A.emplace(5);
  A.emplace(6);

  og_stack<int> B({1, 2, 3});
  const int a = 4;
  B.push(a);
  for (int b = 5; b < 7; ++b) B.push(b);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(A.top(), B.top());
    A.pop();
    B.pop();
  }
}

TEST(StackTest, Other) {
  stack<int> A;
  og_stack<int> A_OG;
  for (int i = 0; i < 100; i++) {
    A.emplace(i);
    A_OG.emplace(i);
  }

  EXPECT_EQ(A.size(), A_OG.size());
  EXPECT_EQ(A.size(), 100);
  while (!A.empty()) {
    A.pop();
  }
  EXPECT_EQ(A.size(), 0);
}
