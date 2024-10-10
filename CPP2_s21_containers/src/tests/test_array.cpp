//
// Created by Тихон Чабусов on 29.07.2024.
//
#include "all_tests.h"

using namespace s21;

TEST(ArrayTest, Default_Constructor) {
  Array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5UL);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(ArrayTest, Initializer_List_Constructor) {
  Array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5UL);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
  EXPECT_EQ(arr[4], 5);
}

TEST(ArrayTest, Copy_Constructor) {
  Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  Array<int, 5> arr2(arr1);
  EXPECT_EQ(arr2.size(), 5UL);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
  EXPECT_EQ(arr2[4], 5);
}

TEST(ArrayTest, Move_Constructor) {
  Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  Array<int, 5> arr2(std::move(arr1));
  EXPECT_EQ(arr2.size(), 5UL);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
  EXPECT_EQ(arr2[4], 5);
}

TEST(ArrayTest, Copy_Assignment) {
  Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  Array<int, 5> arr2;
  arr2 = arr1;
  EXPECT_EQ(arr2.size(), 5UL);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
  EXPECT_EQ(arr2[4], 5);
}

TEST(ArrayTest, Move_Assignment) {
  Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  Array<int, 5> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.size(), 5UL);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
  EXPECT_EQ(arr2[4], 5);
}

TEST(ArrayTest, At) {
  Array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(1), 2);
  EXPECT_EQ(arr.at(2), 3);
  EXPECT_EQ(arr.at(3), 4);
  EXPECT_EQ(arr.at(4), 5);
  EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(ArrayTest, Front_Back) {
  Array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.front(), 1);
  EXPECT_EQ(arr.back(), 5);
}

TEST(ArrayTest, Data) {
  Array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(*arr.data(), 1);
}

TEST(ArrayTest, Iterators) {
  Array<int, 5> arr = {1, 2, 3, 4, 5};
  int sum = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 15);
}

TEST(ArrayTest, Empty_Size_Max_Size) {
  Array<int, 5> arr;
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(arr.size(), 5UL);
  EXPECT_EQ(arr.max_size(), 5UL);
}

TEST(ArrayTest, Swap) {
  Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  Array<int, 5> arr2 = {6, 7, 8, 9, 10};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 6);
  EXPECT_EQ(arr1[1], 7);
  EXPECT_EQ(arr1[2], 8);
  EXPECT_EQ(arr1[3], 9);
  EXPECT_EQ(arr1[4], 10);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
  EXPECT_EQ(arr2[4], 5);
}

TEST(ArrayTest, Fill) {
  Array<int, 5> arr;
  arr.fill(42);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 42);
  }
}
