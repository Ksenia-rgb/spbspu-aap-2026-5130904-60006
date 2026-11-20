#include <algorithm>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>

namespace zorin
{
  long long diagonalSum(const long long * a, int n, int m, int i, int j)
  {
    long long sum = 0;
    while (i < n && j < m)
    {
      sum += a[static_cast< std::size_t >(i) * m + j];
      ++i;
      ++j;
    }
    return sum;
  }

  long long minDiagonal(const long long * a, int n, int m)
  {
    if (n == 0 || m == 0 || (n == 1 && m == 1))
    {
      return 0;
    }
    long long best = std::numeric_limits< long long >::max();
    for (int j = 1; j < m; ++j)
    {
      best = std::min(best, diagonalSum(a, n, m, 0, j));
    }
    for (int i = 1; i < n; ++i)
    {
      best = std::min(best, diagonalSum(a, n, m, i, 0));
    }
    return best;
  }

  void spiral(long long * a, int n, int m)
  {
    long long step = 1;
    int top = 0;
    int left = 0;
    int bottom = n;
    int right = m;
    while (top < bottom && left < right)
    {
      for (int j = left; j < right; ++j)
      {
        a[static_cast< std::size_t >(top) * m + j] -= step++;
      }
      ++top;
      --right;
      for (int i = top; i < bottom; ++i)
      {
        a[static_cast< std::size_t >(i) * m + right] -= step++;
      }
      if (top < bottom && left < right)
      {
        --bottom;
        for (int j = right; j > left; --j)
        {
          a[static_cast< std::size_t >(bottom) * m + j - 1] -= step++;
        }
        for (int i = bottom; i > top; --i)
        {
          a[static_cast< std::size_t >(i - 1) * m + left] -= step++;
        }
      }
      ++left;
    }
  }

  int run(std::istream & in, const char * path, long long * a, int n, int m, std::size_t size)
  {
    for (std::size_t i = 0; i < size; ++i)
    {
      int value = 0;
      if (!(in >> value))
      {
        std::cerr << "Invalid matrix elements\n";
        return 2;
      }
      a[i] = value;
    }
    in >> std::ws;
    if (!in.eof() || in.bad())
    {
      std::cerr << "Unexpected data after the matrix\n";
      return 2;
    }
    std::ofstream out(path);
    out << minDiagonal(a, n, m) << '\n';
    spiral(a, n, m);
    out << n << ' ' << m;
    for (std::size_t i = 0; i < size; ++i)
    {
      out << ' ' << a[i];
    }
    out << '\n';
    out.close();
    if (!out)
    {
      std::cerr << "Cannot write output file\n";
      return 2;
    }
    return 0;
  }
}

int main(int argc, char ** argv)
{
  if (argc != 4 || (std::strcmp(argv[1], "1") != 0 && std::strcmp(argv[1], "2") != 0))
  {
    std::cerr << "Usage: lab 1|2 input output\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  int n = 0;
  int m = 0;
  const std::size_t limit = 10000;
  const bool fixed = argv[1][0] == '1';
  const auto maxSize = std::numeric_limits< std::size_t >::max() / sizeof(long long);
  if (!(in >> n >> m) || n < 0 || m < 0 || (m > 0 && static_cast< std::size_t >(n) > maxSize / m))
  {
    std::cerr << "Invalid matrix size or input file\n";
    return 2;
  }
  const auto size = static_cast< std::size_t >(n) * m;
  if (fixed)
  {
    if (size > limit)
    {
      std::cerr << "Matrix exceeds the fixed array capacity\n";
      return 2;
    }
    long long a[limit];
    return zorin::run(in, argv[3], a, n, m, size);
  }

  long long * a = nullptr;
  try
  {
    a = new long long[size];
  }
  catch (...)
  {
    std::cerr << "Cannot allocate the matrix\n";
    return 2;
  }
  const int result = zorin::run(in, argv[3], a, n, m, size);
  delete[] a;
  return result;
}
