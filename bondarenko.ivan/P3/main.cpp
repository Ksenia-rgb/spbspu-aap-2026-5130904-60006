#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
namespace bondarenko {
  const int INVALID_ARGUMENTS = 1;
  const int WRONG_ARRAY = 2;

  void writeToFile(std::ofstream &output, int rows, int cols, int **matrix)
  {
    output << rows << ' ' << cols << ' ';
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        output << matrix[i][j] << ' ';
      }
    }
    output << "\n";
  }

  void problemA(std::ofstream &output, int rows, int cols, int **matrix)
  {
    for (int layer = 0; layer < std::min(rows, cols) / 2 + std::min(rows, cols) % 2; layer++) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          if ((i >= layer && i <= rows - layer - 1 && j >= layer && j <= cols - layer - 1)
              && (i == layer || i == rows - layer - 1 || j == layer || j == cols - layer - 1)) {
            matrix[i][j] += (layer + 1);
          }
        }
      }
    }
    writeToFile(output, rows, cols, matrix);
  }

  void problemB(std::ofstream &output, int rows, int cols, int **matrix)
  {
    const int min_diagonal = -(rows - 2);
    const int max_diagonal = cols - 2;

    int count = 0;

    for (int diagonal = min_diagonal; diagonal <= max_diagonal; diagonal++) {
      bool flag = true;
      for (int i = 0; i < rows; i++) {
        if (!flag) {
          break;
        }
        for (int j = 0; j < cols; j++) {
          if (j - i == diagonal && matrix[i][j] == 0) {
            flag = false;
            break;
          }
        }
      }
      if (flag) {
        count++;
      }
    }
    output << count;
  }

  void fillMatrix(std::ifstream &input, int rows, int cols, int **matrix)
  {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        input >> matrix[i][j];
      }
    }
  }

  void copyMatrix(int **original, int **copy, int rows, int cols)
  {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        copy[i][j] = original[i][j];
      }
    }
  }

  void processStatic(std::ifstream &input, std::ofstream &output, int rows, int cols)
  {
    constexpr int MAX_ROWS = 100;
    constexpr int MAX_COLS = 100;
    
    try {
      int matrix[MAX_ROWS][MAX_COLS];
      int *pointers[MAX_ROWS];

      int copy_matrix[MAX_ROWS][MAX_COLS];
      int *copy_pointers[MAX_ROWS];

      for (int i = 0; i < rows; i++) {
        pointers[i] = matrix[i];
        copy_pointers[i] = copy_matrix[i];
      }

      fillMatrix(input, rows, cols, pointers);

      copyMatrix(pointers, copy_pointers, rows, cols);
      problemA(output, rows, cols, copy_pointers);

      copyMatrix(pointers, copy_pointers, rows, cols);
      problemB(output, rows, cols, copy_pointers);
    } catch (...) {
      throw;
    }
  }

  void processDynamic(std::ifstream &input, std::ofstream &output, int rows, int cols)
  {
    try {
      int **const matrix = new int*[rows];
      int **const copy_matrix = new int*[rows];

      for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        copy_matrix[i] = new int[cols];
      }

      fillMatrix(input, rows, cols, matrix);

      copyMatrix(matrix, copy_matrix, rows, cols);
      problemA(output, rows, cols, copy_matrix);

      copyMatrix(matrix, copy_matrix, rows, cols);
      problemB(output, rows, cols, copy_matrix);

      for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
        delete[] copy_matrix[i];
      }

      delete[] matrix;
      delete[] copy_matrix;
    } catch (...) {
      throw;
    }
  }
}
int main(int argc, char *argv[])
{
  if (argc != 4) {
    std::cerr << "Invalid count of arguments\n";
    return bondarenko::INVALID_ARGUMENTS;
  }
  const std::string num = argv[1];
  if (num != "1" && num != "2") {
    std::cerr << "Invalid argument\n";
    return bondarenko::INVALID_ARGUMENTS;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open()) {
    std::cerr << "Failed to open input file\n";
    return bondarenko::INVALID_ARGUMENTS;
  }

  std::ofstream output(argv[3]);
  if (!output.is_open()) {
    std::cerr << "Failed to open output file\n";
    return bondarenko::INVALID_ARGUMENTS;
  }

  int rows = 0, cols = 0;

  if (!(input >> rows >> cols)) {
    std::cerr << "Invalid matrix argument\n";
    return bondarenko::WRONG_ARRAY;
  }
  if (rows < 0 || cols < 0) {
    std::cerr << "Invalid matrix argument\n";
    return bondarenko::INVALID_ARGUMENTS;
  }

  if (num == "1") {
    try {
      bondarenko::processStatic(input, output, rows, cols);
    } catch (...) {
      std::cerr << "Cannot alloc static matrix\n";
      return bondarenko::WRONG_ARRAY;
    }
  } else if (num == "2") {
    try {
      bondarenko::processDynamic(input, output, rows, cols);
    } catch (...) {
      std::cerr << "Cannot alloc dynamic matrix\n";
      return bondarenko::WRONG_ARRAY;
    }
  } else {
    return bondarenko::INVALID_ARGUMENTS;
  }
}
