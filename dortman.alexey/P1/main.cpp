#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <limits>

void freeMatrix(int** matrix, size_t rows)
{
  if (!matrix)
  {
    return;
  }
  for (size_t i = 0; i < rows; ++i)
  {
    std::free(matrix[i]);
  }
  std::free(matrix);
}

int** allocateMatrix(size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0)
  {
    return nullptr;
  }

  if (rows > std::numeric_limits< size_t >::max() / sizeof(int*))
  {
    return nullptr;
  }
  int** matrix = static_cast< int** >(std::malloc(rows * sizeof(int*)));
  if (!matrix)
  {
    return nullptr;
  }

  if (cols > std::numeric_limits< size_t >::max() / sizeof(int))
  {
    std::free(matrix);
    return nullptr;
  }

  for (size_t i = 0; i < rows; ++i)
  {
    matrix[i] = static_cast< int* >(std::malloc(cols * sizeof(int)));
    if (!matrix[i])
    {
      freeMatrix(matrix, i);
      return nullptr;
    }
  }

  return matrix;
}

int readMatrix(int** matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      if (!(std::cin >> matrix[i][j]))
      {
        return 1;
      }
    }
  }
  return 0;
}

void printTransposed(const int* const* matrix, size_t rows, size_t cols)
{
  for (size_t j = 0; j < cols; ++j)
  {
    for (size_t i = 0; i < rows; ++i)
    {
      std::cout << matrix[i][j] << (i + 1 == rows ? "" : " ");
    }
    std::cout << '\n';
  }
}

int main()
{
  size_t rows = 0;
  size_t cols = 0;

  if (!(std::cin >> rows >> cols) || rows == 0 || cols == 0)
  {
    return 1;
  }

  int** matrix = allocateMatrix(rows, cols);
  if (!matrix)
  {
    return 2;
  }

  if (readMatrix(matrix, rows, cols) != 0)
  {
    freeMatrix(matrix, rows);
    return 1;
  }

  printTransposed(matrix, rows, cols);

  freeMatrix(matrix, rows);
  return 0;
}
