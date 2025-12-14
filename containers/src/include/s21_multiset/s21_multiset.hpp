//
// Created by Тихон Чабусов on 29.07.2024.
//

#ifndef CPP2_S21_CONTAINERS_1_S21_MULTISET_HPP
#define CPP2_S21_CONTAINERS_1_S21_MULTISET_HPP

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <memory>

#include "../s21_vector/s21_vector.hpp"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class Multiset {
 private:
  struct Node {
    Key key;
    Node *left;
    Node *right;

    explicit Node(const Key &k) : key(k), left(nullptr), right(nullptr) {}
  };

  Node *root_;
  size_t size_;
  Compare comp_;
  Allocator alloc_;

  void clear(Node *node);
  // Вставляет ключ в дерево, начиная с указанного узла
  Node *insert(Node *node, const Key &key);

  // Находит узел с заданным ключом, начиная с указанного узла (константная
  // версия)
  Node *find(Node *node, const Key &key) const;

  // Находит первый узел не меньший, чем заданный ключ, начиная с указанного
  // узла (константная версия)
  Node *lower_bound(Node *node, const Key &key) const;

  // Находит первый узел больший, чем заданный ключ, начиная с указанного узла
  // (константная версия)
  Node *upper_bound(Node *node, const Key &key) const;

  // Выполняет обход дерева в порядке возрастания и сохраняет ключи в векторе
  void in_order_traversal(Node *node, Vector<Key> &elements) const;

  // Удаляет узел с заданным ключом, начиная с указанного узла
  Node *erase(Node *node, const Key &key);

  // Находит узел с минимальным ключом, начиная с указанного узла
  Node *find_min(Node *node) const;

 public:
  using key_type = Key;
  using value_type = Key;  // мультимножество хранит только ключи
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  // Вложенный класс итератора
  class iterator {
   private:
    Node *node_;  // Указатель на текущий узел, на который указывает итератор
    Vector<Node *>
        nodes_;  // Вектор узлов для хранения обхода в порядке возрастания
    size_t index_;  // Индекс текущего узла в векторе узлов

    // Выполняет обход дерева в порядке возрастания и заполняет вектор узлов
    void in_order(Node *node);

   public:
    // Конструктор итератора, начинающий с корня дерева
    explicit iterator(Node *root);

    // Оператор постфиксного инкремента итератора
    iterator &operator++();

    // Оператор разыменования итератора для доступа к ключу
    Key &operator*();

    // Оператор сравнения итераторов на неравенство
    bool operator!=(const iterator &other) const;
  };

  // Вложенный класс константного итератора
  class const_iterator {
   private:
    Node *node_;
    Vector<Node *> nodes_;
    size_t index_;

    void in_order(Node *node);

   public:
    explicit const_iterator(Node *root);

    const_iterator &operator++();

    const Key &operator*() const;

    bool operator!=(const const_iterator &other) const;
  };

  // Конструкторы

  Multiset();

  Multiset(std::initializer_list<Key> const
               &items); /* конструктор списка инициализаторов, создает
          контейнер, инициализированный с использованием std::initializer_list
          */

  Multiset(const Multiset &ms);  // копирующий конструктор
  Multiset(Multiset &&ms);  // конструктор перемещения
  ~Multiset();              // Деструктор

  Multiset &operator=(const Multiset &ms);  // Оператор присваивания
  Multiset &operator=(Multiset &&ms);  // Оператор присваивания

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
  void insert(
      const Key &key);  // вставляет элемент в конкретную позицию и возвращает
  // итератор, указывающий на новый элемент
  void erase(iterator pos);  // стирает элемент в позиции pos
  void swap(Multiset &other);  // Заменяет содержимое контейнера содержимым x,
  // которое является другим списком того же типа.
  // Размеры могут отличаться.
  void merge(Multiset &other);  // объединяет два отсортированных контейнера

  size_type count(const Key &key) const;  // Подсчитывает количество элементов с
  // заданным ключом в мультимножестве
  iterator find(const Key &key);  // Находит первый элемент с заданным ключом в
  // мультимножестве
  const_iterator find(const Key &key)
      const;  // Находит первый элемент с заданным ключом в мультимножестве
  bool contains(const Key &key)
      const;  // Проверяет наличие элемента с заданным ключом в мультимножестве
  std::pair<iterator, iterator> equal_range(
      const Key &key);  // Возвращает диапазон элементов с заданным ключом в
  // мультимножестве
  iterator lower_bound(
      const Key &key);  // Возвращает итератор на первый элемент не меньший, чем
  // заданный ключ
  const_iterator lower_bound(
      const Key &key) const;  // Возвращает итератор на первый элемент не
  // меньший, чем заданный ключ
  iterator upper_bound(const Key &key);  // Возвращает итератор на первый
  // элемент больший, чем заданный ключ
  const_iterator upper_bound(
      const Key &key) const;  // Возвращает итератор на первый элемент больший,
                              // чем заданный ключ

  template <typename... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    Vector<std::pair<iterator, bool>> result;
    (result.emplace_back(insert(std::forward<Args>(args))), ...);
    return result;
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_S21_MULTISET_HPP
