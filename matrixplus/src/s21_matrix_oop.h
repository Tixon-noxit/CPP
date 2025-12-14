//
// Created by Тихон Чабусов on 20.06.2024.
//

#ifndef CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 private:
  int rows_, cols_;  // attributes for rows and columns
  double **matrix_;  // pointer to the memory where the matrix will be allocated

  void allocateMemory(int rows, int cols);

  void deallocateMemory();

  void copyMatrix(const S21Matrix &o);

 public:
  S21Matrix();  // Базовый конструктор, инициализирующий матрицу некоторой
                // заранее заданной размерностью
  S21Matrix(int rows, int cols);  // Параметризированный конструктор с
                                  // количеством строк и столбцов.
  S21Matrix(const S21Matrix &o);  // Конструктор копирования.
  S21Matrix(S21Matrix &&o);       // Конструктор переноса.
  ~S21Matrix();                   // Деструктор.

  // some operators overloads
  S21Matrix &operator=(const S21Matrix &o);  // assignment operator overload
  double &operator()(int row, int col);      // index operator overload
  const double &operator()(int row, int col) const;

  S21Matrix &operator+=(const S21Matrix &o);

  S21Matrix operator+(const S21Matrix &o);

  S21Matrix &operator-=(const S21Matrix &o);

  S21Matrix operator-(const S21Matrix &o);

  S21Matrix &operator*=(const S21Matrix &o);

  S21Matrix &operator*=(const double num);

  S21Matrix operator*(const S21Matrix &o);

  S21Matrix operator*(const double num);

  bool operator==(const S21Matrix &o) const;

  // some public methods
  bool EqMatrix(const S21Matrix &o) const;

  void SumMatrix(const S21Matrix &o);

  void SubMatrix(const S21Matrix &o);

  void MulNumber(const double num);

  void MulMatrix(const S21Matrix &o);

  S21Matrix Transpose() const;

  S21Matrix CalcComplements() const;

  double Determinant() const;

  S21Matrix InverseMatrix() const;

  // accessors and mutators
  int getRows() const { return rows_; }

  int getCols() const { return cols_; }

  void setRows(int rows);

  void setCols(int cols);
};

#endif  // CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H
