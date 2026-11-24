#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>

constexpr int ERROR_CODE = 1;
constexpr int SUCCESS_CODE = 0;
constexpr int MODE_ARGUMENT = 1;
constexpr int INPUT_ARGUMENT = 2;
constexpr int OUTPUT_ARGUMENT = 3;
constexpr int ARGUMENT_COUNT = 4;
constexpr char STATIC_MODE = '1';
constexpr char DYNAMIC_MODE = '2';
constexpr std::size_t MAX_SIZE = 10000;

bool isValidMode(const char *mode)
{
  if (mode[0] != STATIC_MODE && mode[0] != DYNAMIC_MODE) {
    return false;
  }
  return mode[1] == '\0';
}

bool readDimensions(std::istream &input, std::size_t &rows, std::size_t &cols)
{
  long long raw_rows = 0;
  long long raw_cols = 0;
  if (!(input >> raw_rows >> raw_cols)) {
    return false;
  }
  if (raw_rows < 0 || raw_cols < 0) {
    return false;
  }
  rows = static_cast< std::size_t >(raw_rows);
  cols = static_cast< std::size_t >(raw_cols);
  if (cols != 0 && rows > std::numeric_limits< std::size_t >::max() / cols) {
    return false;
  }
  return true;
}

bool hasExtraData(std::istream &input)
{
  char extra = '\0';
  return (input >> extra).good();
}

bool readElements(std::istream &input, int *matrix, std::size_t count)
{
  for (std::size_t i = 0; i < count; i++) {
    if (!(input >> matrix[i])) {
      return false;
    }
  }
  return !hasExtraData(input);
}

void decreaseElements(std::size_t rows, std::size_t cols, int *matrix)
{
  if (rows == 0 || cols == 0) {
    return;
  }

  std::size_t top = 0;
  std::size_t bottom = rows - 1;
  std::size_t left = 0;
  std::size_t right = cols - 1;
  int step = 1;

  while (top <= bottom && left <= right) {
    for (std::size_t i = bottom + 1; i > top; i = i - 1) {
      matrix[(i - 1) * cols + left] = matrix[(i - 1) * cols + left] - step;
      step++;
    }
    left++;
    if (left > right) {
      break;
    }

    for (std::size_t j = left; j <= right; j++) {
      matrix[top * cols + j] = matrix[top * cols + j] - step;
      step++;
    }
    top++;
    if (top > bottom) {
      break;
    }

    for (std::size_t i = top; i <= bottom; i++) {
      matrix[i * cols + right] = matrix[i * cols + right] - step;
      step++;
    }
    right = right - 1;
    if (left > right) {
      break;
    }

    for (std::size_t j = right + 1; j > left; j = j - 1) {
      matrix[bottom * cols + j - 1] = matrix[bottom * cols + j - 1] - step;
      step++;
    }
    bottom = bottom - 1;
  }
}

std::size_t countRowsWithoutAdjacentEqual(std::size_t rows, std::size_t cols, const int *matrix)
{
  std::size_t row_count = 0;

  for (std::size_t i = 0; i < rows; i++) {
    bool has_no_equal = true;
    for (std::size_t j = 1; j < cols; j++) {
      if (matrix[i * cols + j] == matrix[i * cols + j - 1]) {
        has_no_equal = false;
        break;
      }
    }
    if (has_no_equal) {
      row_count++;
    }
  }

  return row_count;
}

void writeResult(std::ostream &output, std::size_t rows, std::size_t cols, const int *matrix, std::size_t row_count)
{
  output << rows << ' ' << cols;
  for (std::size_t i = 0; i < rows * cols; i++) {
    output << ' ' << matrix[i];
  }
  output << '\n';
  output << row_count << '\n';
}

int process(
    std::istream &input, std::ostream &output, int *matrix, std::size_t rows, std::size_t cols, std::size_t count)
{
  if (!readElements(input, matrix, count)) {
    return ERROR_CODE;
  }
  const std::size_t row_count = countRowsWithoutAdjacentEqual(rows, cols, matrix);
  decreaseElements(rows, cols, matrix);
  writeResult(output, rows, cols, matrix, row_count);
  return output.good() ? SUCCESS_CODE : ERROR_CODE;
}

int run(char mode, std::istream &input, std::ostream &output)
{
  std::size_t rows = 0;
  std::size_t cols = 0;
  if (!readDimensions(input, rows, cols)) {
    return ERROR_CODE;
  }
  const std::size_t count = rows * cols;

  if (mode == STATIC_MODE) {
    if (count > MAX_SIZE) {
      return ERROR_CODE;
    }
    int matrix[MAX_SIZE];
    return process(input, output, matrix, rows, cols, count);
  }

  int *const matrix = new int[count];
  const int status = process(input, output, matrix, rows, cols, count);
  delete[] matrix;
  return status;
}

int main(int argc, char *argv[])
{
  if (argc != ARGUMENT_COUNT || !isValidMode(argv[MODE_ARGUMENT])) {
    return ERROR_CODE;
  }

  std::ifstream input(argv[INPUT_ARGUMENT]);
  std::ofstream output(argv[OUTPUT_ARGUMENT]);
  if (!input || !output) {
    return ERROR_CODE;
  }

  return run(argv[MODE_ARGUMENT][0], input, output);
}
