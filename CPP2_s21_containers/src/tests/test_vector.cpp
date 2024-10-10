//
// Created by Тихон Чабусов on 25.07.2024.
//

#include "all_tests.h"

using namespace s21;

// Тесты конструкторов
TEST(VectorTest, Default_Constructor) {
  Vector<int> v;
  EXPECT_EQ(v.size(), 0UL);
  EXPECT_EQ(v.capacity(), 0UL);
}

TEST(VectorTest, Size_Constructor) {
  Vector<int> v(5);
  EXPECT_EQ(v.size(), 5UL);
  EXPECT_EQ(v.capacity(), 5UL);
}

TEST(VectorTest, Initializer_List_Constructor) {
  Vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5UL);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, Copy_Constructor) {
  Vector<int> v1{1, 2, 3};
  Vector<int> v2(v1);
  EXPECT_EQ(v2.size(), 3UL);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 3);
}

TEST(VectorTest, Move_Constructor) {
  Vector<int> v1{1, 2, 3};
  Vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.size(), 3UL);
  EXPECT_EQ(v1.size(), 0UL);
}

// Тесты доступа к элементам
TEST(VectorTest, At) {
  Vector<int> v{1, 2, 3};
  EXPECT_EQ(v.at(1), 2);
  EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(VectorTest, Operator_Square_Brackets) {
  Vector<int> v{1, 2, 3};
  EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, Front) {
  Vector<int> v{1, 2, 3};
  EXPECT_EQ(v.front(), 1);
  Vector<int> empty_v;
  EXPECT_THROW(empty_v.front(), std::out_of_range);
}

TEST(VectorTest, Back) {
  Vector<int> v{1, 2, 3};
  EXPECT_EQ(v.back(), 3);
  Vector<int> empty_v;
  EXPECT_THROW(empty_v.back(), std::out_of_range);
}

// Тесты итераторов
TEST(VectorTest, Begin_End) {
  Vector<int> v{1, 2, 3};
  EXPECT_EQ(*v.begin(), 1);
  EXPECT_EQ(*(v.end() - 1), 3);
}

// Тесты вместимости
TEST(VectorTest, Empty) {
  Vector<int> v;
  EXPECT_TRUE(v.empty());
  v.push_back(1);
  EXPECT_FALSE(v.empty());
}

TEST(VectorTest, Reserve) {
  Vector<int> v;
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10UL);
}

TEST(VectorTest, Shrink_To_Fit) {
  Vector<int> v{1, 2, 3};
  v.reserve(10);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 3UL);
}

// Тесты модификаторов
TEST(VectorTest, Clear) {
  Vector<int> v{1, 2, 3};
  v.clear();
  EXPECT_EQ(v.size(), 0UL);
}

TEST(VectorTest, Insert) {
  Vector<int> v{1, 2, 3};
  v.insert(v.begin() + 1, 4);
  EXPECT_EQ(v[1], 4);
}

TEST(VectorTest, Erase) {
  Vector<int> v{1, 2, 3};
  v.erase(v.begin() + 1);
  EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, Push_Back) {
  Vector<int> v;
  v.push_back(1);
  EXPECT_EQ(v.size(), 1UL);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, Pop_Back) {
  Vector<int> v{1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.size(), 2UL);
  EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, Swap) {
  Vector<int> v1{1, 2, 3};
  Vector<int> v2{4, 5, 6};
  v1.swap(v2);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v2[0], 1);
}
