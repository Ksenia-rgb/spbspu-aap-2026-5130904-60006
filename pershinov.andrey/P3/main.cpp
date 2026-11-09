#include <iostream>
#include <fstream>
#include <cstddef>

namespace pershinov {
  size_t findColumn(const int * matrix, size_t rows, size_t cols)
  {
    size_t current_length = 0;
    size_t best_length = 0;
    size_t best_column = 0;
    for (size_t j = 0; j < cols; ++j) {
      for (size_t i = 0; i < rows; ++i) {
        if (i > 0 && matrix[(i - 1) * cols + j] == matrix[i * cols + j]) {
          ++current_length;
        } else {
          current_length = 1;
        }
        if (current_length > best_length) {
          best_length = current_length;
          best_column = j + 1;
        }
      }
    }
    return best_column;
  }
  void spiralDecrease(int * matrix, size_t rows, size_t cols)
  {
    size_t top = 0;
    size_t bottom = rows;
    size_t left = 0;
    size_t right = cols;
    int step = 1;
    while (top < bottom && left < right) {
      for (size_t j = left; j < right; ++j) {
        matrix[top * cols + j] -= step;
        ++step;
      }
      ++top;
      for (size_t i = top; i < bottom; ++i) {
        matrix[i * cols + right - 1] -= step;
        ++step;
      }
      --right;

      if (top < bottom) {
        for (size_t j = right; j > left; --j) {
          matrix[(bottom - 1) * cols + (j - 1)] -= step;
          ++step;
        }
        --bottom;
      }
      if (left < right) {
        for (size_t i = bottom; i > top; --i) {
          matrix[(i - 1) * cols + left] -= step;
          ++step;
        }
        ++left;
      }
    }
  }
}
int main(int argc, char ** argv)
{
  const int input_error = 1;
  if (argc != 4) {
    std::cerr << "Error: wrong arguments\n";
    return input_error;
  }
  const char * const mode = argv[1];
  const char * const input_file = argv[2];
  const char * const output_file = argv[3];
  if (!((mode[0] == '1' || mode[0] == '2') && mode[1] == '\0')) {
    std::cerr << "Error: wrong mode\n";
    return input_error;
  }
  std::ifstream input(input_file);
  if (!input) {
    std::cerr << "Error: could not open input file\n";
    return input_error;
  }
  const int exit_matrix_error = 2;
  size_t cols = 0;
  size_t rows = 0;
  std::ofstream output(output_file);
  if (!output) {
    std::cerr << "Error: could not open output file\n";
    return input_error;
  }
  input >> rows >> cols;
  if (!input) {
    std::cerr << "Error: invalid matrix\n";
    return exit_matrix_error;
  }
  const int big_size = 10000;
  int stack_matrix[big_size];
  int * matrix = stack_matrix;
  if (mode[0] == '2') {
    matrix = new int[rows * cols];
  }
  for (size_t i = 0; i < rows * cols; ++i) {
    input >> matrix[i];
  }
  if (!input) {
    std::cerr << "Error: invalid matrix\n";
    if (mode[0] == '2') {
      delete[] matrix;
    }
    return exit_matrix_error;
  }
  output << pershinov::findColumn(matrix, rows, cols) << '\n';
  pershinov::spiralDecrease(matrix, rows, cols);
  output << rows << " " << cols;
  for (size_t i = 0; i < rows * cols; ++i) {
    output << " " << matrix[i];
  }
  output << '\n';
  if (mode[0] == '2') {
    delete[] matrix;
  }
  return 0;
}
