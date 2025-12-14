//
// Created by Тихон Чабусов on 13.07.2024.
//

#ifndef S21_LIST_HPP
#define S21_LIST_HPP

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class List {
 public:
  using value_type = T;  // определяет тип элемента (T — параметр шаблона)
  using reference = value_type &;  // определяет тип ссылки на элемент
  using const_reference =
      const value_type &;  // определяет тип ссылки на константу
  using size_type = std::size_t;  // size_t определяет тип размера контейнера
                                  // (стандартный тип — size_t)

 private:
  struct Node {
    value_type data;
    Node *next;
    Node *prev;

    explicit Node(const value_type &data)
        : data(data), next(nullptr), prev(nullptr) {}
  };

  Node *head;
  Node *tail;
  size_type list_size;

 public:
  // Вложенный класс итератора
  // определяет тип для перебора контейнера
  class ListIterator {
   private:
    Node *current;

   public:
    explicit ListIterator(Node *node) : current(node) {}

    ListIterator &operator++() {
      current = current->next;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator temp = *this;
      ++(*this);
      return temp;
    }

    ListIterator &operator--() {
      current = current->prev;
      return *this;
    }

    bool operator==(const ListIterator &other) const {
      return current == other.current;
    }

    bool operator!=(const ListIterator &other) const {
      return current != other.current;
    }

    value_type &operator*() const { return current->data; }

    Node *get_current() const { return current; }
  };

  // Вложенный класс константного итератора
  // определяет тип константы для итерации по контейнеру
  class ListConstIterator {
   private:
    const Node *current;

   public:
    explicit ListConstIterator(const Node *node) : current(node) {}

    ListConstIterator &operator++() {
      current = current->next;
      return *this;
    }

    ListConstIterator operator++(int) {
      ListConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    ListConstIterator &operator--() {
      current = current->prev;
      return *this;
    }

    bool operator==(const ListConstIterator &other) const {
      return current == other.current;
    }

    bool operator!=(const ListConstIterator &other) const {
      return current != other.current;
    }

    const value_type &operator*() const { return current->data; }
  };

  using iterator = class ListIterator;
  using const_iterator = class ListConstIterator;

  // Метод insert_many
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

 private:
  void insert_before(Node *&pos, const T &value) {
    Node *new_node = new Node(value);
    new_node->next = pos;
    new_node->prev = pos ? pos->prev : nullptr;
    if (pos) {
      if (pos->prev) pos->prev->next = new_node;
      pos->prev = new_node;
    } else {
      if (tail) tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    }
    if (pos == head) head = new_node;
    pos = new_node;
    ++list_size;
  }

  void insert_before(Node *&pos, T &&value) {
    Node *new_node = new Node(std::move(value));
    new_node->next = pos;
    new_node->prev = pos ? pos->prev : nullptr;
    if (pos) {
      if (pos->prev) pos->prev->next = new_node;
      pos->prev = new_node;
    } else {
      if (tail) tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    }
    if (pos == head) head = new_node;
    pos = new_node;
    ++list_size;
  }

 public:
  // Конструкторы

  List();

  explicit List(
      size_type n);  // параметризованный конструктор, создает список размера n
  List(std::initializer_list<value_type> const
           &items); /* конструктор списка инициализаторов, создает список,
                       инициализированный с использованием std::initializer_list
                     */
  List(const List &other);  // копирующий конструктор
  List(List &&other);       // конструктор перемещения
  ~List();                  // Деструктор
  List &operator=(const List &other);  // Оператор присваивания
  List &operator=(List &&other);  // Оператор присваивания

  // Доступ к элементам

  reference front();  // доступ к первому элементу
  const_reference front() const;  // доступ к первому элементу
  reference back();  // доступ к последнему элементу
  const_reference back() const;  // доступ к последнему элементу

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
  iterator insert(iterator pos,
                  const_reference value);  // вставляет элемент в конкретную

  // Метод insert_many_front
  template <typename... Args>
  void insert_many_front(Args &&...args);

  // Метод insert_many_back
  template <typename... Args>
  void insert_many_back(Args &&...args);

  // позицию и возвращает итератор,
  // указывающий на новый элемент
  void erase(iterator pos);  // стирает элемент в позиции pos
  void push_back(const_reference value);  // добавляет элемент в конец
  void pop_back();  // удаляет последний элемент
  void push_front(const_reference value);  // добавляет элемент в начало
  void pop_front();        // удаляет первый элемент
  void swap(List &other);  // Заменяет содержимое контейнера содержимым x,
  // которое является другим списком того же типа.
  // Размеры могут отличаться.
  void merge(List &other);  // объединяет два отсортированных списка
  void splice(const_iterator pos,
              List &other);  //  вставка всех элементов из одного списка (other)
  //  в другой список (this) на заданную позицию
  void reverse();  // меняет порядок элементов
  void unique();  // удаления дубликатов из отсортированного двусвязного списка
  void sort();    // сортирует элементы
};

}  // namespace s21

#endif  // S21_LIST_HPP