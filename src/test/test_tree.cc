#include <gtest/gtest.h>
#include <random>
#include "../containers/rb_tree.h"

int GetRandomValue() {
  int low = 0, up = 50;
  static std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(low, up);
  return distribution(generator);
}

class TreeTest : public ::testing::Test {
  public:
    typedef std::pair<int, int> ii_pair;
    typedef std::pair<int, std::string> istr_pair;
    typedef std::pair<std::string, int> stri_pair;
  protected:
    void SetUp() override {
    }

    RBTree<int, int> t0; // default int,int tree
    RBTree<int, std::string> t1; // default int,string tree
    RBTree<std::string, int> t2; // default string,int tree

    RBTree<int, std::string> t3 {std::pair<int, std::string>(1, "one"),
                                 std::pair<int, std::string>(2, "two"),
                                 std::pair<int, std::string>(3, "three")
                                };
};

TEST_F(TreeTest, def_ctor) {
  ASSERT_EQ(t0.size(), 0);
  ASSERT_EQ(t1.size(), 0);
  ASSERT_EQ(t2.size(), 0);
}

TEST_F(TreeTest, cpy_ctor) {
  
  t0.insert(ii_pair(0, 123));
  // not unique
  t0.insert(ii_pair(0, 123));
  t0.insert(ii_pair(1, -11));
  t0.insert(ii_pair(2, 10));
  t0.insert(ii_pair(4, 1));
  t0.insert(ii_pair(-10, 18));
  t0.insert(ii_pair(12, 18));
  t0.insert(ii_pair(11, 18));
  t0.insert(ii_pair(-5, 18));
  t0.insert(ii_pair(-13, 18));
  t0.insert(ii_pair(3, 18));
  t0.insert(ii_pair(84, 18));
  t0.insert(ii_pair(75, 18));
  t0.insert(ii_pair(41, 18));
  t0.insert(ii_pair(28, 18));
  t0.insert(ii_pair(57, 18));
  t0.insert(ii_pair(45, 18));

  RBTree<int, int> a {t0};

  ASSERT_EQ(!a.rb_assert(a.get_root()), false);
  ASSERT_EQ(a.size(), t0.size());
  ASSERT_EQ(*a.begin(), *t0.begin());

  auto it = a.begin();
  auto it1 = t0.begin();
  for (; it != a.end(); ++it, ++it1)
    ASSERT_EQ(*it, *it1);

  ASSERT_EQ(it.get_ptr(), nullptr);
  ASSERT_EQ(it1.get_ptr(), nullptr);
}

TEST_F(TreeTest, cpy_assign) {
  
  t0.insert(ii_pair(0, 123));
  // not unique
  t0.insert(ii_pair(0, 123));
  t0.insert(ii_pair(1, -11));
  t0.insert(ii_pair(2, 10));
  t0.insert(ii_pair(4, 1));
  t0.insert(ii_pair(-10, 18));
  t0.insert(ii_pair(110, 18));
  t0.insert(ii_pair(11, 18));
  t0.insert(ii_pair(-5, 18));
  t0.insert(ii_pair(-13, 18));
  t0.insert(ii_pair(3, 18));
  t0.insert(ii_pair(84, 18));
  t0.insert(ii_pair(75, 18));
  t0.insert(ii_pair(41, 18));
  t0.insert(ii_pair(28, 18));
  t0.insert(ii_pair(57, 18));
  t0.insert(ii_pair(45, 18));
  t0.insert(ii_pair(99, 18));
  t0.insert(ii_pair(-1, 18));
  t0.insert(ii_pair(44, 18));
  t0.insert(ii_pair(-3, 18));

  RBTree<int, int> a;

  a = t0;

  ASSERT_EQ(!a.rb_assert(a.get_root()), false);
  ASSERT_EQ(a.size(), t0.size());
  ASSERT_EQ(*a.begin(), *t0.begin());

  auto it = a.begin();
  auto it1 = t0.begin();
  for (; it != a.end(); ++it, ++it1)
    ASSERT_EQ(*it, *it1);

  ASSERT_EQ(it.get_ptr(), nullptr);
  ASSERT_EQ(it1.get_ptr(), nullptr);
}

TEST_F(TreeTest, move_ctor) {
  RBTree<int, std::string> tr {std::move(t3)};

  ASSERT_EQ(tr.size(), 3);
  ASSERT_EQ(t3.size(), 0);
  ASSERT_EQ(*tr.begin(), 1);
}

TEST_F(TreeTest, begin) {
  t1.insert(istr_pair(0, "BigCat"));
  t1.insert(istr_pair(2, "MidCat"));
  t1.insert(istr_pair(1, "SmallCat"));
  t1.insert(istr_pair(-1, "BiGDog"));
  t1.insert(istr_pair(-2, "SmallDog"));
  t1.insert(istr_pair(-3, "MidDog"));
  t1.insert(istr_pair(10, "BullDog"));
  t1.insert(istr_pair(-10, "Parrot"));

  ASSERT_EQ(t1.size(), 8);
  ASSERT_EQ(t1.at(*t1.begin()), "Parrot");
  ASSERT_EQ(t1.at(*++t1.begin()), "MidDog");

  ASSERT_EQ(1, t1.erase(*t1.begin()));

  ASSERT_EQ(t1.size(), 7);
  ASSERT_EQ(t1[*t1.begin()], "MidDog");
}

TEST_F(TreeTest, erase) {
  for (int i = 0; i < 11; ++i) {
    t0.insert(ii_pair(GetRandomValue(), GetRandomValue()));
    ASSERT_EQ(t0.rb_assert(t0.get_root()) == 0, false);
  }

  for (int i = 0; i < 51; ++i) {
    t0.erase(i);
    /* std::cout << "AFTER ERASE\n"; */
    /* t0.printTree(); */
    ASSERT_EQ(!t0.rb_assert(t0.get_root()), false);
  }
  t0.printTree();
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
