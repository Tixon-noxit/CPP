//
// Created by AdisAlagic on 17.07.2024.
//

#include "s21_queue/s21_queue.hpp"

#include <algorithm>

namespace s21 {
template <typename value_type>
queue<value_type>::queue() : array_(std::make_unique<value_type[]>(std_size)) {}

template <typename value_type>
queue<value_type>::queue(queue<value_type>::size_type capacity)
    : size_((queue<value_type>::std_size)),
      capacity_(capacity),
      array_(std::make_unique<value_type[]>(capacity)) {}

template <typename value_type>
queue<value_type>::queue(const queue<value_type> &other)
    : size_(other.size_),
      capacity_(other.capacity_),
      array_(std::make_unique<value_type[]>(other.capacity_)) {
  memcpy(this->array_.get(), other.array_.get(), size_);
}

template <typename value_type>
queue<value_type>::queue(queue<value_type> &&other) noexcept
    : size_(other.size_),
      capacity_(other.capacity_),
      array_(std::make_unique<value_type[]>(other.capacity_)) {
  memcpy(this->array_.get(), other.array_.get(),
         capacity_ * sizeof(value_type));
  other.array_.reset();
  other.size_ = std_size;
  other.capacity_ = std_size;
}

template <typename value_type>
queue<value_type>::~queue() {
  capacity_ = 0;
  size_ = 0;
  array_.reset();
}

template <typename T>
queue<T>::queue(const std::initializer_list<value_type> &items)
    : size_(items.size()),
      capacity_(items.size()),
      array_(std::make_unique<value_type[]>(items.size())) {
  memcpy(this->array_.get(), items.begin(), size_ * sizeof(value_type));
}

template <typename value_type>
typename queue<value_type>::reference queue<value_type>::back() {
  return this->array_.get()[size_ - 1];
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::back() const {
  return this->array_.get()[size_ - 1];
}

template <typename value_type>
typename queue<value_type>::reference queue<value_type>::front() {
  return this->array_.get()[0];
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::front() const {
  return this->array_.get()[0];
}

template <typename value_type>
bool queue<value_type>::empty() const {
  return this->size_ == 0;
}

template <typename value_type>
void queue<value_type>::pop() {
  if (size_ == 1) {
    memset(array_.get(), 0, sizeof(value_type) * capacity_);
  } else {
    for (size_type i = 0; i < (size_type)(size_ - 1); ++i) {
      this->array_.get()[i] = this->array_.get()[i + 1];
    }
  }
  size_--;
}

template <typename value_type>
void queue<value_type>::push(const value_type &val) {
  if (capacity_ == 0) reallocate((size_type)1);
  if (capacity_ == size_) reallocate(capacity_ * 2);
  this->array_.get()[size_] = val;
  size_++;
}

template <typename value_type>
typename queue<value_type>::size_type queue<value_type>::size() const {
  return size_;
}

template <typename value_type>
void queue<value_type>::reallocate(queue<value_type>::size_type new_size) {
  if (new_size == this->capacity_) return;
  std::unique_ptr<value_type[]> copy = std::make_unique<value_type[]>(new_size);
  memcpy(copy.get(), this->array_.get(),
         (this->capacity_ > new_size ? new_size : this->capacity_) *
             sizeof(value_type));
  this->array_ = std::move(copy);
  this->capacity_ = new_size;
}

template <typename value_type>
bool queue<value_type>::operator<(const queue &rhs) const {
  return this->size_ < rhs.size_;
}

template <typename value_type>
bool queue<value_type>::operator>(const queue &rhs) const {
  return rhs < *this;
}

template <typename value_type>
bool queue<value_type>::operator<=(const queue &rhs) const {
  return (rhs < *this) || (rhs == *this);  // do not simplify
}

template <typename value_type>
bool queue<value_type>::operator>=(const queue &rhs) const {
  return (rhs > *this) || (rhs == *this);  // do not simplify
}

template <typename value_type>
bool queue<value_type>::operator==(const queue &rhs) const {
  if (this->size_ != rhs.size_) return false;
  for (size_type i = 0; i < std::min(this->size_, rhs.size_); i++) {
    if (this->array_.get()[i] != rhs.array_.get()[i]) return false;
  }
  return true;
}

template <typename value_type>
bool queue<value_type>::operator!=(const queue &rhs) const {
  return !(rhs == *this);  // do not simplify
}

template <typename value_type>
void queue<value_type>::operator<<(const value_type val) {
  this->push(val);
}

template <typename value_type>
queue<value_type> &queue<value_type>::operator=(const queue &rhs) {
  if (this == &rhs) return *this;
  if (rhs.size_ > this->size_) reallocate(rhs.capacity_);
  memcpy(this->array_.get(), rhs.array_.get(), capacity_ * sizeof(value_type));
  this->capacity_ = rhs.capacity_;
  this->size_ = rhs.size_;
  return *this;
}

}  // namespace s21