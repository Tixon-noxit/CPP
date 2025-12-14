//
// Created by KWAZAR_ on 13.07.2024.
//
#ifndef S21_STACK_CPP
#define S21_STACK_CPP

#include "../../include/s21_stack/s21_stack.hpp"

namespace s21 {

template <class T>
stack<T>::stack() : data_(nullptr), size_(0), capacity_(0) {}

template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items)
    : data_(new value_type[items.size()]),
      size_(items.size()),
      capacity_(items.size()) {
  std::copy(items.begin(), items.end(), data_);
}

template <class T>
stack<T>::stack(const stack &other)
    : data_(new value_type[other.capacity_]),
      size_(other.size_),
      capacity_(other.capacity_) {
  std::copy(other.data_, other.data_ + other.size_, data_);
}

template <class T>
stack<T>::stack(stack &&other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <class T>
stack<T>::~stack() {
  delete[] data_;
}

template <class T>
typename stack<T>::const_reference stack<T>::top() const {
  if (empty()) throw std::out_of_range("stack is empty");
  return data_[size_ - 1];
}

template <class T>
bool stack<T>::empty() const {
  return size_ == 0;
}

template <class T>
typename stack<T>::size_type stack<T>::size() const {
  return size_;
}

template <class T>
void stack<T>::push(const_reference value) {
  if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : 2 * capacity_);
  data_[size_++] = value;
}

template <class T>
void stack<T>::pop() {
  if (empty()) throw std::out_of_range("stack is empty");
  --size_;
}

template <class T>
void stack<T>::swap(stack &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <class T>
template <class... Args>
void stack<T>::insert_many_front(Args &&...args) {
  size_type new_elements = sizeof...(args);
  if (size_ + new_elements > capacity_) reserve(size_ + new_elements);

  value_type temp[] = {args...};

  for (size_type i = 0; i < new_elements; ++i) {
    data_[size_ + i] = temp[i];
  }

  size_ += new_elements;
}

template <class T>
stack<T> &stack<T>::operator=(const stack &other) {
  if (this != &other) {
    stack temp(other);
    swap(temp);
  }

  return *this;
}

template <class T>
stack<T> &stack<T>::operator=(stack &&other) noexcept {
  if (this != &other) {
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  return *this;
}

template <class T>
void stack<T>::reserve(size_type new_capacity) {
  if (new_capacity > capacity_) {
    value_type *new_data = new value_type[new_capacity];

    for (size_type i = 0; i < size_; ++i) {
      new_data[i] = std::move(data_[i]);
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }
}
}  // namespace s21

#endif  // S21_STACK_CPP
