//
// Created by Тихон Чабусов on 27.07.2024.
//
#include "all_tests.h"

using namespace s21;

// Тест конструктора по умолчанию
TEST(MapTest, Default_Constructor) {
  Map<int, int> map;
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0UL);
}

// Тест конструктора с initializer_list
TEST(MapTest, Initializer_List_Constructor) {
  Map<int, int> map{{1, 10}, {2, 20}, {3, 30}};
  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3UL);
  EXPECT_EQ(map.at(1), 10);
  EXPECT_EQ(map.at(2), 20);
  EXPECT_EQ(map.at(3), 30);
}

// Тест конструктора копирования
TEST(MapTest, Copy_Constructor) {
  Map<int, int> map1{{1, 10}, {2, 20}, {3, 30}};
  Map<int, int> map2(map1);
  EXPECT_FALSE(map2.empty());
  EXPECT_EQ(map2.size(), 3UL);
  EXPECT_EQ(map2.at(1), 10);
  EXPECT_EQ(map2.at(2), 20);
  EXPECT_EQ(map2.at(3), 30);
}

// Тест конструктора перемещения
TEST(MapTest, Move_Constructor) {
  Map<int, int> map1{{1, 10}, {2, 20}, {3, 30}};
  Map<int, int> map2(std::move(map1));
  EXPECT_FALSE(map2.empty());
  EXPECT_EQ(map2.size(), 3UL);
  EXPECT_EQ(map2.at(1), 10);
  EXPECT_EQ(map2.at(2), 20);
  EXPECT_EQ(map2.at(3), 30);
  EXPECT_TRUE(map1.empty());
  EXPECT_EQ(map1.size(), 0UL);
}

// Тест оператора присваивания перемещения
TEST(MapTest, Move_Assignment_Operator) {
  Map<int, int> map1{{1, 10}, {2, 20}, {3, 30}};
  Map<int, int> map2;
  map2 = std::move(map1);
  EXPECT_FALSE(map2.empty());
  EXPECT_EQ(map2.size(), 3UL);
  EXPECT_EQ(map2.at(1), 10);
  EXPECT_EQ(map2.at(2), 20);
  EXPECT_EQ(map2.at(3), 30);
  EXPECT_TRUE(map1.empty());
  EXPECT_EQ(map1.size(), 0UL);
}

// Тест метода at
TEST(MapTest, At) {
  Map<int, int> map{{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(map.at(1), 10);
  EXPECT_EQ(map.at(2), 20);
  EXPECT_EQ(map.at(3), 30);
  EXPECT_THROW(map.at(4), std::out_of_range);
}

// Тест оператора []
TEST(MapTest, Bracket_Operator) {
  Map<int, int> map;
  map[1] = 10;
  map[2] = 20;
  map[3] = 30;
  EXPECT_EQ(map[1], 10);
  EXPECT_EQ(map[2], 20);
  EXPECT_EQ(map[3], 30);
}

// Тест метода clear
TEST(MapTest, Clear) {
  Map<int, int> map{{1, 10}, {2, 20}, {3, 30}};
  map.clear();
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0UL);
}

// Тест метода insert
TEST(MapTest, Insert) {
  Map<int, int> map;
  auto result = map.insert({1, 10});
  EXPECT_TRUE(result.second);
  EXPECT_EQ((*result.first).second, 10);
  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 1UL);

  result = map.insert({1, 20});
  EXPECT_FALSE(result.second);
  EXPECT_EQ((*result.first).second, 10);
}

// Тест метода insert_or_assign
TEST(MapTest, Insert_Or_Assign) {
  Map<int, int> map;
  auto result = map.insert_or_assign(1, 10);
  EXPECT_TRUE(result.second);
  EXPECT_EQ((*result.first).second, 10);
  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 1UL);

  result = map.insert_or_assign(1, 20);
  EXPECT_FALSE(result.second);
  EXPECT_EQ((*result.first).second, 20);
}

// Тест метода erase
TEST(MapTest, Erase) {
  Map<int, int> map{{1, 10}, {2, 20}, {3, 30}};
  auto it = map.begin();
  map.erase(it);
  EXPECT_EQ(map.size(), 2UL);
  EXPECT_THROW(map.at(1), std::out_of_range);

  it = map.begin();
  map.erase(it);
  EXPECT_EQ(map.size(), 1UL);
  EXPECT_THROW(map.at(2), std::out_of_range);

  it = map.begin();
  map.erase(it);
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0UL);
}

// Тест метода swap
TEST(MapTest, Swap) {
  Map<int, int> map1{{1, 10}, {2, 20}};
  Map<int, int> map2{{3, 30}, {4, 40}};
  map1.swap(map2);

  EXPECT_EQ(map1.size(), 2UL);
  EXPECT_EQ(map1.at(3), 30);
  EXPECT_EQ(map1.at(4), 40);

  EXPECT_EQ(map2.size(), 2UL);
  EXPECT_EQ(map2.at(1), 10);
  EXPECT_EQ(map2.at(2), 20);
}

// Тест метода merge
TEST(MapTest, Merge) {
  Map<int, int> map1{{1, 10}, {2, 20}};
  Map<int, int> map2{{3, 30}, {4, 40}};
  map1.merge(map2);

  EXPECT_EQ(map1.size(), 4UL);
  EXPECT_EQ(map1.at(1), 10);
  EXPECT_EQ(map1.at(2), 20);
  EXPECT_EQ(map1.at(3), 30);
  EXPECT_EQ(map1.at(4), 40);

  EXPECT_TRUE(map2.empty());
}

// Тест метода contains
TEST(MapTest, Contains) {
  Map<int, int> map{{1, 10}, {2, 20}};
  EXPECT_TRUE(map.contains(1));
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

// Тест итераторов
TEST(MapTest, Iterators) {
  Map<int, int> map{{1, 10}, {2, 20}, {3, 30}};
  auto it = map.begin();
  EXPECT_EQ((*it).second, 10);
  ++it;
  EXPECT_EQ((*it).second, 20);
  ++it;
  EXPECT_EQ((*it).second, 30);
  ++it;
  EXPECT_EQ(it, map.end());
}

TEST(MapTest, Erase_Leaf_Node) {
  s21::Map<int, int> map;
  map.insert(10, 10);
  map.insert(5, 5);
  map.insert(15, 15);
  map.insert(3, 3);  // Leaf node

  auto it = map.find(3);
  map.erase(it);

  EXPECT_EQ(map.find(3), map.end());
  EXPECT_EQ(map.size(), 3UL);
}

TEST(MapTest, Erase_Node_With_One_Child) {
  s21::Map<int, int> map;
  map.insert(10, 10);
  map.insert(5, 5);
  map.insert(15, 15);
  map.insert(3, 3);
  map.insert(4, 4);  // Node with one child

  auto it = map.find(3);
  map.erase(it);

  EXPECT_EQ(map.find(3), map.end());
  EXPECT_NE(map.find(4), map.end());
  EXPECT_EQ(map.size(), 4UL);
}

TEST(MapTest, Erase_Node_With_Two_Children) {
  s21::Map<int, int> map;
  map.insert(10, 10);
  map.insert(5, 5);
  map.insert(15, 15);
  map.insert(3, 3);
  map.insert(7, 7);
  map.insert(12, 12);
  map.insert(18, 18);
  map.insert(6, 6);  // Node with two children
  map.insert(8, 8);  // Node with two children

  auto it = map.find(7);
  map.erase(it);

  EXPECT_EQ(map.find(7), map.end());
  EXPECT_NE(map.find(6), map.end());
  EXPECT_NE(map.find(8), map.end());
  EXPECT_EQ(map.size(), 8UL);
}

TEST(MapTest, Erase_Root_Node) {
  s21::Map<int, int> map;
  map.insert(10, 10);  // Root node
  map.insert(5, 5);
  map.insert(15, 15);

  auto it = map.find(10);
  map.erase(it);

  EXPECT_EQ(map.find(10), map.end());
  EXPECT_NE(map.find(5), map.end());
  EXPECT_NE(map.find(15), map.end());
  EXPECT_EQ(map.size(), 2UL);
}

TEST(MapTest, Erase_Non_Existent_Node) {
  s21::Map<int, int> map;
  map.insert(10, 10);
  map.insert(5, 5);
  map.insert(15, 15);

  auto it = map.find(20);  // Node does not exist
  map.erase(it);

  EXPECT_EQ(map.find(20), map.end());
  EXPECT_EQ(map.size(), 3UL);
}
