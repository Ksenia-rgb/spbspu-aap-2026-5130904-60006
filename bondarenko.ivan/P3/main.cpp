#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

void writeToFile(std::ofstream &output, int rows, int cols, int **matrix) {
  output << rows << ' ' << cols << ' ';
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      output << matrix[i][j] << ' ';
    }
  }
  output << "\n";
}

void problem_a(std::ofstream &output, int rows, int cols, int **matrix) {
  for (int layer = 0;
       layer < std::min(rows, cols) / 2 + std::min(rows, cols) % 2; layer++) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if ((i >= layer && i <= rows - layer - 1 && j >= layer &&
             j <= cols - layer - 1) &&
            (i == layer || i == rows - layer - 1 || j == layer ||
             j == cols - layer - 1)) {
          matrix[i][j] += (layer + 1);
        }
      }
    }
  }
  writeToFile(output, rows, cols, matrix);
}

void problem_b(std::ofstream &output, int rows, int cols, int **matrix) {

  int minDiagonal = -(rows - 2);
  int maxDiagonal = cols - 2;

  int count = 0;

  for (int diagonal = minDiagonal; diagonal <= maxDiagonal; diagonal++) {
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

void fillMatrix(std::ifstream &input, int rows, int cols, int **matrix) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      input >> matrix[i][j];
    }
  }
}

void copy_matrix(int **original, int **copy, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      copy[i][j] = original[i][j];
    }
  }
}

void process_static(std::ifstream &input, std::ofstream &output, int rows,
                    int cols) {
  constexpr int MAX_ROWS = 100;
  constexpr int MAX_COLS = 100;

  int matrix[MAX_ROWS][MAX_COLS];
  int *pointers[MAX_ROWS];

  int copyMatrix[MAX_ROWS][MAX_COLS];
  int *copyPointers[MAX_ROWS];

  for (int i = 0; i < rows; i++) {
    pointers[i] = matrix[i];
    copyPointers[i] = copyMatrix[i];
  }

  fillMatrix(input, rows, cols, pointers);

  copy_matrix(pointers, copyPointers, rows, cols);
  problem_a(output, rows, cols, copyPointers);

  copy_matrix(pointers, copyPointers, rows, cols);
  problem_b(output, rows, cols, copyPointers);
}

void process_dynamic(std::ifstream &input, std::ofstream &output, int rows,
                     int cols) {

  int **matrix = new int *[rows];
  int **copyMatrix = new int *[rows];

  for (int i = 0; i < rows; i++) {
    matrix[i] = new int[cols];
    copyMatrix[i] = new int[cols];
  }

  fillMatrix(input, rows, cols, matrix);

  copy_matrix(matrix, copyMatrix, rows, cols);
  problem_a(output, rows, cols, copyMatrix);

  copy_matrix(matrix, copyMatrix, rows, cols);
  problem_b(output, rows, cols, copyMatrix);

  for (int i = 0; i < rows; i++) {
    delete[] matrix[i];
    delete[] copyMatrix[i];
  }

  delete[] matrix;
  delete[] copyMatrix;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Invalid count of arguments\n";
    return 1;
  }
  std::string num = argv[1];
  if (num != "1" && num != "2") {
    std::cerr << "Invalid argument\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open()) {
    std::cerr << "Failed to open input file\n";
    return 1;
  }

  std::ofstream output(argv[3]);
  if (!output.is_open()) {
    std::cerr << "Failed to open output file\n";
    return 1;
  }

  int rows = 0, cols = 0;

  if (!(input >> rows >> cols)) {
    std::cerr << "Invalid matrix argument\n";
    return 2;
  }
  if (rows <= 0 || cols <= 0) {
    std::cerr << "Invalid matrix argument\n";
    return 1;
  }

  if (num == "1") {
    process_static(input, output, rows, cols);
  } else if (num == "2") {
    process_dynamic(input, output, rows, cols);
  } else {
    return 1;
  }
}
