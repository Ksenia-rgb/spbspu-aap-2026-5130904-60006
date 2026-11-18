#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace nurmedov {
constexpr std::size_t fixed_matrix_capacity = 10000;
const int expected_arg_count = 4;
const int code_bad_arguments = 1;
const int code_bad_data = 2;

// Variant 11 [NUM-COL-LSR]: number of the column with the longest run of equal
// elements
int numColLsr(const int *matrix, int rows, int cols) {
  if (matrix == nullptr || rows <= 0 || cols <= 0) {
    return 0;
  }
  const std::size_t column_count = static_cast<std::size_t>(cols);
  int best_column = 0;
  int best_length = 0;
  for (int column = 0; column < cols; ++column) {
    int current_length = 1;
    int max_length = 1;
    const std::size_t column_position = static_cast<std::size_t>(column);
    for (int row = 1; row < rows; ++row) {
      const std::size_t previous_index =
          static_cast<std::size_t>(row - 1) * column_count + column_position;
      const std::size_t current_index =
          static_cast<std::size_t>(row) * column_count + column_position;
      if (matrix[previous_index] == matrix[current_index]) {
        ++current_length;
        if (current_length > max_length) {
          max_length = current_length;
        }
      } else {
        current_length = 1;
      }
    }
    if (max_length > best_length) {
      best_length = max_length;
      best_column = column + 1;
    }
  }
  return best_column;
}

// Variant 6 [LFT-BOT-CNT]: spiral increment from the bottom-left corner,
// counter-clockwise
void addSpiral(int *data, const int rows, const int cols) {
  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = cols - 1;
  int increment = 1;
  while (top <= bottom && left <= right) {
    for (int col = left; col <= right; ++col) {
      data[bottom * cols + col] += increment;
      ++increment;
    }
    --bottom;
    for (int row = bottom; row >= top; --row) {
      data[row * cols + right] += increment;
      ++increment;
    }
    --right;
    if (top <= bottom) {
      for (int col = right; col >= left; --col) {
        data[top * cols + col] += increment;
        ++increment;
      }
      ++top;
    }
    if (left <= right) {
      for (int row = top; row <= bottom; ++row) {
        data[row * cols + left] += increment;
        ++increment;
      }
      ++left;
    }
  }
}

bool readMatrix(std::ifstream &input, int *data, const long long count) {
  for (long long i = 0; i < count; ++i) {
    if (!(input >> data[i])) {
      return false;
    }
  }
  input >> std::ws;
  return input.eof();
}

void writeMatrix(std::ofstream &output, const int *data, const int rows,
                 const int cols, const long long count) {
  output << rows << ' ' << cols;
  for (long long i = 0; i < count; ++i) {
    output << ' ' << data[i];
  }
  output << '\n';
}

// Reads the matrix once, then applies both variants to the ORIGINAL data:
// variant 11 is calculated first, because variant 6 modifies the matrix.
int processMatrix(int *data, const int rows, const int cols,
                  const long long count, std::ifstream &input,
                  const char *output_name) {
  if (!readMatrix(input, data, count)) {
    std::cerr << "Input file has no correct matrix\n";
    return code_bad_data;
  }
  const int column_number = numColLsr(data, rows, cols);
  addSpiral(data, rows, cols);
  std::ofstream output(output_name);
  if (!output) {
    std::cerr << "Cant open output file\n";
    return code_bad_data;
  }
  writeMatrix(output, data, rows, cols, count);
  output << column_number << '\n';
  if (!output) {
    std::cerr << "Cant write result\n";
    return code_bad_data;
  }
  return 0;
}

int runProgram(const char *mode, const char *input_name,
               const char *output_name) {
  std::ifstream input(input_name);
  if (!input) {
    std::cerr << "Cant open input file\n";
    return code_bad_data;
  }
  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "Input file has no correct matrix\n";
    return code_bad_data;
  }
  const long long count = static_cast<long long>(rows) * cols;
  if (std::strcmp(mode, "1") == 0) {
    if (count > static_cast<long long>(fixed_matrix_capacity)) {
      std::cerr << "Matrix is too big for a fixed size\n";
      return code_bad_data;
    }
    int stack_data[fixed_matrix_capacity] = {};
    return processMatrix(stack_data, rows, cols, count, input, output_name);
  }
  if (std::strcmp(mode, "2") == 0) {
    if (count > std::numeric_limits<int>::max()) {
      std::cerr << "Matrix is too big\n";
      return code_bad_data;
    }
    int *const heap_data = new int[static_cast<std::size_t>(count)];
    const int code =
        processMatrix(heap_data, rows, cols, count, input, output_name);
    delete[] heap_data;
    return code;
  }
  std::cerr << "Unknown mode\n";
  return code_bad_arguments;
}
} // namespace nurmedov

int main(int argc, char *argv[]) {
  if (argc != nurmedov::expected_arg_count) {
    std::cerr << "Usage: ./lab num input output\n";
    return nurmedov::code_bad_arguments;
  }
  const char *const mode = argv[1];
  if (std::strcmp(mode, "1") != 0 && std::strcmp(mode, "2") != 0) {
    std::cerr << "Mode can be 1 or 2 only!!!\n";
    return nurmedov::code_bad_arguments;
  }
  try {
    return nurmedov::runProgram(mode, argv[2], argv[3]);
  } catch (const std::bad_alloc &) {
    std::cerr << "Not enough memory\n";
    return nurmedov::code_bad_data;
  }
}
