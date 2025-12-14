//
// Created by KWAZAR_ on 13.07.2024.
//

#ifndef CPP2_S21_CONTAINERS_1_S21_STACK_HPP
#define CPP2_S21_CONTAINERS_1_S21_STACK_HPP

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &other);
  stack(stack &&other) noexcept;
  ~stack();

  const_reference top() const;
  bool empty() const;
  size_type size() const;
  void push(const_reference value);
  void pop();

  void swap(stack &other);

  template <class... Args>
  void insert_many_front(Args &&...args);

  stack &operator=(const stack &other);
  stack &operator=(stack &&other) noexcept;

 private:
  value_type *data_;
  size_type size_;
  size_type capacity_;

  void reserve(size_type new_capacity);
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_S21_STACK_HPP
