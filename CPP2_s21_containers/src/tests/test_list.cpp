//
// Created by Тихон Чабусов on 21.07.2024.
//

#include "all_tests.h"

using namespace s21;

TEST(ListTest, Default_Constructor) {
  List<int> list;
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(static_cast<int>(list.size()), 0);
}

TEST(ListTest, Size_Constructor) {
  List<int> list(5);
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(static_cast<int>(list.size()), 5);
}

TEST(ListTest, Initializer_List_Constructor) {
  List<int> list = {1, 2, 3, 4, 5};
  EXPECT_EQ(static_cast<int>(list.size()), 5);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 5);
}

TEST(ListTest, Copy_Constructor) {
  List<int> list1 = {1, 2, 3, 4, 5};
  List<int> list2(list1);
  EXPECT_EQ(static_cast<int>(list1.size()), 5);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 5);
}

TEST(ListTest, Move_Constructor) {
  List<int> list1 = {1, 2, 3, 4, 5};
  List<int> list2(std::move(list1));
  EXPECT_EQ(list1.size(), 0UL);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 5);
  EXPECT_TRUE(list1.empty());
}

TEST(ListTest, Copy_Assignment) {
  List<int> list1 = {1, 2, 3, 4, 5};
  List<int> list2;
  list2 = list1;
  EXPECT_EQ(static_cast<int>(list1.size()), 5);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 5);
}

TEST(ListTest, Move_Assignment) {
  List<int> list1 = {1, 2, 3, 4, 5};
  List<int> list2;
  list2 = std::move(list1);
  EXPECT_EQ(list1.size(), 0UL);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 5);
  EXPECT_TRUE(list1.empty());
}

TEST(ListTest, Push_Back) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  EXPECT_EQ(static_cast<int>(list.size()), 2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, Push_Front) {
  List<int> list;
  list.push_front(1);
  list.push_front(2);
  EXPECT_EQ(static_cast<int>(list.size()), 2);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, Pop_Back) {
  List<int> list = {1, 2, 3};
  list.pop_back();
  EXPECT_EQ(static_cast<int>(list.size()), 2);
  EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, Pop_Front) {
  List<int> list = {1, 2, 3};
  list.pop_front();
  EXPECT_EQ(static_cast<int>(list.size()), 2);
  EXPECT_EQ(list.front(), 2);
}

TEST(ListTest, Clear) {
  List<int> list = {1, 2, 3};
  list.clear();
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(static_cast<int>(list.size()), 0);
}

TEST(ListTest, Insert) {
  List<int> list = {1, 2, 3};
  auto it = list.begin();
  ++it;
  list.insert(it, 4);
  EXPECT_EQ(static_cast<int>(list.size()), 4);
  EXPECT_EQ(*(++list.begin()), 4);
}

TEST(ListTest, Erase) {
  List<int> list = {1, 2, 3};
  auto it = list.begin();
  ++it;
  list.erase(it);
  EXPECT_EQ(static_cast<int>(list.size()), 2);
  EXPECT_EQ(*(++list.begin()), 3);
}

TEST(ListTest, Swap_Empty_Lists) {
  s21::List<int> list1;
  s21::List<int> list2;

  list1.swap(list2);

  EXPECT_TRUE(list1.empty());
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Swap_Non_Empty_Lists) {
  s21::List<int> list1;
  s21::List<int> list2;

  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  list2.push_back(4);
  list2.push_back(5);
  list2.push_back(6);

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 3UL);
  EXPECT_EQ(list2.size(), 3UL);

  EXPECT_EQ(list1.front(), 4);
  EXPECT_EQ(list1.back(), 6);

  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 3);
}

TEST(ListTest, Swap_With_One_Empty_List) {
  s21::List<int> list1;
  s21::List<int> list2;

  list1.push_back(1);
  list1.push_back(2);

  list2.push_back(3);
  list2.push_back(4);
  list2.push_back(5);

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 3UL);
  EXPECT_EQ(list2.size(), 2UL);

  EXPECT_EQ(list1.front(), 3);
  EXPECT_EQ(list1.back(), 5);

  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
}

TEST(ListTest, Swap_Lists_With_Different_Sizes) {
  s21::List<int> list1;
  s21::List<int> list2;

  list1.push_back(1);
  list1.push_back(2);

  list2.push_back(3);
  list2.push_back(4);
  list2.push_back(5);
  list2.push_back(6);

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 4UL);
  EXPECT_EQ(list2.size(), 2UL);

  EXPECT_EQ(list1.front(), 3);
  EXPECT_EQ(list1.back(), 6);

  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
}

TEST(ListTest, Merge) {
  List<int> list1 = {1, 3, 5};
  List<int> list2 = {2, 4, 6};
  list1.merge(list2);
  EXPECT_EQ(static_cast<int>(list1.size()), 6);
  EXPECT_EQ(static_cast<int>(list2.size()), 0);
  auto it = list1.begin();
  for (int i = 1; i <= 6; ++i, ++it) {
    EXPECT_EQ(*it, i);
  }
}

TEST(ListTest, Reverse) {
  List<int> list = {1, 2, 3};
  list.reverse();
  auto it = list.begin();
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it, 1);
}

TEST(ListTest, Unique) {
  List<int> list = {1, 1, 2, 3, 3};
  list.unique();
  EXPECT_EQ(static_cast<int>(list.size()), 3);
  auto it = list.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it, 3);
}

TEST(ListTest, Sort) {
  List<int> list = {3, 1, 2};
  list.sort();
  auto it = list.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it, 3);
}