//
// Created by Тихон Чабусов on 29.07.2024.
//

#include "../../include/s21_array/s21_array.hpp"

namespace s21 {

// Конструкторы

template <typename T, std::size_t N>
Array<T, N>::Array() : size_(N) {
  std::fill(elements, elements + size_, 0);
}

template <typename T, std::size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::out_of_range("Initializer list size exceeds array capacity");
  }
  size_type i = 0;
  for (auto it = items.begin(); it != items.end(); ++it, ++i) {
    elements[i] = *it;
  }
}

template <typename T, std::size_t N>
Array<T, N>::Array(const Array &a) {
  for (size_type i = 0; i < N; ++i) {
    elements[i] = a.elements[i];
  }
}

template <typename T, std::size_t N>
Array<T, N>::Array(Array &&a) {
  std::move(a.elements, a.elements + N, elements);
}

// Операторы присваивания

template <typename T, std::size_t N>
Array<T, N> &Array<T, N>::operator=(const Array &a) {
  if (this != &a) {
    for (size_type i = 0; i < N; ++i) {
      elements[i] = a.elements[i];
    }
    size_ = a.size_;
  }
  return *this;
}

template <typename T, std::size_t N>
Array<T, N> &Array<T, N>::operator=(Array &&a) noexcept {
  if (this != &a) {
    std::move(a.elements, a.elements + N, elements);
    size_ = a.size_;
    a.size_ = 0;
  }
  return *this;
}

// Доступ к элементам

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return elements[pos];
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type pos) {
  return elements[pos];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::front() {
  return elements[0];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::back() {
  return elements[N - 1];
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::data() {
  return elements;
}

// Итераторы

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() {
  return elements;
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::end() {
  return elements + N;
}

// Вместимость

template <typename T, std::size_t N>
bool Array<T, N>::empty() const noexcept {
  return N == 0;
}

template <typename T, std::size_t N>
typename Array<T, N>::size_type Array<T, N>::size() const noexcept {
  return N;
}

template <typename T, std::size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size() const noexcept {
  return N;
}

// Модификаторы

template <typename T, std::size_t N>
void Array<T, N>::swap(Array &other) noexcept {
  for (size_type i = 0; i < N; ++i) {
    T temp = elements[i];
    elements[i] = other.elements[i];
    other.elements[i] = temp;
  }
}

template <typename T, std::size_t N>
void Array<T, N>::fill(const_reference value) {
  std::fill_n(elements, N, value);
}

}  // namespace s21