#include <iostream>
#include <fstream>
#include <new>

namespace sherbakov {

  const int ERR_ARGS = 1;
  const int ERR_FILE = 2;
  const int MAX_STATIC = 10000;
  const long long MAX_TOTAL = 10000000LL;

  bool getMode(const char* s, int& mode)
  {
    if (s == nullptr) {
      return false;
    }
    if (s[0] == '1' && s[1] == '\0') {
      mode = 1;
      return true;
    }
    if (s[0] == '2' && s[1] == '\0') {
      mode = 2;
      return true;
    }
    return false;
  }

  int countCols(const int* a, int rows, int cols)
  {
    int count = 0;
    for (int j = 0; j < cols; ++j) {
      bool good = true;
      for (int i = 1; i < rows; ++i) {
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

  long long maxSum(const int* a, int rows, int cols)
  {
    if (rows <= 0 || cols <= 0) {
      return 0;
    }

    long long best = 0;
    bool found = false;
    const int max_k = (rows - 1) + (cols - 1);
    const int sec_k = cols - 1;

    for (int k = 0; k <= max_k; ++k) {
      if (k == sec_k) {
        continue;
      }

      int i_min = k - (cols - 1);
      if (i_min < 0) {
        i_min = 0;
      }

      int i_max = k;
      if (i_max > rows - 1) {
        i_max = rows - 1;
      }

      long long sum = 0;
      for (int i = i_min; i <= i_max; ++i) {
        const int j = k - i;
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

  if (argc != 4) {
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

  const long long total_ll = rows_ll * cols_ll;
  if (total_ll > MAX_TOTAL) {
    std::cerr << "Error: matrix is too large\n";
    return ERR_FILE;
  }

  const int rows = static_cast< int >(rows_ll);
  const int cols = static_cast< int >(cols_ll);
  const int total = static_cast< int >(total_ll);

  int static_buf[MAX_STATIC];
  int* a = nullptr;
  bool dynamic = false;

  if (mode == 1) {
    if (total > MAX_STATIC) {
      std::cerr << "Error: too many elements for static storage\n";
      return ERR_FILE;
    }
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
  for (int k = 0; k < total; ++k) {
    if (!(in >> a[k])) {
      read_ok = false;
      break;
    }
  }
  if (!read_ok) {
    std::cerr << "Error: not enough matrix elements\n";
    if (dynamic) {
      delete[] a;
    }
    return ERR_FILE;
  }

  const int task9_result = countCols(a, rows, cols);
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
