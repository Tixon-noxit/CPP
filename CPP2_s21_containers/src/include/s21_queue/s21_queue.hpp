//
// Created by Тихон Чабусов on 13.07.2024.
//

#ifndef CPP2_S21_CONTAINERS_1_S21_QUEUE_HPP
#define CPP2_S21_CONTAINERS_1_S21_QUEUE_HPP

#include <cassert>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <locale>
#include <memory>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class queue {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  queue();

  queue(const queue<value_type> &other);

  queue(queue<value_type> &&other)

      noexcept;

  explicit queue(size_type capacity);

  queue(std::initializer_list<value_type> const &items);

  ~queue();

  reference back();

  const_reference back() const;

  reference front();

  const_reference front() const;

  [[nodiscard]] bool empty() const;

  void pop();

  void push(const_reference val);

  [[nodiscard]] size_type size() const;

  void operator<<(value_type val);

  bool operator==(const queue &rhs) const;

  bool operator!=(const queue &rhs) const;

  bool operator<(const queue &rhs) const;

  bool operator>(const queue &rhs) const;

  bool operator<=(const queue &rhs) const;

  bool operator>=(const queue &rhs) const;

  queue<T> &operator=(const queue &rhs);

  // Метод insert_many_back
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (void)std::initializer_list<int>{(push(std::forward<Args>(args)), 0)...};
  }

 private:
  static constexpr size_type std_size = 0;
  size_type size_ = std_size;
  size_type capacity_ = std_size;
  std::unique_ptr<value_type[]> array_;

  void reallocate(size_type new_size);
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_S21_QUEUE_HPP
