//
// Created by Тихон Чабусов on 29.07.2024.
//

#include "all_tests.h"

using namespace s21;

TEST(MultisetTest, Default_Constructor) {
  Multiset<int> ms;
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0UL);
}

TEST(MultisetTest, Initializer_List_Constructor) {
  Multiset<int> ms{1, 2, 3, 4, 5};
  EXPECT_FALSE(ms.empty());
  EXPECT_EQ(ms.size(), 5UL);
}

TEST(MultisetTest, Copy_Constructor) {
  Multiset<int> ms1{1, 2, 3};
  Multiset<int> ms2(ms1);
  EXPECT_EQ(ms1.size(), ms2.size());
  EXPECT_EQ(ms1.count(1), ms2.count(1));
}

TEST(MultisetTest, Move_Constructor) {
  Multiset<int> ms1{1, 2, 3};
  Multiset<int> ms2(std::move(ms1));
  EXPECT_EQ(ms2.size(), 3UL);
  EXPECT_TRUE(ms1.empty());
}

TEST(MultisetTest, Assignment_Operator) {
  Multiset<int> ms1{1, 2, 3};
  Multiset<int> ms2;
  ms2 = ms1;
  EXPECT_EQ(ms1.size(), ms2.size());
  EXPECT_EQ(ms1.count(1), ms2.count(1));
}

TEST(MultisetTest, Insert_And_Count) {
  Multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(1);
  EXPECT_EQ(ms.count(1), 2UL);
  EXPECT_EQ(ms.count(2), 1UL);
}

TEST(MultisetTest, Erase) {
  Multiset<int> ms{1, 2, 3};
  auto it = ms.find(2);
  ms.erase(it);
  EXPECT_EQ(ms.count(2), 0UL);
  EXPECT_EQ(ms.size(), 2UL);
}

TEST(MultisetTest, Swap) {
  Multiset<int> ms1{1, 2, 3};
  Multiset<int> ms2{4, 5, 6};
  ms1.swap(ms2);
  EXPECT_EQ(ms1.count(4), 1UL);
  EXPECT_EQ(ms2.count(1), 1UL);
}

TEST(MultisetTest, Merge) {
  Multiset<int> ms1{1, 2, 3};
  Multiset<int> ms2{3, 4, 5};
  ms1.merge(ms2);
  EXPECT_EQ(ms1.count(3), 2UL);
  EXPECT_EQ(ms1.count(4), 1UL);
  EXPECT_EQ(ms2.size(), 0UL);
}

TEST(MultisetTest, Find) {
  Multiset<int> ms{1, 2, 3};
  auto it = ms.find(2);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(*it, 2);
}

TEST(MultisetTest, Contains) {
  Multiset<int> ms{1, 2, 3};
  EXPECT_TRUE(ms.contains(2));
  EXPECT_FALSE(ms.contains(4));
}

TEST(MultisetTest, Lower_Bound) {
  Multiset<int> ms{1, 2, 3, 4, 5};
  auto it = ms.lower_bound(3);
  EXPECT_EQ(*it, 3);
}

TEST(MultisetTest, Upper_Bound) {
  Multiset<int> ms{1, 2, 3, 4, 5};
  auto it = ms.upper_bound(3);
  EXPECT_EQ(*it, 4);
}