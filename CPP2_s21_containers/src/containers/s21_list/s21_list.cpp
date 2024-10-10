//
// Created by Тихон Чабусов on 19.07.2024.
//
// s21_list.cpp

#include "../../include/s21_list/s21_list.hpp"

namespace s21 {

// Конструктор по умолчанию
template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), list_size(0) {}

// Конструктор с размером
template <typename T>
List<T>::List(size_type n) : List() {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
}

// Конструктор со списком инициализации
template <typename T>
List<T>::List(std::initializer_list<T> const &items) : List() {
  for (const T &item : items) {
    push_back(item);
  }
}

// Копирующий конструктор
template <typename T>
List<T>::List(const List &other) : List() {
  for (Node *current = other.head; current != nullptr;
       current = current->next) {
    push_back(current->data);
  }
}

// Конструктор перемещения
template <typename T>
List<T>::List(List &&other)
    : head(other.head), tail(other.tail), list_size(other.list_size) {
  other.head = nullptr;
  other.tail = nullptr;
  other.list_size = 0;
}

// Деструктор
template <typename T>
List<T>::~List() {
  clear();
}

// Оператор присваивания (копирующий)
template <typename T>
List<T> &List<T>::operator=(const List &other) {
  if (this == &other) return *this;
  clear();
  for (Node *current = other.head; current != nullptr;
       current = current->next) {
    push_back(current->data);
  }

  return *this;
}

// Оператор присваивания (перемещающий)
template <typename T>
List<T> &List<T>::operator=(List &&other) {
  if (this == &other) return *this;
  clear();
  head = other.head;
  tail = other.tail;
  list_size = other.list_size;
  other.head = nullptr;
  other.tail = nullptr;
  other.list_size = 0;

  return *this;
}

// Доступ к элементам

template <typename T>
typename List<T>::reference List<T>::front() {
  if (empty()) throw std::out_of_range("List is empty");
  return head->data;
}

template <typename T>
typename List<T>::const_reference List<T>::front() const {
  if (empty()) throw std::out_of_range("List is empty");
  return head->data;
}

template <typename T>
typename List<T>::reference List<T>::back() {
  if (empty()) throw std::out_of_range("List is empty");
  return tail->data;
}

template <typename T>
typename List<T>::const_reference List<T>::back() const {
  if (empty()) throw std::out_of_range("List is empty");
  return tail->data;
}

// Итераторы

template <typename T>
typename List<T>::iterator List<T>::begin() {
  return iterator(head);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
  return const_iterator(head);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const {
  return const_iterator(nullptr);
}

// Вместимость

template <typename T>
bool List<T>::empty() const {
  return list_size == 0;
}

template <typename T>
typename List<T>::size_type List<T>::size() const {
  return list_size;
}

template <typename T>
typename List<T>::size_type List<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

// Модификаторы

template <typename T>
void List<T>::clear() {
  while (head != nullptr) {
    Node *temp = head;
    head = head->next;
    delete temp;
  }
  tail = nullptr;
  list_size = 0;
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  Node *new_node = new Node(value);
  Node *current = pos.get_current();

  if (current == nullptr) {
    if (tail == nullptr) {
      head = tail = new_node;
    } else {
      tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    }
  } else {
    new_node->next = current;
    new_node->prev = current->prev;
    if (current->prev != nullptr) {
      current->prev->next = new_node;
    } else {
      head = new_node;
    }
    current->prev = new_node;
  }

  ++list_size;
  return iterator(new_node);
}

template <typename T>
void List<T>::erase(iterator pos) {
  Node *current = pos.get_current();
  if (current == nullptr) return;

  if (current->prev != nullptr) {
    current->prev->next = current->next;
  } else {
    head = current->next;
  }

  if (current->next != nullptr) {
    current->next->prev = current->prev;
  } else {
    tail = current->prev;
  }

  delete current;
  --list_size;
}

template <typename T>
void List<T>::push_back(const_reference value) {
  Node *new_node = new Node(value);
  if (tail == nullptr) {
    head = tail = new_node;
  } else {
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
  }
  ++list_size;
}

template <typename T>
void List<T>::pop_back() {
  if (tail == nullptr) return;
  Node *temp = tail;
  if (tail->prev != nullptr) {
    tail = tail->prev;
    tail->next = nullptr;
  } else {
    head = tail = nullptr;
  }
  delete temp;
  --list_size;
}

template <typename T>
void List<T>::push_front(const_reference value) {
  Node *new_node = new Node(value);
  if (head == nullptr) {
    head = tail = new_node;
  } else {
    head->prev = new_node;
    new_node->next = head;
    head = new_node;
  }
  ++list_size;
}

template <typename T>
void List<T>::pop_front() {
  if (head == nullptr) return;
  Node *temp = head;
  if (head->next != nullptr) {
    head = head->next;
    head->prev = nullptr;
  } else {
    head = tail = nullptr;
  }
  delete temp;
  --list_size;
}

template <typename T>
void List<T>::swap(List &other) {
  Node *temp_head = head;
  Node *temp_tail = tail;
  size_type temp_size = list_size;

  head = other.head;
  tail = other.tail;
  list_size = other.list_size;

  other.head = temp_head;
  other.tail = temp_tail;
  other.list_size = temp_size;
}

template <typename T>
void List<T>::merge(List &other) {
  if (this == &other) return;
  if (other.empty()) return;

  if (empty()) {
    swap(other);
    return;
  }

  Node *this_current = head;
  Node *other_current = other.head;
  while (this_current != nullptr && other_current != nullptr) {
    if (other_current->data < this_current->data) {
      Node *next_other = other_current->next;
      other_current->prev = this_current->prev;
      other_current->next = this_current;

      if (this_current->prev != nullptr) {
        this_current->prev->next = other_current;
      } else {
        head = other_current;
      }

      this_current->prev = other_current;
      other_current = next_other;
    } else {
      this_current = this_current->next;
    }
  }

  if (other_current != nullptr) {
    tail->next = other_current;
    other_current->prev = tail;
    tail = other.tail;
  }

  list_size += other.list_size;
  other.head = other.tail = nullptr;
  other.list_size = 0;
}

template <typename T>
void List<T>::splice(const_iterator pos, List &other) {
  if (this == &other) return;
  if (other.empty()) return;

  Node *current = pos.get_current();
  if (current == nullptr) {
    if (tail == nullptr) {
      head = other.head;
    } else {
      tail->next = other.head;
      other.head->prev = tail;
    }
    tail = other.tail;
  } else {
    if (current->prev != nullptr) {
      current->prev->next = other.head;
      other.head->prev = current->prev;
    } else {
      head = other.head;
    }
    other.tail->next = current;
    current->prev = other.tail;
  }

  list_size += other.list_size;
  other.head = other.tail = nullptr;
  other.list_size = 0;
}

template <typename T>
void List<T>::reverse() {
  if (empty()) return;

  Node *current = head;
  Node *temp = nullptr;

  while (current != nullptr) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  temp = head;
  head = tail;
  tail = temp;
}

template <typename T>
void List<T>::unique() {
  if (empty()) return;

  Node *current = head;
  while (current != nullptr && current->next != nullptr) {
    if (current->data == current->next->data) {
      Node *temp = current->next;
      current->next = temp->next;
      if (temp->next != nullptr) {
        temp->next->prev = current;
      } else {
        tail = current;
      }
      delete temp;
      --list_size;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void List<T>::sort() {
  if (list_size < 2) return;
  bool swapped;
  do {
    swapped = false;
    for (Node *i = head; i != nullptr && i->next != nullptr; i = i->next) {
      if (i->data > i->next->data) {
        std::swap(i->data, i->next->data);
        swapped = true;
      }
    }
  } while (swapped);
}

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  Node *current = pos.get_current();

  (void)std::initializer_list<int>{
      (insert_before(current, std::forward<Args>(args)), 0)...};

  return iterator(current ? current->prev : tail);
}

template <typename... Args>
void insert_many_back(Args &&...args) {
  (void)std::initializer_list<int>{(push_back(std::forward<Args>(args)), 0)...};
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_front(Args &&...args) {
  (void)std::initializer_list<int>{
      (push_front(std::forward<Args>(args)), 0)...};
}

}  // namespace s21