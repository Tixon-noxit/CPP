//
// Created by Тихон Чабусов on 20.06.2024.
//

#include "s21_matrix_oop.h"

void S21Matrix::allocateMemory(int rows, int cols) {
  matrix_ = new double *[rows];
  for (int i = 0; i < rows; ++i) {
    matrix_[i] = new double[cols]();
  }
}

void S21Matrix::deallocateMemory() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

void S21Matrix::copyMatrix(const S21Matrix &o) {
  allocateMemory(o.rows_, o.cols_);
  for (int i = 0; i < o.rows_; ++i) {
    for (int j = 0; j < o.cols_; ++j) {
      matrix_[i][j] = o.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix() : rows_(3), cols_(3) { allocateMemory(rows_, cols_); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  allocateMemory(rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix &o) : rows_(o.rows_), cols_(o.cols_) {
  copyMatrix(o);
}

S21Matrix::S21Matrix(S21Matrix &&o)
    : rows_(o.rows_), cols_(o.cols_), matrix_(o.matrix_) {
  o.rows_ = 0;
  o.cols_ = 0;
  o.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { deallocateMemory(); }

S21Matrix &S21Matrix::operator=(const S21Matrix &o) {
  if (this != &o) {
    deallocateMemory();
    rows_ = o.rows_;
    cols_ = o.cols_;
    copyMatrix(o);
  }
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[row][col];
}

const double &S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[row][col];
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &o) {
  SumMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &o) {
  S21Matrix result = *this;
  result.SumMatrix(o);
  return result;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &o) {
  SubMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &o) {
  S21Matrix result = *this;
  result.SubMatrix(o);
  return result;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &o) {
  MulMatrix(o);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &o) {
  S21Matrix result = *this;
  result.MulMatrix(o);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result = *this;
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &o) const { return EqMatrix(o); }

bool S21Matrix::EqMatrix(const S21Matrix &o) const {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::fabs(matrix_[i][j] - o.matrix_[i][j]) > 1e-9) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::invalid_argument("Matrices dimensions must match for addition");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += o.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::invalid_argument(
        "Matrices dimensions must match for subtraction");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= o.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &o) {
  if (cols_ != o.rows_) {
    throw std::invalid_argument(
        "Matrix multiplication requires the number of columns in the first "
        "matrix to equal the number of rows in the second matrix");
  }
  S21Matrix result(rows_, o.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < o.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * o.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to calculate complements");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix subMatrix(rows_ - 1, cols_ - 1);
      int sub_i = 0;
      for (int k = 0; k < rows_; k++) {
        if (k == i) continue;
        int sub_j = 0;
        for (int l = 0; l < cols_; l++) {
          if (l == j) continue;
          subMatrix(sub_i, sub_j) = matrix_[k][l];
          sub_j++;
        }
        sub_i++;
      }
      result(i, j) = subMatrix.Determinant() * ((i + j) % 2 == 0 ? 1 : -1);
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to calculate determinant");
  }

  // Base cases for 1x1 and 2x2 matrices
  if (rows_ == 1) {
    return matrix_[0][0];
  } else if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }

  double det = 0.0;
  S21Matrix minor(rows_ - 1, cols_ - 1);

  for (int p = 0; p < cols_; ++p) {
    int minor_i = 0;
    for (int i = 1; i < rows_; ++i) {
      int minor_j = 0;
      for (int j = 0; j < cols_; ++j) {
        if (j == p) {
          continue;
        }
        minor(minor_i, minor_j) = matrix_[i][j];
        ++minor_j;
      }
      ++minor_i;
    }

    double minor_det = minor.Determinant();
    det += matrix_[0][p] * minor_det * ((p % 2 == 0) ? 1 : -1);
  }

  return det;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square to calculate inverse");
  }
  double det = Determinant();
  if (std::fabs(det) < 1e-9) {
    throw std::invalid_argument("Matrix is singular and cannot be inverted");
  }
  S21Matrix result = CalcComplements().Transpose();
  result.MulNumber(1.0 / det);
  return result;
}

void S21Matrix::setRows(int rows) {
  if (rows != rows_) {
    S21Matrix new_matrix(rows, cols_);
    for (int i = 0; i < std::min(rows, rows_); ++i) {
      for (int j = 0; j < cols_; ++j) {
        new_matrix.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(new_matrix);
  }
}

void S21Matrix::setCols(int cols) {
  if (cols != cols_) {
    S21Matrix new_matrix(rows_, cols);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < std::min(cols, cols_); ++j) {
        new_matrix.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(new_matrix);
  }
}
