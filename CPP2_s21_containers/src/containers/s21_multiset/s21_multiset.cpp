//
// Created by Тихон Чабусов on 29.07.2024.
//

#include "../../include/s21_multiset/s21_multiset.hpp"

namespace s21 {

template <typename Key, typename Compare, typename Allocator>
Multiset<Key, Compare, Allocator>::Multiset() : root_(nullptr), size_(0) {}

template <typename Key, typename Compare, typename Allocator>
Multiset<Key, Compare, Allocator>::Multiset(
    std::initializer_list<Key> const& items)
    : Multiset() {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key, typename Compare, typename Allocator>
Multiset<Key, Compare, Allocator>::Multiset(const Multiset& ms) : Multiset() {
  *this = ms;
}

template <typename Key, typename Compare, typename Allocator>
Multiset<Key, Compare, Allocator>::Multiset(Multiset&& ms)
    : root_(ms.root_), size_(ms.size_) {
  ms.root_ = nullptr;
  ms.size_ = 0;
}

template <typename Key, typename Compare, typename Allocator>
Multiset<Key, Compare, Allocator>::~Multiset() {
  clear(root_);
}

template <typename Key, typename Compare, typename Allocator>
void Multiset<Key, Compare, Allocator>::clear(Node* node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename Key, typename Compare, typename Allocator>
Multiset<Key, Compare, Allocator>& Multiset<Key, Compare, Allocator>::operator=(
    const Multiset& ms) {
  if (this != &ms) {
    clear();
    for (const auto& item : ms) {
      insert(item);
    }
  }
  return *this;
}

template <typename Key, typename Compare, typename Allocator>
Multiset<Key, Compare, Allocator>& Multiset<Key, Compare, Allocator>::operator=(
    Multiset&& ms) {
  if (this != &ms) {
    clear();
    root_ = ms.root_;
    size_ = ms.size_;
    ms.root_ = nullptr;
    ms.size_ = 0;
  }
  return *this;
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::iterator
Multiset<Key, Compare, Allocator>::begin() {
  return iterator(root_);
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::iterator
Multiset<Key, Compare, Allocator>::end() {
  return iterator(nullptr);
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::const_iterator
Multiset<Key, Compare, Allocator>::begin() const {
  return const_iterator(root_);
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::const_iterator
Multiset<Key, Compare, Allocator>::end() const {
  return const_iterator(nullptr);
}

template <typename Key, typename Compare, typename Allocator>
bool Multiset<Key, Compare, Allocator>::empty() const {
  return size_ == 0;
}

template <typename Key, typename Compare, typename Allocator>
size_t Multiset<Key, Compare, Allocator>::size() const {
  return size_;
}

template <typename Key, typename Compare, typename Allocator>
size_t Multiset<Key, Compare, Allocator>::max_size() const {
  return std::allocator_traits<Allocator>::max_size(alloc_);
}

template <typename Key, typename Compare, typename Allocator>
void Multiset<Key, Compare, Allocator>::clear() {
  clear(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename Key, typename Compare, typename Allocator>
void Multiset<Key, Compare, Allocator>::insert(const Key& key) {
  root_ = insert(root_, key);
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::Node*
Multiset<Key, Compare, Allocator>::insert(Node* node, const Key& key) {
  if (!node) {
    size_++;
    return new Node(key);
  }
  if (comp_(key, node->key)) {
    node->left = insert(node->left, key);
  } else {
    node->right = insert(node->right, key);
  }
  return node;
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::Node*
Multiset<Key, Compare, Allocator>::find(Node* node, const Key& key) const {
  if (!node) return nullptr;
  if (comp_(key, node->key)) {
    return find(node->left, key);
  } else if (comp_(node->key, key)) {
    return find(node->right, key);
  }
  return node;
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::iterator
Multiset<Key, Compare, Allocator>::find(const Key& key) {
  return iterator(find(root_, key));
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::const_iterator
Multiset<Key, Compare, Allocator>::find(const Key& key) const {
  return const_iterator(find(root_, key));
}

template <typename Key, typename Compare, typename Allocator>
bool Multiset<Key, Compare, Allocator>::contains(const Key& key) const {
  return find(root_, key) != nullptr;
}

template <typename Key, typename Compare, typename Allocator>
void Multiset<Key, Compare, Allocator>::erase(iterator pos) {
  if (pos != end()) {
    root_ = erase(root_, *pos);
    size_--;
  }
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::Node*
Multiset<Key, Compare, Allocator>::erase(Node* node, const Key& key) {
  if (!node) return nullptr;

  if (comp_(key, node->key)) {
    node->left = erase(node->left, key);
  } else if (comp_(node->key, key)) {
    node->right = erase(node->right, key);
  } else {
    if (!node->left) {
      Node* right_child = node->right;
      delete node;
      return right_child;
    } else if (!node->right) {
      Node* left_child = node->left;
      delete node;
      return left_child;
    } else {
      Node* min_node = find_min(node->right);
      node->key = min_node->key;
      node->right = erase(node->right, min_node->key);
    }
  }
  return node;
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::Node*
Multiset<Key, Compare, Allocator>::find_min(Node* node) const {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename Compare, typename Allocator>
void Multiset<Key, Compare, Allocator>::swap(Multiset& other) {
  Node* temp_root = root_;
  root_ = other.root_;
  other.root_ = temp_root;

  size_type temp_size = size_;
  size_ = other.size_;
  other.size_ = temp_size;
}

template <typename Key, typename Compare, typename Allocator>
void Multiset<Key, Compare, Allocator>::merge(Multiset& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  other.clear();
}

template <typename Key, typename Compare, typename Allocator>
size_t Multiset<Key, Compare, Allocator>::count(const Key& key) const {
  size_t cnt = 0;
  auto node = find(root_, key);
  while (node) {
    cnt++;
    node = find(node->right, key);
  }
  return cnt;
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::Node*
Multiset<Key, Compare, Allocator>::lower_bound(Node* node,
                                               const Key& key) const {
  if (!node) return nullptr;
  if (comp_(node->key, key)) {
    return lower_bound(node->right, key);
  }
  auto left_result = lower_bound(node->left, key);
  return left_result ? left_result : node;
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::iterator
Multiset<Key, Compare, Allocator>::lower_bound(const Key& key) {
  return iterator(lower_bound(root_, key));
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::const_iterator
Multiset<Key, Compare, Allocator>::lower_bound(const Key& key) const {
  return const_iterator(lower_bound(root_, key));
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::Node*
Multiset<Key, Compare, Allocator>::upper_bound(Node* node,
                                               const Key& key) const {
  if (!node) return nullptr;
  if (!comp_(key, node->key)) {
    return upper_bound(node->right, key);
  }
  auto left_result = upper_bound(node->left, key);
  return left_result ? left_result : node;
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::iterator
Multiset<Key, Compare, Allocator>::upper_bound(const Key& key) {
  return iterator(upper_bound(root_, key));
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::const_iterator
Multiset<Key, Compare, Allocator>::upper_bound(const Key& key) const {
  return const_iterator(upper_bound(root_, key));
}

// Методы итератора

template <typename Key, typename Compare, typename Allocator>
void Multiset<Key, Compare, Allocator>::iterator::in_order(Node* node) {
  if (node) {
    in_order(node->left);
    nodes_.push_back(node);
    in_order(node->right);
  }
}

template <typename Key, typename Compare, typename Allocator>
Multiset<Key, Compare, Allocator>::iterator::iterator(Node* root)
    : node_(root), index_(0) {
  in_order(root);
  if (!nodes_.empty()) {
    node_ = nodes_[0];
  }
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::iterator&
Multiset<Key, Compare, Allocator>::iterator::operator++() {
  if (index_ < nodes_.size() - 1) {
    node_ = nodes_[++index_];
  } else {
    node_ = nullptr;
  }
  return *this;
}

template <typename Key, typename Compare, typename Allocator>
Key& Multiset<Key, Compare, Allocator>::iterator::operator*() {
  return node_->key;
}

template <typename Key, typename Compare, typename Allocator>
bool Multiset<Key, Compare, Allocator>::iterator::operator!=(
    const iterator& other) const {
  return node_ != other.node_;
}

// Методы константного итератора

template <typename Key, typename Compare, typename Allocator>
void Multiset<Key, Compare, Allocator>::const_iterator::in_order(Node* node) {
  if (node) {
    in_order(node->left);
    nodes_.push_back(node);
    in_order(node->right);
  }
}

template <typename Key, typename Compare, typename Allocator>
Multiset<Key, Compare, Allocator>::const_iterator::const_iterator(Node* root)
    : node_(root), index_(0) {
  in_order(root);
  if (!nodes_.empty()) {
    node_ = nodes_[0];
  }
}

template <typename Key, typename Compare, typename Allocator>
typename Multiset<Key, Compare, Allocator>::const_iterator&
Multiset<Key, Compare, Allocator>::const_iterator::operator++() {
  if (index_ < nodes_.size() - 1) {
    node_ = nodes_[++index_];
  } else {
    node_ = nullptr;
  }
  return *this;
}

template <typename Key, typename Compare, typename Allocator>
const Key& Multiset<Key, Compare, Allocator>::const_iterator::operator*()
    const {
  return node_->key;
}

template <typename Key, typename Compare, typename Allocator>
bool Multiset<Key, Compare, Allocator>::const_iterator::operator!=(
    const const_iterator& other) const {
  return node_ != other.node_;
}

}  // namespace s21
