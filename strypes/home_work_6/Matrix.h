#ifndef MATRIX_H
#define MATRIX_H

#include "Array.h"
#include <iostream>
#include <stdexcept>

template<typename T>
class Matrix
{
private:
  Array<T> data;

public:
  size_t rows;
  size_t cols;
  Matrix(size_t rows, size_t cols, T defaultValue = T())
    : data(rows * cols)
    , rows(rows)
    , cols(cols)
  {
    for (size_t i = 0; i < rows * cols; ++i) {
      data.set(i, defaultValue);
    }
  }

  T get(size_t row, size_t col) const
  {
    if (row >= rows || col >= cols) {
      throw std::out_of_range("Index out of bounds");
    }
    return data.get(row * cols + col);
  }

  void set(size_t row, size_t col, T value)
  {
    if (row >= rows || col >= cols) {
      throw std::out_of_range("Index out of bounds");
    }
    data.set(row * cols + col, value);
  }

  void print() const
  {
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        std::cout << get(i, j) << " ";
      }
      std::cout << "\n";
    }
  }

  void destroy() { this->data.destroy(); }
};

template<typename T>
Matrix<T>
multiply(const Matrix<T>& mat1, const Matrix<T>& mat2)
{
  size_t rows = mat1.rows;
  size_t cols = mat2.cols;
  size_t common = mat1.cols;

  if (common != mat2.rows) {
    throw std::invalid_argument(
      "Number of columns in the first matrix must be equal to the number of "
      "rows in the second matrix.");
  }

  Matrix<T> result(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      T sum = 0;
      for (size_t k = 0; k < common; ++k) {
        sum += mat1.get(i, k) * mat2.get(k, j);
      }
      result.set(i, j, sum);
    }
  }

  return result;
}

/*
 * For a non square matrix, row-rotation changes dimension.
 * This invalidates the implemented data structure.
 * For this reason, two versions are given.
 * */
template<typename T>
bool
rotate90DegInPlace(Matrix<T>& mat)
{
  auto rows = mat.rows;
  auto cols = mat.cols;
  if (rows != cols) {
    return false;
  }
  size_t n = rows;
  for (size_t layer = 0; layer < n / 2; ++layer) {
    size_t first = layer;
    size_t last = n - 1 - layer;
    for (size_t i = first; i < last; ++i) {
      size_t offset = i - first;

      // Save top
      T top = mat.get(first, i);

      // left -> top
      mat.set(first, i, mat.get(last - offset, first));

      // bottom -> left
      mat.set(last - offset, first, mat.get(last, last - offset));

      // right -> bottom
      mat.set(last, last - offset, mat.get(i, last));

      // top -> right
      mat.set(i, last, top);
    }
  }
  return true;
}

/* General matrix rotation version, creating a new matrix */
template<typename T>
Matrix<T>
genRotateMatrix90Deg(const Matrix<T>& matrix)
{
  size_t newRows = matrix.cols;
  size_t newCols = matrix.rows;
  Matrix<T> rotatedMatrix(newRows, newCols);

  for (size_t i = 0; i < matrix.rows; ++i) {
    for (size_t j = 0; j < matrix.cols; ++j) {
      rotatedMatrix.set(j, matrix.rows - 1 - i, matrix.get(i, j));
    }
  }

  return rotatedMatrix;
}

#endif // MATRIX_H
