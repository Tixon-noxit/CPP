//
// Created by adis on 21.07.2024.
//

#include <gtest/gtest.h>

#include <queue>

#include "../include/s21_containers.hpp"

void test_push(s21::queue<int>& a, int val) {
  auto ls = a.size();
  auto first = ls == 0 ? 0 : a.front();
  a.push(val);
  EXPECT_EQ(a.back(), val);
  EXPECT_EQ(a.size(), ls + 1);
  if (ls != 0) {
    EXPECT_EQ(a.front(), first);
  }
}

TEST(S21_Queue, Constructor1) {
  s21::queue<int> q;
  EXPECT_EQ(q.size(), 0UL);
}

TEST(S21_Queue, Constructor2) {
  s21::queue<int> q(20);
  EXPECT_EQ(q.size(), 0UL);
}

TEST(S21_Queue, Push1) {
  s21::queue<int> q;
  test_push(q, 1);
}

TEST(S21_Queue, Push2) {
  s21::queue<int> q;
  q.push(1);
  q.push(2);
  EXPECT_EQ(q.size(), 2UL);
  EXPECT_EQ(q.back(), 2);
  EXPECT_EQ(q.front(), 1);
}

TEST(S21_Queue, Pop1) {
  s21::queue<int> q;
  test_push(q, 1);
  q.pop();
  EXPECT_EQ(q.size(), 0UL);
}

TEST(S21_Queue, Pop2) {
  s21::queue<int> q;
  q.push(1);
  test_push(q, 2);
  q.pop();
  EXPECT_EQ(q.size(), 1UL);
  EXPECT_EQ(q.back(), 2);
  EXPECT_EQ(q.front(), 2);
}

TEST(S21_Queue, Constructor3) {
  s21::queue<int> c;
  test_push(c, 1);
  s21::queue<int> q(c);
  EXPECT_EQ(q.front(), c.front());
  EXPECT_EQ(q.back(), c.back());
  EXPECT_EQ(q.empty(), c.empty());
  EXPECT_EQ(q.size(), c.size());
}

TEST(S21_Queue, Constructor4) {
  s21::queue<int> c;
  test_push(c, 1);
  auto size = c.size();
  auto front = c.front();
  auto back = c.back();
  auto empty = c.empty();
  s21::queue<int> q = std::move(c);
  EXPECT_EQ(q.front(), front);
  EXPECT_EQ(q.back(), back);
  EXPECT_EQ(q.empty(), empty);
  EXPECT_EQ(q.size(), size);
}

TEST(S21_Queue, Constructor5) {
  s21::queue<int> c{1, 2, 3, 4};
  EXPECT_EQ(c.size(), 4UL);
  EXPECT_EQ(c.empty(), false);
  EXPECT_EQ(c.front(), 1);
  EXPECT_EQ(c.back(), 4);
}

TEST(S21_Queue, Swap1) {
  s21::queue<int> q;
  s21::queue<int> c;
  test_push(q, 1);
  test_push(q, 2);
  test_push(q, 3);
  test_push(c, 3);
  test_push(c, 2);
  test_push(c, 1);
  std::swap(q, c);
  EXPECT_EQ(q.front(), 3);
  q.pop();
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_EQ(q.front(), 1);
}

TEST(S21_Queue, Swap2) {
  s21::queue<int> q;
  s21::queue<int> c;
  test_push(q, 1);
  test_push(q, 2);
  test_push(q, 3);
  test_push(c, 3);
  test_push(c, 2);
  test_push(c, 1);
  q = c;
  EXPECT_EQ(q.front(), 3);
  q.pop();
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_EQ(q.front(), 1);
}

TEST(S21_Queue, Equal1) {
  s21::queue<int> q;
  test_push(q, 1);
  test_push(q, 2);
  test_push(q, 3);
  s21::queue<int> c;
  test_push(c, 1);
  test_push(c, 2);
  test_push(c, 3);
  EXPECT_EQ(q, c);
}

TEST(S21_Queue, Equal2) {
  s21::queue<int> q;
  test_push(q, 1);
  test_push(q, 2);
  test_push(q, 3);
  s21::queue<int> c;
  test_push(c, 1);
  test_push(c, 2);
  test_push(c, 4);
  EXPECT_NE(q, c);
}

TEST(S21_Queue, Equal3) {
  s21::queue<int> q;
  test_push(q, 1);
  test_push(q, 2);
  s21::queue<int> c;
  test_push(c, 1);
  test_push(c, 2);
  test_push(c, 3);
  EXPECT_NE(q, c);
}

TEST(S21_Queue, Equal4) {
  s21::queue<int> q;
  test_push(q, 1);
  test_push(q, 2);
  test_push(q, 3);
  s21::queue<int> c;
  test_push(c, 1);
  test_push(c, 2);
  test_push(c, 3);
  EXPECT_TRUE(q == c);
}

TEST(S21_Queue, Equal5) {
  s21::queue<int> q;
  test_push(q, 1);
  test_push(q, 2);
  test_push(q, 3);
  s21::queue<int> c;
  test_push(c, 1);
  test_push(c, 2);
  test_push(c, 4);
  EXPECT_TRUE(q != c);
}

TEST(S21_Queue, GreaterThen1) {
  s21::queue<int> q;
  test_push(q, 1);
  test_push(q, 2);
  test_push(q, 3);
  s21::queue<int> c;
  test_push(c, 1);
  test_push(c, 2);
  EXPECT_GT(q, c);
}

TEST(S21_Queue, GreaterThen2) {
  s21::queue<int> q;
  test_push(q, 1);
  test_push(q, 2);
  test_push(q, 3);
  s21::queue<int> c;
  test_push(c, 1);
  test_push(c, 2);
  test_push(c, 3);
  EXPECT_FALSE(q > c);
}

TEST(S21_Queue, LessThen1) {
  s21::queue<int> q;
  test_push(q, 1);
  test_push(q, 2);
  s21::queue<int> c;
  test_push(c, 1);
  test_push(c, 2);
  test_push(c, 3);
  EXPECT_LT(q, c);
}

TEST(S21_Queue, LessThen2) {
  s21::queue<int> q;
  test_push(q, 1);
  test_push(q, 2);
  test_push(q, 3);
  s21::queue<int> c;
  test_push(c, 1);
  test_push(c, 2);
  test_push(c, 3);
  EXPECT_FALSE(q < c);
}