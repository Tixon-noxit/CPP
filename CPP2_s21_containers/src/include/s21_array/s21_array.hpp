//
// Created by Тихон Чабусов on 29.07.2024.
//

#ifndef CPP2_S21_CONTAINERS_1_S21_ARRAY_HPP
#define CPP2_S21_CONTAINERS_1_S21_ARRAY_HPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21 {

template <typename T, std::size_t N>
class Array {
 private:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = std::size_t;

  value_type elements[N];
  size_type size_ = N;

 public:
  // Конструкторы

  Array();
  Array(std::initializer_list<value_type> const &items);
  Array(const Array &a);
  Array(Array &&a);
  ~Array() = default;

  Array &operator=(const Array &a);
  Array &operator=(Array &&a) noexcept;

  // Доступ к элементам

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Итераторы

  iterator begin();
  iterator end();

  // Вместимость

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Модификаторы

  void swap(Array &other) noexcept;
  void fill(const_reference value);
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_S21_ARRAY_HPP