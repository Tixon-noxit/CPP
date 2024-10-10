//
// Created by Тихон Чабусов on 5.08.2024.
//

#ifndef S21_SET_HPP
#define S21_SET_HPP

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <stack>

#include "../s21_vector/s21_vector.hpp"

namespace s21 {

template <typename Key>
class Set;  // Forward declaration of Set class

template <typename Key>
class SetIterator {
 private:
  using Node = typename Set<Key>::Node;
  Node* current;
  std::stack<Node*> ancestors;

  void pushLeft(Node* node);

 public:
  SetIterator();
  explicit SetIterator(Node* root);
  SetIterator& operator++();
  SetIterator operator++(int);
  Key& operator*();
  Key* operator->();
  bool operator==(const SetIterator& other) const;
  bool operator!=(const SetIterator& other) const;
  Node* get_current() const;
};

template <typename Key>
class SetConstIterator {
 private:
  using Node = typename Set<Key>::Node;
  const Node* current;
  std::stack<const Node*> ancestors;

  void pushLeft(const Node* node);

 public:
  SetConstIterator();
  explicit SetConstIterator(const Node* root);
  SetConstIterator& operator++();
  SetConstIterator operator++(int);
  const Key& operator*() const;
  const Key* operator->() const;
  bool operator==(const SetConstIterator& other) const;
  bool operator!=(const SetConstIterator& other) const;
  const Node* get_current() const;
};

template <typename Key>
class Set {
 private:
  struct Node {
    Key key;
    Node* left;
    Node* right;

    explicit Node(const Key& key) : key(key), left(nullptr), right(nullptr) {}
  };

  Node* root;
  size_t tree_size;

  // Utility functions
  Node* copyTree(Node* other);
  void deleteTree(Node* node);
  std::pair<Node*, bool> insertNode(Node*& node, const Key& key);
  Node* findNode(Node* node, const Key& key) const;
  void inorder(Node* node, std::function<void(Node*)> func) const;

 public:
  friend class SetIterator<Key>;
  friend class SetConstIterator<Key>;

  // Переопределения типов
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = SetIterator<Key>;
  using const_iterator = SetConstIterator<Key>;
  using size_type = size_t;

  // Конструкторы
  Set();
  Set(std::initializer_list<value_type> const& items);
  Set(const Set& s);
  Set(Set&& s) noexcept;
  ~Set();

  // Доступ к элементам
  Set& operator=(const Set& s);
  Set& operator=(Set&& s) noexcept;

  // Итераторы
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // Вместимость
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Модификаторы
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(Set& other);
  void merge(Set& other);

  // Просмотр контейнера
  iterator find(const key_type& key);
  bool contains(const key_type& key) const;

  template <typename... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

}  // namespace s21

#endif  // S21_SET_HPP
