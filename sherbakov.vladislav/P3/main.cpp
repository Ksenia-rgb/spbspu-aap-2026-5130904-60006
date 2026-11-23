#include <iostream>
#include <fstream>
#include <new>

namespace sherbakov {

  const size_t ERR_ARGS = 1;
  const size_t ERR_FILE = 2;
  const size_t MAX_STATIC = 10000;
  const size_t MAX_TOTAL = 10000000LL;

  const size_t MODE_STATIC = 1;
  const size_t MODE_DYNAMIC = 2;
  const size_t EXPECTED_ARGS_COUNT = 4;

  bool getMode(const char* s, int& mode)
  {
    if (s == nullptr) {
      return false;
    }
    if (s[0] == '1' && s[1] == '\0') {
      mode = MODE_STATIC;
      return true;
    }
    if (s[0] == '2' && s[1] == '\0') {
      mode = MODE_DYNAMIC;
      return true;
    }
    return false;
  }

  size_t countCols(const int* a, size_t rows, size_t cols)
  {
    size_t count = 0;
    for (size_t j = 0; j < cols; ++j) {
      bool good = true;
      for (size_t i = 1; i < rows; ++i) {
        if (a[i * cols + j] == a[(i - 1) * cols + j]) {
          good = false;
          break;
        }
      }
      if (good) {
        ++count;
      }
    }
    return count;
  }

  long long maxSum(const int* a, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }

    long long best = 0;
    bool found = false;
    const size_t max_k = (rows - 1) + (cols - 1);
    const size_t sec_k = cols - 1;

    for (size_t k = 0; k <= max_k; ++k) {
      if (k == sec_k) {
        continue;
      }

      size_t i_min = 0;
      if (k >= cols) {
        i_min = k - (cols - 1);
      }

      size_t i_max = k;
      if (i_max > rows - 1) {
        i_max = rows - 1;
      }

      long long sum = 0;
      for (size_t i = i_min; i <= i_max; ++i) {
        const size_t j = k - i;
        sum += a[i * cols + j];
      }

      if (!found || sum > best) {
        best = sum;
        found = true;
      }
    }

    if (found) {
      return best;
    }
    return 0;
  }
}
int main(int argc, char** argv)
{
  using namespace sherbakov;

  if (argc != EXPECTED_ARGS_COUNT) {
    std::cerr << "Error: expected 3 arguments (mode input output)\n";
    return ERR_ARGS;
  }

  int mode = 0;
  if (!getMode(argv[1], mode)) {
    std::cerr << "Error: first argument must be 1 or 2\n";
    return ERR_ARGS;
  }

  std::ifstream in(argv[2]);
  if (!in.is_open()) {
    std::cerr << "Error: cannot open input file\n";
    return ERR_FILE;
  }

  long long rows_ll = 0;
  long long cols_ll = 0;
  if (!(in >> rows_ll >> cols_ll)) {
    std::cerr << "Error: cannot read matrix dimensions\n";
    return ERR_FILE;
  }
  if (rows_ll < 0 || cols_ll < 0) {
    std::cerr << "Error: negative dimensions\n";
    return ERR_FILE;
  }
  
  const size_t rows = static_cast< size_t >(rows_ll);
  const size_t cols = static_cast< size_t >(cols_ll);
  const long long total_ll = rows_ll * cols_ll;
  if (total_ll > MAX_TOTAL) {
    std::cerr << "Error: matrix is too large\n";
    return ERR_FILE;
  }

  const size_t total = static_cast< size_t >(total_ll);

  int* a = nullptr;
  bool dynamic = false;

  if (mode == MODE_STATIC) {
    if (total > MAX_STATIC) {
      std::cerr << "Error: too many elements for static storage\n";
      return ERR_FILE;
    }
    static int static_buf[MAX_STATIC];
    a = static_buf;
  } else {
    try {
      a = new int[total];
      dynamic = true;
    } catch (const std::bad_alloc&) {
      std::cerr << "Error: cannot allocate memory\n";
      return ERR_FILE;
    }
  }

  bool read_ok = true;
  for (size_t k = 0; k < total; ++k) {
    if (!(in >> a[k])) {
      read_ok = false;
      break;
    }
  }
  if (!read_ok) {
    std::cerr << "Error: not enough matrix elements\n";
    if (dynamic) delete[] a;
    return ERR_FILE;
  }
  in >> std::ws;

  if (!in.eof()) {
    std::cerr << "Error: extra values after matrix\n";
    if (dynamic) delete[] a;
    return ERR_FILE;
  }

  const size_t task9_result = countCols(a, rows, cols);
  const long long task13_result = maxSum(a, rows, cols);

  if (dynamic) {
    delete[] a;
  }

  std::ofstream out(argv[3]);
  if (!out.is_open()) {
    std::cerr << "Error: cannot open output file\n";
    return ERR_FILE;
  }

  out << task9_result << '\n';
  out << task13_result << '\n';

  return 0;
}
