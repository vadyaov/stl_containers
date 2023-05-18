#include <gtest/gtest.h>

#include <map>
#include <string>
#include <vector>

#include "../containers/map.h"

class TestMap : public ::testing::Test {
 public:
  typedef std::pair<int, int> ii_pair;
  typedef std::pair<int, std::string> istr_pair;
  typedef std::pair<std::string, int> stri_pair;

 protected:
  void SetUp() override {}

  s21::map<int, int> m1;
  s21::map<int, std::string> m2;
  s21::map<std::string, std::string> m3;
};

TEST_F(TestMap, default_ctor) {
  s21::map<std::string, int> map1;
  s21::map<char, double> map2;
  const s21::map<int, int> map3;
  const s21::map<std::string, std::string> map4;

  ASSERT_EQ(map1.size(), 0);
  ASSERT_EQ(map2.size(), 0);
  ASSERT_EQ(map3.size(), 0);
  ASSERT_EQ(map4.size(), 0);
}

TEST_F(TestMap, cpy_ctor) {
  std::map<int, int> mstd{ii_pair(1, 121), ii_pair(2, 122), ii_pair(3, 123),
                          ii_pair(4, 124)};
  s21::map<int, int> ms21{ii_pair(1, 121), ii_pair(2, 122), ii_pair(3, 123),
                          ii_pair(4, 124)};
  ASSERT_EQ(ms21.size(), mstd.size());

  s21::map<int, int> mcpy(ms21);

  ASSERT_EQ(ms21.size(), mcpy.size());

  auto j = mcpy.begin();
  for (auto i : ms21) {
    ASSERT_EQ(i, *j);
    ++j;
  }
}

TEST_F(TestMap, cpy_assignment) {
  const std::map<int, int> mstd{ii_pair(1, 121), ii_pair(2, 122),
                                ii_pair(3, 123), ii_pair(4, 124)};
  const s21::map<int, int> ms21{ii_pair(1, 121), ii_pair(2, 122),
                                ii_pair(3, 123), ii_pair(4, 124)};
  ASSERT_EQ(ms21.size(), mstd.size());

  const s21::map<int, int> mcpy = ms21;

  ASSERT_EQ(ms21.size(), mcpy.size());

  auto j = mcpy.begin();
  for (auto i : ms21) {
    ASSERT_EQ(i, *j);
    ++j;
  }
}

TEST_F(TestMap, move_ctor) {
  s21::map<int, std::string> m{istr_pair(1, "Ivan"), istr_pair(2, "Vladimir"),
                               istr_pair(3, "Evgeniy")};
  s21::map<int, std::string> mcpy{std::move(m)};
  ASSERT_EQ(mcpy.size(), 3);
  ASSERT_EQ(m.size(), 0);
  std::vector<std::string> expected = {"Ivan", "Vladimir", "Evgeniy"};
  int k = 0;
  for (auto i : mcpy) {
    ASSERT_EQ(mcpy.at(i), expected[k++]);
  }
}

TEST_F(TestMap, move_assignment) {
  s21::map<int, std::string> m{istr_pair(1, "Ivan"), istr_pair(2, "Vladimir"),
                               istr_pair(3, "Evgeniy")};
  s21::map<int, std::string> mcpy = std::move(m);
  ASSERT_EQ(mcpy.size(), 3);
  ASSERT_EQ(m.size(), 0);
  std::vector<std::string> expected = {"Ivan", "Vladimir", "Evgeniy"};
  int k = 0;
  for (auto i : mcpy) {
    ASSERT_EQ(mcpy.at(i), expected[k++]);
  }
}

TEST_F(TestMap, at) {
  s21::map<int, int> A(
      {ii_pair(1, 123), ii_pair(2, 345), ii_pair(2, 456), ii_pair(3, 567)});
  std::map<int, int> B(
      {ii_pair(1, 123), ii_pair(2, 345), ii_pair(2, 456), ii_pair(3, 567)});

  ASSERT_EQ(A.at(1), B.at(1));
  ASSERT_EQ(A.at(2), B.at(2));
  ASSERT_EQ(A.at(3), B.at(3));
  A.at(3) = 200;
  B.at(3) = 200;
  ASSERT_EQ(A.at(3), B.at(3));

  s21::map<double, char> AA({std::pair<double, char>(0.234567, 'a'),
                             std::pair<double, char>(9.5678, 'b'),
                             std::pair<double, char>(9.5678, 'c'),
                             std::pair<double, char>(3.45678, 'd')});

  std::map<double, char> BB({std::pair<double, char>(0.234567, 'a'),
                             std::pair<double, char>(9.5678, 'b'),
                             std::pair<double, char>(9.5678, 'c'),
                             std::pair<double, char>(3.45678, 'd')});

  ASSERT_EQ(AA.at(0.234567), BB.at(0.234567));
  ASSERT_EQ(AA.at(9.5678), BB.at(9.5678));
  ASSERT_EQ(AA.at(3.45678), BB.at(3.45678));

  AA.at(3.45678) = 'K';
  BB.at(3.45678) = 'K';
  ASSERT_EQ(AA.at(3.45678), BB.at(3.45678));
}

TEST_F(TestMap, insert) {
  s21::map<int, int> A(
      {ii_pair(1, 123), ii_pair(2, 345), ii_pair(2, 456), ii_pair(3, 567)});
  std::map<int, int> B(
      {ii_pair(1, 123), ii_pair(2, 345), ii_pair(2, 456), ii_pair(3, 567)});

  auto j = B.begin();
  auto insert_pair = A.insert(std::pair<int, int>(6, -1));
  auto og_insert_pair = B.insert(std::pair<int, int>(6, -1));
  EXPECT_EQ(*insert_pair.first, (*(og_insert_pair.first)).first);
  EXPECT_EQ(A.at(*insert_pair.first), (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);

  insert_pair = A.insert(std::pair<int, int>(-1, 6));
  og_insert_pair = B.insert(std::pair<int, int>(-1, 6));
  EXPECT_EQ(*insert_pair.first, (*(og_insert_pair.first)).first);
  EXPECT_EQ(A.at(*insert_pair.first), (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);

  insert_pair = A.insert(std::pair<int, int>(6, 666));
  og_insert_pair = B.insert(std::pair<int, int>(6, 666));
  EXPECT_EQ(*insert_pair.first, (*(og_insert_pair.first)).first);
  EXPECT_EQ(A.at(*insert_pair.first), (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);

  j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i);
    EXPECT_EQ((*j).second, A.at(i));
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST_F(TestMap, insert1) {
  s21::map<double, char> A({std::pair<double, char>(0.234567, 'a'),
                            std::pair<double, char>(9.5678, 'b'),
                            std::pair<double, char>(9.5678, 'c'),
                            std::pair<double, char>(3.45678, 'd')});
  std::map<double, char> B({std::pair<double, char>(0.234567, 'a'),
                            std::pair<double, char>(9.5678, 'b'),
                            std::pair<double, char>(9.5678, 'c'),
                            std::pair<double, char>(3.45678, 'd')});

  auto j = B.begin();
  A.insert(std::pair<double, char>(11.23456, 'M'));
  B.insert(std::pair<double, char>(11.23456, 'M'));

  A.insert(std::pair<double, char>(-456.45678, '!'));
  B.insert(std::pair<double, char>(-456.45678, '!'));

  A.insert(std::pair<double, char>(11.23456, 'M'));
  B.insert(std::pair<double, char>(11.23456, 'M'));

  A.insert(std::pair<double, char>(623849, '*'));
  B.insert(std::pair<double, char>(623849, '*'));
  j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i);
    EXPECT_EQ((*j).second, A.at(i));
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST_F(TestMap, s_wap) {
  s21::map<double, char> A({std::pair<double, char>(0.234567, 'a'),
                            std::pair<double, char>(9.5678, 'b'),
                            std::pair<double, char>(9.5678, 'c'),
                            std::pair<double, char>(3.45678, 'd')});
  auto acpy = A;
  s21::map<double, char> AA;
  std::map<double, char> B({std::pair<double, char>(0.234567, 'a'),
                            std::pair<double, char>(9.5678, 'b'),
                            std::pair<double, char>(9.5678, 'c'),
                            std::pair<double, char>(3.45678, 'd')});
  std::map<double, char> BB;

  AA.swap(A);
  BB.swap(B);
  auto j = BB.begin();
  for (auto i : AA) {
    EXPECT_EQ((*j).first, i);
    EXPECT_EQ((*j).second, acpy.at(i));
    j++;
  }
  EXPECT_EQ(AA.size(), BB.size());
}

TEST_F(TestMap, emplace) {
  s21::map<char, char> A(
      {std::pair<char, char>('a', '1'), std::pair<char, char>('b', '2'),
       std::pair<char, char>('b', '3'), std::pair<char, char>('c', '4'),
       std::pair<char, char>('d', '5')});
  std::map<int, int> B(
      {std::pair<char, char>('a', '1'), std::pair<char, char>('b', '2'),
       std::pair<char, char>('b', '3'), std::pair<char, char>('c', '4'),
       std::pair<char, char>('d', '5')});
  A.emplace(std::pair<char, char>('e', '!'));
  B.emplace(std::pair<char, char>('e', '!'));
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i);
    EXPECT_EQ((*j).second, A.at(i));
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST_F(TestMap, erase) {
  s21::map<double, char> A;
  std::map<double, char> B;
  for (int i = 0; i < 50; i++) {
    A.insert(std::pair<double, char>(i * 0.1234, char(i)));
    B.insert(std::pair<double, char>(i * 0.1234, char(i)));
  }
  EXPECT_EQ(A.at(5.0594), ')');
  EXPECT_EQ(A.at(5.0594), B.at(5.0594));
  EXPECT_EQ(A.at(4.4424), '$');
  EXPECT_EQ(A.at(4.4424), B.at(4.4424));
  EXPECT_EQ(A.at(5.9232), '0');
  EXPECT_EQ(A.at(5.9232), B.at(5.9232));
  EXPECT_EQ(A.size(), 50);
  EXPECT_EQ(A.size(), B.size());

  for (int i = 0; i < 10; i++) {
    A.erase(*A.begin());
    B.erase(B.begin());
  }
  EXPECT_EQ(A.size(), 40);
  EXPECT_EQ(A.size(), B.size());

  A.insert(std::pair<double, char>(61 * 0.1234, char(61)));
  B.insert(std::pair<double, char>(61 * 0.1234, char(61)));
  A.insert(std::pair<double, char>(62 * 0.1234, char(62)));
  B.insert(std::pair<double, char>(62 * 0.1234, char(62)));
  A.insert(std::pair<double, char>(63 * 0.1234, char(63)));
  B.insert(std::pair<double, char>(63 * 0.1234, char(63)));
  EXPECT_EQ(A.size(), 43);
  EXPECT_EQ(A.size(), B.size());

  for (int i = 0; i < 40; i++) {
    A.erase(*A.begin());
    B.erase(B.begin());
  }
  EXPECT_EQ(A.size(), 3);
  EXPECT_EQ(A.size(), B.size());
  A.clear();
  B.clear();
  EXPECT_EQ(A.size(), 0);
  EXPECT_EQ(A.size(), B.size());
}
