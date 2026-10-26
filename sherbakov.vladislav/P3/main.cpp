#include <iostream>
#include <fstream>
#include <new>

namespace sherbakov {

  const int ERR_ARGS = 1;
  const int ERR_FILE = 2;
  const int MAX_STATIC = 10000;

  bool parseMode(const char* s, int& mode)
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

  int countColumnsNoEqualNeighbors(const int* a, int rows, int cols)
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

  long long maxSumParallelSecondary(const int* a, int rows, int cols)
  {
    if (rows <= 0 || cols <= 0) {
      return 0;
    }

    long long best = 0;
    bool found = false;
    int maxK = (rows - 1) + (cols - 1);
    int secK = cols - 1;

    for (int k = 0; k <= maxK; ++k) {
      if (k == secK) {
        continue;
      }

      int iMin = k - (cols - 1);
      if (iMin < 0) {
        iMin = 0;
      }

      int iMax = k;
      if (iMax > rows - 1) {
        iMax = rows - 1;
      }

      long long sum = 0;
      for (int i = iMin; i <= iMax; ++i) {
        int j = k - i;
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

  int main(int argc, char** argv)
  {
    using namespace sherbakov;

    if (argc != 4) {
      std::cerr << "Error: expected 3 arguments (mode input output)\n";
      return ERR_ARGS;
    }

    int mode = 0;
    if (!parseMode(argv[1], mode)) {
      std::cerr << "Error: first argument must be 1 or 2\n";
      return ERR_ARGS;
    }

    std::ifstream in(argv[2]);
    if (!in.is_open()) {
      std::cerr << "Error: cannot open input file\n";
      return ERR_FILE;
    }

    long long rowsLL = 0;
    long long colsLL = 0;
    if (!(in >> rowsLL >> colsLL)) {
      std::cerr << "Error: cannot read matrix dimensions\n";
      return ERR_FILE;
    }
    if (rowsLL < 0 || colsLL < 0) {
      std::cerr << "Error: negative dimensions\n";
      return ERR_FILE;
    }

    long long totalLL = rowsLL * colsLL;
    if (totalLL > 10000000LL) {
      std::cerr << "Error: matrix is too large\n";
      return ERR_FILE;
    }

    int rows = static_cast< int >(rowsLL);
    int cols = static_cast< int >(colsLL);
    int total = static_cast< int >(totalLL);

    int staticBuf[MAX_STATIC];
    int* a = nullptr;
    bool dynamic = false;

    if (mode == 1) {
      if (total > MAX_STATIC) {
        std::cerr << "Error: too many elements for static storage\n";
        return ERR_FILE;
      }
      a = staticBuf;
    } else {
      try {
        a = new int[total];
        dynamic = true;
      } catch (const std::bad_alloc&) {
        std::cerr << "Error: cannot allocate memory\n";
        return ERR_FILE;
      }
    }

    bool readOk = true;
    for (int k = 0; k < total; ++k) {
      if (!(in >> a[k])) {
        readOk = false;
        break;
      }
    }
    if (!readOk) {
      std::cerr << "Error: not enough matrix elements\n";
      if (dynamic) {
        delete[] a;
      }
      return ERR_FILE;
    }

    int task9Result = countColumnsNoEqualNeighbors(a, rows, cols);
    long long task13Result = maxSumParallelSecondary(a, rows, cols);

    if (dynamic) {
      delete[] a;
    }

    std::ofstream out(argv[3]);
    if (!out.is_open()) {
      std::cerr << "Error: cannot open output file\n";
      return ERR_FILE;
    }

    out << task9Result << '\n';
    out << task13Result << '\n';

    return 0;
  }
