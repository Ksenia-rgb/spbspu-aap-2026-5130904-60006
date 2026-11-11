#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>

namespace repina {
  constexpr int exitBadArguments = 1;
  constexpr int exitError = 2;
  constexpr int maxElements = 10000;
  constexpr int maxNumber = 1000;
  constexpr int base = 10;
  constexpr double roundFactor = 10.0;
  constexpr int requiredArgCount = 4;
  constexpr int modeStatic = 1;
  constexpr int modeDynamic = 2;

  bool parseInt(const char* s, int& result)
  {
    int n = 0;
    if (s[0] == '\0') {
      return false;
    }
    for (std::size_t i = 0; s[i] != '\0'; i++) {
      if (s[i] < '0' || s[i] > '9') {
        return false;
      }
      n = n * base + (s[i] - '0');
      if (n > maxNumber) {
        return false;
      }
    }
    result = n;
    return true;
  }

  bool checkRowsAndCols(int rows, int cols, int limit)
  {
    if (rows < 0 || cols < 0) {
      std::cerr << "wrong with rows and cols" << "\n";
      return false;
    }
    if (rows != 0) {
      if (cols > std::numeric_limits< int >::max() / rows) {
        std::cerr << "cols too large" << "\n";
        return false;
      }
    }
    if (cols * rows > limit) {
      std::cerr << "matrix too large" << "\n";
      return false;
    }
    return true;
  }

  bool readElements(std::istream& input, int* data, int total)
  {
    for (int i = 0; i < total; i++) {
      if (!(input >> data[i])) {
        std::cerr << "wrong input element" << "\n";
        return false;
      }
    }
    input >> std::ws;
    if (!input.eof()) {
      std::cerr << "too much in the data\n";
      return false;
    }
    return true;
  }

  void buildSmoothedMatrix(const int* data, double* res, int rows, int cols)
  {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        int sum = 0;
        int count = 0;
        for (int di = -1; di <= 1; di++) {
          for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) {
              continue;
            }
            const int ni = i + di;
            const int nj = j + dj;
            if (ni < 0 || ni >= rows || nj < 0 || nj >= cols) {
              continue;
            }
            sum += data[ni * cols + nj];
            count++;
          }
        }
        if (count != 0) {
          res[i * cols + j] = static_cast< double >(sum) / count;
        } else {
          res[i * cols + j] = 0;
        }
      }
    }
  }

  long long findMaxDiagonalSum(const int* data, int rows, int cols)
  {
    long long best = 0;
    bool found = false;
    for (int d = -(rows - 1); d <= cols - 1; d++) {
      if (d == 0) {
        continue;
      }
      long long sum = 0;
      bool has = false;
      for (int i = 0; i <= rows - 1; i++) {
        const int j = i + d;
        if (j >= cols || j < 0) {
          continue;
        }
        sum += data[i * cols + j];
        has = true;
      }
      if (has && (!found || sum > best)) {
        best = sum;
        found = true;
      }
    }
    return found ? best : 0;
  }
}

int main(int argc, char** argv)
{
  if (argc != repina::requiredArgCount) {
    std::cerr << "not enough arguments" << "\n";
    return repina::exitBadArguments;
  }
  const char* const mode = argv[1];
  const char* const input_path = argv[2];
  const char* const output_path = argv[3];
  int mode_num = 0;
  if (!repina::parseInt(mode, mode_num) || mode_num < repina::modeStatic || mode_num > repina::modeDynamic) {
    std::cerr << "mode error" << "\n";
    return repina::exitBadArguments;
  }

  std::ifstream input(input_path);
  if (!input) {
    std::cerr << "some wrong with input_path file" << "\n";
    return repina::exitError;
  }
  std::ofstream output(output_path);
  if (!output) {
    std::cerr << "some wrong with output_path file" << "\n";
    return repina::exitError;
  }
  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols)) {
    std::cerr << "cannot read rows and cols" << "\n";
    return repina::exitError;
  }
  if (!repina::checkRowsAndCols(rows, cols, repina::maxElements)) {
    return repina::exitError;
  }

  if (mode_num == repina::modeStatic) {
    int data[repina::maxElements] = {};
    double res[repina::maxElements] = {};
    if (!repina::readElements(input, data, rows * cols)) {
      return repina::exitError;
    }
    repina::buildSmoothedMatrix(data, res, rows, cols);
    output << rows << " " << cols << "\n";
    for (int i = 0; i < rows * cols; i++) {
      const double rounded = std::round(res[i] * repina::roundFactor) / repina::roundFactor;
      output << rounded << " ";
    }
    output << "\n";
    output << repina::findMaxDiagonalSum(data, rows, cols) << "\n";
  }

  if (mode_num == repina::modeDynamic) {
    int* const data = new int[rows * cols];
    double* const res = new double[rows * cols];
    if (!repina::readElements(input, data, rows * cols)) {
      delete[] data;
      delete[] res;
      return repina::exitError;
    }
    repina::buildSmoothedMatrix(data, res, rows, cols);
    output << rows << " " << cols << "\n";
    for (int i = 0; i < rows * cols; i++) {
      const double rounded = std::round(res[i] * repina::roundFactor) / repina::roundFactor;
      output << rounded << " ";
    }
    output << "\n";
    output << repina::findMaxDiagonalSum(data, rows, cols) << "\n";

    delete[] data;
    delete[] res;
  }
  return 0;
}
