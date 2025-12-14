//
// Created by Тихон Чабусов on 25.07.2024.
//

#include "../../include/s21_vector/s21_vector.hpp"

#include <algorithm>
#include <cstring>
#include <stdexcept>

namespace s21 {

// Конструкторы

template <typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
Vector<T>::Vector(size_type n) : data_(new T[n]), size_(n), capacity_(n) {}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> const &items)
    : data_(new T[items.size()]), size_(items.size()), capacity_(items.size()) {
  auto it = items.begin();
  for (size_t i = 0; it != items.end(); ++it, ++i) {
    data_[i] = *it;
  }
}

template <typename T>
Vector<T>::Vector(const Vector &other)
    : data_(new T[other.capacity_]),
      size_(other.size_),
      capacity_(other.capacity_) {
  for (size_t i = 0; i < other.size_; ++i) {
    data_[i] = other.data_[i];
  }
}

template <typename T>
Vector<T>::Vector(Vector &&other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&other) noexcept {
  if (this != &other) {
    delete[] data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

// Деструктор

template <typename T>
Vector<T>::~Vector() {
  delete[] data_;
}

// Доступ к элементам

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() {
  if (empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() {
  if (empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[size_ - 1];
}

template <typename T>
T *Vector<T>::data() {
  return data_;
}

// Итераторы
// В заголовочном файле

// Вместимость

template <typename T>
bool Vector<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() {
  return size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void Vector<T>::reserve(size_type new_capacity) {
  if (new_capacity > capacity_) {
    T *new_data = new T[new_capacity];
    for (size_type i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    T *new_data = new T[size_];
    for (size_type i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
  }
}

// Модификаторы

template <typename T>
void Vector<T>::clear() {
  size_ = 0;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - data_;
  if (size_ == capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  for (size_type i = size_; i > index; --i) {
    data_[i] = data_[i - 1];
  }
  data_[index] = value;
  ++size_;
  return data_ + index;
}

template <typename T>
void Vector<T>::erase(iterator pos) {
  iterator erase_pos = data_ + (pos - data_);
  for (T *it = erase_pos + 1; it != data_ + size_; ++it) {
    *(it - 1) = *it;
  }
  --size_;
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve(capacity_ == 0 ? 1 : 2 * capacity_);
  }
  data_[size_++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
  }
}

template <typename T>
void Vector<T>::swap(Vector &other) {
  size_type temp_size = size_;
  size_ = other.size_;
  other.size_ = temp_size;

  size_type temp_capacity = capacity_;
  capacity_ = other.capacity_;
  other.capacity_ = temp_capacity;

  T *temp_data = data_;
  data_ = other.data_;
  other.data_ = temp_data;
}

}  // namespace s21