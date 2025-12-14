//
// Created by Тихон Чабусов on 05.08.2024.
//

#include <utility>
#include <vector>

#include "all_tests.h"

using namespace s21;

TEST(SetTest, Default_Constructor) {
  Set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0UL);
}

TEST(SetTest, Initializer_List_Constructor) {
  Set<int> s = {1, 2, 3, 4, 5};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 5UL);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(5));
  EXPECT_FALSE(s.contains(6));
}

TEST(SetTest, Copy_Constructor) {
  Set<int> s1 = {1, 2, 3};
  Set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Move_Constructor) {
  Set<int> s1 = {1, 2, 3};
  Set<int> s2(std::move(s1));
  EXPECT_TRUE(s1.empty());
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s2.size(), 3UL);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Assignment_Operator) {
  Set<int> s1 = {1, 2, 3};
  Set<int> s2;
  s2 = s1;
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Move_Assignment_Operator) {
  Set<int> s1 = {1, 2, 3};
  Set<int> s2;
  s2 = std::move(s1);
  EXPECT_TRUE(s1.empty());
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s2.size(), 3UL);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Insert) {
  Set<int> s;
  auto result = s.insert(1);
  EXPECT_TRUE(result.second);
  EXPECT_EQ(*result.first, 1);
  EXPECT_EQ(s.size(), 1UL);

  result = s.insert(1);
  EXPECT_FALSE(result.second);
  EXPECT_EQ(s.size(), 1UL);
}

TEST(SetTest, Erase) {
  Set<int> s = {1, 2, 3};
  auto it = s.find(2);
  s.erase(it);
  EXPECT_FALSE(s.contains(2));
  EXPECT_EQ(s.size(), 2UL);
}

TEST(SetTest, Clear) {
  Set<int> s = {1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0UL);
}

TEST(SetTest, Swap) {
  Set<int> s1 = {1, 2, 3};
  Set<int> s2 = {4, 5, 6};
  s1.swap(s2);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Merge) {
  Set<int> s1 = {1, 2, 3};
  Set<int> s2 = {4, 5, 6};
  s1.merge(s2);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, Find) {
  Set<int> s = {1, 2, 3};
  auto it = s.find(2);
  EXPECT_EQ(*it, 2);
  it = s.find(4);
  EXPECT_EQ(it, s.end());
}

TEST(SetTest, Contains) {
  Set<int> s = {1, 2, 3};
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(3));
  EXPECT_FALSE(s.contains(4));
}
