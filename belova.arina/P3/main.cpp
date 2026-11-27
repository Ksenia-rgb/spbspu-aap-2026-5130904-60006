#include <cstddef>
#include <fstream>
#include <iostream>
namespace belova {
void transformSpiral(int *matrix, size_t rows, size_t cols) {
  size_t top = 0;
  size_t bottom = rows - 1;
  size_t left = 0;
  size_t right = cols - 1;
  int decrement = 1;
  while (top <= bottom && left <= right) {
    for (size_t j = left; j <= right; ++j) {
      matrix[top * cols + j] -= decrement++;
    }
    ++top;
    for (size_t i = top; i <= bottom; ++i) {
      matrix[i * cols + right] -= decrement++;
    }
    if (right == 0) {
      break;
    }
    --right;
    if (top <= bottom) {
      for (size_t j = right + 1; j-- > left;) {
        matrix[bottom * cols + j] -= decrement++;
      }
      --bottom;
    }
    if (left <= right) {
      for (size_t i = bottom + 1; i-- > top;) {
        matrix[i * cols + left] -= decrement++;
      }
      ++left;
    }
  }
}
bool run(std::istream &input, std::ostream &output, int mode) {
  size_t rows = 0;
  size_t cols = 0;
  if (!(input >> rows >> cols)) {
    return false;
  }
  if (rows == 0 && cols == 0) {
    output << 0 << '\n';
    output << "0 0\n";
    return output.good();
  }
  if (rows == 0 || cols == 0 || rows > 10000 || cols > 10000) {
    return false;
  }
  if (rows > 10000 / cols) {
    return false;
  }
  size_t total = rows * cols;
  int stackMatrix[10000] = {};
  int *matrix = stackMatrix;
  if (mode == 2) {
    matrix = new int[rows * cols];
  }
  for (size_t i = 0; i < rows * cols; i++) {
    if (!(input >> matrix[i])) {
      if (mode == 2) {
        delete[] matrix;
      }
      return false;
    }
  }
  size_t count = 0;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      int value = matrix[i * cols + j];
      bool minInRow = true;
      bool maxInCol = true;
      for (size_t k = 0; k < cols; ++k) {
        if (matrix[i * cols + k] < value) {
          minInRow = false;
          break;
        }
      }
      for (size_t k = 0; k < rows; ++k) {
        if (matrix[k * cols + j] > value) {
          maxInCol = false;
          break;
        }
      }
      if (minInRow && maxInCol) {
        ++count;
      }
    }
  }
  output << count << '\n';
  transformSpiral(matrix, rows, cols);
  output << rows << ' ' << cols << '\n';
  for (size_t i = 0; i < total; ++i) {
    output << matrix[i];
    if ((i + 1) % cols == 0) {
      output << '\n';
    } else {
      output << ' ';
    }
  }
  if (mode == 2) {
    delete[] matrix;
  }
  return output.good();
}
} // namespace belova
int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << "incorrect number of arguments\n";
    return 1;
  }
  if (argv[1][0] != '1' && argv[1][0] != '2') {
    std::cerr << "incorrect mode\n";
    return 1;
  }
  if (argv[1][1] != '\0') {
    std::cerr << "incorrect mode\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "cannot open input file\n";
    return 2;
  }
  std::ofstream output(argv[3]);
  if (!output) {
    std::cerr << "cannot open output file\n";
    return 2;
  }
  int mode = argv[1][0] - '0';
  if (!belova::run(input, output, mode)) {
    std::cerr << "incorrect input data\n";
    return 2;
  }
  return 0;
}
