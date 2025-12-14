//
// Created by Тихон Чабусов on 27.07.2024.
//

#include "../../include/s21_map/s21_map.hpp"

#include <vector>

namespace s21 {

template <typename Key, typename T>
Map<Key, T>::Map() : root(nullptr), node_count(0) {}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const& items) : Map() {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map& other) : Map() {
  for (const auto& item : other) {
    insert(item);
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(Map&& other) noexcept
    : root(other.root), node_count(other.node_count) {
  other.root = nullptr;
  other.node_count = 0;
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
  clear(root);
}

template <typename Key, typename T>
Map<Key, T>& Map<Key, T>::operator=(Map&& other) noexcept {
  if (this != &other) {
    clear();
    root = other.root;
    node_count = other.node_count;
    other.root = nullptr;
    other.node_count = 0;
  }
  return *this;
}

template <typename Key, typename T>
T& Map<Key, T>::at(const Key& key) {
  Node* node = findNode(key);
  if (!node) {
    throw std::out_of_range("Key not found");
  }
  return node->data.second;
}

template <typename Key, typename T>
T& Map<Key, T>::operator[](const Key& key) {
  return insert(std::make_pair(key, T())).first->second;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  return iterator(findMin(root), root);
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  return iterator(nullptr, root);
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::begin() const {
  return const_iterator(findMin(root), root);
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::end() const {
  return const_iterator(nullptr, root);
}

template <typename Key, typename T>
bool Map<Key, T>::empty() const {
  return node_count == 0;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::size() const {
  return node_count;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename Key, typename T>
void Map<Key, T>::clear() {
  clear(root);
  root = nullptr;
  node_count = 0;
}

template <typename Key, typename T>
void Map<Key, T>::clear(Node* node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const value_type& value) {
  return insert(value.first, value.second);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const Key& key, const T& obj) {
  Node* parent = nullptr;
  Node* current = root;

  while (current) {
    if (key == current->data.first) {
      return std::make_pair(iterator(current, root), false);
    }

    parent = current;
    if (key < current->data.first) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  Node* new_node = new Node(std::make_pair(key, obj));
  new_node->parent = parent;

  if (!parent) {
    root = new_node;
  } else if (key < parent->data.first) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }

  ++node_count;
  return std::make_pair(iterator(new_node, root), true);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  auto result = insert(key, obj);
  if (!result.second) {
    result.first->second = obj;
  }
  return result;
}

template <typename Key, typename T>
void Map<Key, T>::erase(iterator pos) {
  Node* node = pos.getCurrent();
  if (!node) {
    return;
  }

  // У узла нет потомков
  if (!node->left && !node->right) {
    if (node->parent) {
      if (node->parent->left == node) {
        node->parent->left = nullptr;
      } else {
        node->parent->right = nullptr;
      }
    } else {
      root = nullptr;  // Node is root
    }
  }
  // У узла 1 потомок
  else if (!node->left || !node->right) {
    Node* child = node->left ? node->left : node->right;
    if (node->parent) {
      if (node->parent->left == node) {
        node->parent->left = child;
      } else {
        node->parent->right = child;
      }
    } else {
      root = child;  // Node is root
    }
    child->parent = node->parent;
  }
  // У узла 2 потомка
  else {
    Node* successor = findMin(node->right);

    // Повторная связка узлов (взамен копирования)
    if (successor->parent->left == successor) {
      successor->parent->left = successor->right;
    } else {
      successor->parent->right = successor->right;
    }
    if (successor->right) {
      successor->right->parent = successor->parent;
    }

    // Обновление данных узла
    node->data.~value_type();
    new (&node->data) value_type(std::move(successor->data));

    node = successor;
  }

  delete node;
  --node_count;
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map& other) {
  Node* tempRoot = root;
  root = other.root;
  other.root = tempRoot;

  size_t tempNodeCount = node_count;
  node_count = other.node_count;
  other.node_count = tempNodeCount;
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  other.clear();
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key& key) const {
  return findNode(key) != nullptr;
}

template <typename Key, typename T>
typename Map<Key, T>::Node* Map<Key, T>::findNode(const Key& key) const {
  Node* current = root;
  while (current) {
    if (key == current->data.first) {
      return current;
    }
    if (key < current->data.first) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return nullptr;
}

template <typename Key, typename T>
typename Map<Key, T>::Node* Map<Key, T>::findMin(Node* node) const {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename T>
const typename Map<Key, T>::Node* Map<Key, T>::MapConstIterator::findMin(
    const Node* node) const {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::find(const Key& key) {
  Node* node = findNodeForTesting(key);
  if (node) {
    return iterator(node, root);
  } else {
    return end();
  }
}

template <typename Key, typename Value>
template <typename... Args>
Vector<std::pair<typename Map<Key, Value>::iterator, bool>>
Map<Key, Value>::insert_many(Args&&... args) {
  Vector<std::pair<iterator, bool>> results;
  (results.push_back(insert(std::forward<Args>(args))), ...);
  return results;
}

}  // namespace s21
