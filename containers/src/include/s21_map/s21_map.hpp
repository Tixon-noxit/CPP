//
// Created by Тихон Чабусов on 27.07.2024.
//

#ifndef CPP2_S21_CONTAINERS_1_S21_MAP_HPP
#define CPP2_S21_CONTAINERS_1_S21_MAP_HPP

#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

#include "../s21_vector/s21_vector.hpp"

namespace s21 {

template <typename Key, typename T>
class Map {
 public:
  using key_type = Key;   // первый параметр шаблона
  using mapped_type = T;  // второй параметр шаблона
  using value_type =
      std::pair<const key_type,
                mapped_type>;  // определяет тип элемента (T — параметр шаблона)
  using reference = value_type&;  // определяет тип ссылки на элемент
  using const_reference =
      const value_type&;  // определяет тип ссылки на константу
  using size_type = std::size_t;  // size_t определяет тип размера контейнера
                                  // (стандартный тип — size_t)

 private:
  struct Node {
    value_type data;
    Node* left;
    Node* right;
    Node* parent;

    explicit Node(const value_type& value)
        : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
  };

  Node* root;
  size_type node_count;

 public:
  // Вложенный класс итератора
  // определяет тип для перебора контейнера
  class MapIterator {
   private:
    Node* current;
    Node* root;

    // возвращает узел с минимальным ключом в поддереве
    Node* findMin(Node* node) {
      while (node && node->left) {
        node = node->left;
      }
      return node;
    }

    // возвращает узел, который является последующим узлом в порядке обхода
    // дерева для node
    Node* findNext(Node* node) {
      if (node->right) {
        return findMin(node->right);
      }

      Node* parent = node->parent;
      while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }

   public:
    explicit MapIterator(Node* node, Node* root) : current(node), root(root) {}

    // перемещает итератор на следующий элемент
    MapIterator& operator++() {
      current = findNext(current);
      return *this;
    }

    // перемещает итератор на следующий элемент в контейнере, но возвращает
    // значение итератора до его перемещения
    MapIterator operator++(int) {
      MapIterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const MapIterator& other) const {
      return current == other.current;
    }

    bool operator!=(const MapIterator& other) const {
      return !operator==(other);
    }

    // оператор разыменования
    reference operator*() const { return current->data; }

    Node* getCurrent() const { return current; }

    value_type* operator->() const { return &(current->data); }
  };

  // Вложенный класс константного итератора
  // определяет тип константы для итерации по контейнеру
  class MapConstIterator {
   private:
    const Node* current;
    const Node* root;

   public:
    explicit MapConstIterator(const Node* node, const Node* root)
        : current(node), root(root) {}

    MapConstIterator& operator++() {
      current = findNext(current);
      return *this;
    }

    MapConstIterator operator++(int) {
      MapConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const MapConstIterator& other) const {
      return current == other.current;
    }

    bool operator!=(const MapConstIterator& other) const {
      return !operator==(other);
    }

    const_reference operator*() const { return current->data; }

   private:
    const Node* findMin(const Node* node) const;

    const Node* findNext(const Node* node) const {
      if (node->right) {
        return findMin(node->right);
      }

      const Node* parent = node->parent;
      while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }
  };

  using iterator = MapIterator;
  using const_iterator = MapConstIterator;

  // Конструкторы

  Map();
  Map(std::initializer_list<value_type> const&
          items); /* конструктор списка инициализаторов, создает список,
инициализированный с использованием std::initializer_list
*/
  Map(const Map& other);      // копирующий конструктор
  Map(Map&& other) noexcept;  // конструктор перемещения

  ~Map();  // Деструктор

  Map& operator=(Map&& other) noexcept;  // Оператор присваивания

  // Доступ к элементам

  T& at(const Key& key);  // доступ к указанному элементу с проверкой границ
  T& operator[](
      const Key& key);  // получить доступ или вставить указанный элемент

  // Итераторы

  iterator begin();  // возвращает итератор, указывающий на начало списка
  iterator end();  // возвращает итератор, указывающий на конец списка
  const_iterator begin()
      const;  // возвращает итератор, указывающий на начало списка
  const_iterator end()
      const;  // возвращает итератор, указывающий на конец списка

  // Вместимость

  bool empty() const;  // проверяет, пуст ли контейнер
  size_type size() const;  // возвращает количество элементов
  size_type max_size()
      const;  // возвращает максимально возможное количество элементов

  // Модификаторы

  void clear();  // очищает содержимое контейнера
  std::pair<iterator, bool> insert(
      const value_type&
          value);  // вставляет значение по ключу и возвращает итератор туда,
                   // где находится элемент в контейнере, и логическое значение,
                   // обозначающее, имела ли место вставка.
  std::pair<iterator, bool> insert(
      const Key& key,
      const T& obj);  // вставляет значение по ключу и возвращает итератор туда,
                      // где находится элемент в контейнере, и логическое
                      // значение, обозначающее, имела ли место вставка.
  std::pair<iterator, bool> insert_or_assign(
      const Key& key, const T& obj);  // удаляет из контейнера либо один
                                      // элемент, либо диапазон элементов.
  void erase(iterator pos);  // стирает элемент в позиции pos
  void swap(Map& other);  // заменяет содержимое контейнера содержимым x,
                          // которое является другим списком того же типа.
                          // Размеры могут отличаться.
  void merge(Map& other);  // объединяет два контейнера map

  // Просмотр контейнера

  bool contains(const Key& key)
      const;  // проверяет, есть ли в контейнере элемент с ключом key
  void custom_swap(T& a, T& b);

  // Вспомогательные методы

  Node* findNodeForTesting(const Key& key) const { return findNode(key); }
  iterator find(const Key& key);

  template <typename... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  Node* findNode(const Key& key) const;
  Node* findMin(Node* node) const;
  void clear(Node* node);
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_S21_MAP_HPP
