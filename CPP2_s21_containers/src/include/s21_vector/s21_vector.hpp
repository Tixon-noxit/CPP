//
// Created by Тихон Чабусов on 25.07.2024.
//

#ifndef S21_VECTOR_HPP
#define S21_VECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {

template <typename T>
class Vector {
 public:
  using value_type = T;  // определяет тип элемента (T — параметр шаблона)
  using reference = T&;  // определяет тип ссылки на элемент
  using const_reference = const T&;  // определяет тип ссылки на константу
  using iterator = T*;  // итерация по контейнеру
  using const_iterator = const T*;  // константа для итерации по контейнеру
  using size_type = std::size_t;  // size_t определяет тип размера контейнера
                                  // (стандартный тип — size_t)

 private:
  T* data_;
  size_type size_;
  size_type capacity_;

  void reallocate(size_type new_capacity);

 public:
  // Конструкторы

  Vector();
  explicit Vector(
      size_type n);  // параметризованный конструктор, создает вектор размера n
  Vector(std::initializer_list<value_type> const&
             items); /* конструктор списка инициализаторов, создает список,
                        инициализированный с использованием
                        std::initializer_list */
  Vector(const Vector& other);  // копирующий конструктор
  Vector(Vector&& other) noexcept;  // конструктор перемещения
  Vector& operator=(Vector&& other) noexcept;  // Оператор присваивания
  ~Vector();                                   // Деструктор

  // Доступ к элементам

  reference at(
      size_type pos);  // доступ к указанному элементу с проверкой границ
  reference operator[](size_type pos);  // доступ к указанному элементу
  const_reference front();  // доступ к первлму элементу
  const_reference back();  // доступ к последнему элементу
  T* data();  // прямой доступ к базовому массиву

  // Итераторы

  iterator begin() { return data_; };  // перемещает итератор в начало
  iterator end() { return data_ + size_; };  // перемещает итератор в конец
  const_iterator begin() const;  // перемещает итератор в начало
  const_iterator end() const;  // перемещает итератор в конец

  // Вместимость

  bool empty();      // проверяет, пуст ли контейнер
  size_type size();  // возвращает количество элементов
  size_type
  max_size();  // возвращает максимально возможное количество элементов
  void reserve(size_type new_cap);  // выделяет память для указанного количества
                                    // элементов и копирует текущие элементы
                                    // массива в новый массив
  size_type capacity();  // возвращает количество элементов, которые могут
                         // храниться в выделенной на данный момент памяти
  void shrink_to_fit();  // уменьшает использование памяти за счет освобождения
                         // неиспользуемой памяти

  // Модификаторы

  void clear();  // очищает содержимое контейнера
  iterator insert(iterator pos,
                  const_reference value);  // вставляет элемент в конкретную
                                           // позицию и возвращает итератор,
                                           // указывающий на новый элемент
  void erase(iterator pos);  // стирает элемент в позиции pos
  void push_back(const_reference value);  // добавляет элемент в конец
  void pop_back();           // удаляет последний элемент
  void swap(Vector& other);  // Заменяет содержимое контейнера содержимым x,
                             // которое является другим векторным объектом того
                             // же типа. Размеры могут отличаться

  // Метод insert_many
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    size_type index = pos - data_;
    size_type count = sizeof...(args);

    if (size_ + count > capacity_) {
      reserve(size_ + count);
    }

    T* insert_pos = data_ + index;
    std::move_backward(insert_pos, data_ + size_, data_ + size_ + count);

    (void)std::initializer_list<int>{
        (new (insert_pos++) T(std::forward<Args>(args)), 0)...};
    size_ += count;

    return data_ + index;
  }

  // Метод insert_many_back
  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (void)std::initializer_list<int>{
        (push_back(std::forward<Args>(args)), 0)...};
  }
};
}  // namespace s21

#endif  // S21_VECTOR_HPP