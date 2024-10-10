//
// Created by Тихон Чабусов on 05.08.2024.
//

#include "../../include/s21_set/s21_set.hpp"

#include <functional>
#include <stack>
#include <vector>

namespace s21 {

template <typename Key>
typename Set<Key>::Node* Set<Key>::copyTree(Node* other) {
  if (!other) return nullptr;
  Node* newNode = new Node(other->key);
  newNode->left = copyTree(other->left);
  newNode->right = copyTree(other->right);
  return newNode;
}

template <typename Key>
void Set<Key>::deleteTree(Node* node) {
  if (!node) return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

template <typename Key>
std::pair<typename Set<Key>::Node*, bool> Set<Key>::insertNode(Node*& node,
                                                               const Key& key) {
  if (!node) {
    node = new Node(key);
    return {node, true};
  }
  if (key < node->key) {
    return insertNode(node->left, key);
  } else if (key > node->key) {
    return insertNode(node->right, key);
  }
  return {node, false};
}

template <typename Key>
typename Set<Key>::Node* Set<Key>::findNode(Node* node, const Key& key) const {
  if (!node || node->key == key) return node;
  if (key < node->key) return findNode(node->left, key);
  return findNode(node->right, key);
}

template <typename Key>
void Set<Key>::inorder(Node* node, std::function<void(Node*)> func) const {
  if (!node) return;
  inorder(node->left, func);
  func(node);
  inorder(node->right, func);
}

// Конструкторы

template <typename Key>
Set<Key>::Set() : root(nullptr), tree_size(0) {}

template <typename Key>
Set<Key>::Set(std::initializer_list<value_type> const& items) : Set() {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
Set<Key>::Set(const Set& s) : root(copyTree(s.root)), tree_size(s.tree_size) {}

template <typename Key>
Set<Key>::Set(Set&& s) noexcept : root(s.root), tree_size(s.tree_size) {
  s.root = nullptr;
  s.tree_size = 0;
}

template <typename Key>
Set<Key>::~Set() {
  deleteTree(root);
}

// Операторы присваивания
template <typename Key>
Set<Key>& Set<Key>::operator=(const Set& s) {
  if (this == &s) return *this;
  deleteTree(root);
  root = copyTree(s.root);
  tree_size = s.tree_size;
  return *this;
}

template <typename Key>
Set<Key>& Set<Key>::operator=(Set&& s) noexcept {
  if (this == &s) return *this;
  deleteTree(root);
  root = s.root;
  tree_size = s.tree_size;
  s.root = nullptr;
  s.tree_size = 0;
  return *this;
}

// Итераторы

template <typename Key>
typename Set<Key>::iterator Set<Key>::begin() {
  return iterator(root);
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::end() {
  return iterator();
}

template <typename Key>
typename Set<Key>::const_iterator Set<Key>::begin() const {
  return const_iterator(root);
}

template <typename Key>
typename Set<Key>::const_iterator Set<Key>::end() const {
  return const_iterator();
}

// Вместимость

template <typename Key>
bool Set<Key>::empty() const {
  return tree_size == 0;
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::size() const {
  return tree_size;
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::max_size() const {
  return ~(static_cast<size_type>(0));
}

template <typename Key>
typename Set<Key>::Node* SetIterator<Key>::get_current() const {
  return current;
}

template <typename Key>
const typename Set<Key>::Node* SetConstIterator<Key>::get_current() const {
  return current;
}

// Модификаторы

template <typename Key>
void Set<Key>::clear() {
  deleteTree(root);
  root = nullptr;
  tree_size = 0;
}

template <typename Key>
std::pair<typename Set<Key>::iterator, bool> Set<Key>::insert(
    const value_type& value) {
  auto result = insertNode(root, value);
  if (result.second) ++tree_size;
  return {iterator(result.first), result.second};
}

template <typename Key>
void Set<Key>::erase(iterator pos) {
  Node* node = pos.get_current();
  if (!node) return;

  // Лямбда-функция :)
  std::function<Node*(Node*, Node*)> eraseNode =
      [&](Node* root, Node* nodeToDelete) -> Node* {
    if (!root) return root;

    if (nodeToDelete->key < root->key) {
      root->left = eraseNode(root->left, nodeToDelete);
    } else if (nodeToDelete->key > root->key) {
      root->right = eraseNode(root->right, nodeToDelete);
    } else {
      if (!root->left) {
        Node* temp = root->right;
        delete root;
        return temp;
      } else if (!root->right) {
        Node* temp = root->left;
        delete root;
        return temp;
      }

      Node* temp = root->right;
      while (temp && temp->left != nullptr) {
        temp = temp->left;
      }
      if (temp) {
        root->key = temp->key;
        root->right = eraseNode(root->right, temp);
      }
    }
    return root;
  };

  eraseNode(root, node);
  --tree_size;
}

template <typename Key>
void Set<Key>::swap(Set& other) {
  Node* tempRoot = root;
  root = other.root;
  other.root = tempRoot;

  size_type tempSize = tree_size;
  tree_size = other.tree_size;
  other.tree_size = tempSize;
}

template <typename Key>
void Set<Key>::merge(Set& other) {
  for (iterator it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  other.clear();
}

// Просмотр контейнера

template <typename Key>
typename Set<Key>::iterator Set<Key>::find(const key_type& key) {
  return iterator(findNode(root, key));
}

template <typename Key>
bool Set<Key>::contains(const key_type& key) const {
  return findNode(root, key) != nullptr;
}

// SetIterator

template <typename Key>
void SetIterator<Key>::pushLeft(Node* node) {
  while (node) {
    ancestors.push(node);
    node = node->left;
  }
}

template <typename Key>
SetIterator<Key>::SetIterator() : current(nullptr) {}

template <typename Key>
SetIterator<Key>::SetIterator(Node* root) : current(nullptr) {
  pushLeft(root);
  if (!ancestors.empty()) {
    current = ancestors.top();
    ancestors.pop();
  }
}

template <typename Key>
SetIterator<Key>& SetIterator<Key>::operator++() {
  if (current->right) {
    pushLeft(current->right);
  }
  if (!ancestors.empty()) {
    current = ancestors.top();
    ancestors.pop();
  } else {
    current = nullptr;
  }
  return *this;
}

template <typename Key>
SetIterator<Key> SetIterator<Key>::operator++(int) {
  SetIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key>
Key& SetIterator<Key>::operator*() {
  return current->key;
}

template <typename Key>
Key* SetIterator<Key>::operator->() {
  return &(current->key);
}

template <typename Key>
bool SetIterator<Key>::operator==(const SetIterator& other) const {
  return current == other.current;
}

template <typename Key>
bool SetIterator<Key>::operator!=(const SetIterator& other) const {
  return current != other.current;
}

// SetConstIterator
template <typename Key>
void SetConstIterator<Key>::pushLeft(const Node* node) {
  while (node) {
    ancestors.push(node);
    node = node->left;
  }
}

template <typename Key>
SetConstIterator<Key>::SetConstIterator() : current(nullptr) {}

template <typename Key>
SetConstIterator<Key>::SetConstIterator(const Node* root) : current(nullptr) {
  pushLeft(root);
  if (!ancestors.empty()) {
    current = ancestors.top();
    ancestors.pop();
  }
}

template <typename Key>
SetConstIterator<Key>& SetConstIterator<Key>::operator++() {
  if (current->right) {
    pushLeft(current->right);
  }
  if (!ancestors.empty()) {
    current = ancestors.top();
    ancestors.pop();
  } else {
    current = nullptr;
  }
  return *this;
}

template <typename Key>
SetConstIterator<Key> SetConstIterator<Key>::operator++(int) {
  SetConstIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key>
const Key& SetConstIterator<Key>::operator*() const {
  return current->key;
}

template <typename Key>
const Key* SetConstIterator<Key>::operator->() const {
  return &(current->key);
}

template <typename Key>
bool SetConstIterator<Key>::operator==(const SetConstIterator& other) const {
  return current == other.current;
}

template <typename Key>
bool SetConstIterator<Key>::operator!=(const SetConstIterator& other) const {
  return current != other.current;
}

template <typename Key>
template <typename... Args>
Vector<std::pair<typename Set<Key>::iterator, bool>> Set<Key>::insert_many(
    Args&&... args) {
  Vector<std::pair<iterator, bool>> results;
  (results.push_back(insert(std::forward<Args>(args))), ...);
  return results;
}

}  // namespace s21
