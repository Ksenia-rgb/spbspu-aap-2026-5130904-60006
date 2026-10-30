#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <new>

namespace usanov
{
  constexpr std::size_t maxFixedSize = 10000;

  bool readSize(std::istream & input, std::size_t & rows, std::size_t & cols)
  {
    long long r = 0;
    long long c = 0;
    if (!(input >> r >> c) || r < 0 || c < 0)
    {
      return false;
    }
    rows = static_cast< std::size_t >(r);
    cols = static_cast< std::size_t >(c);
    return rows == 0 || cols <= SIZE_MAX / rows;
  }

  bool readElements(std::istream & input, int * data, std::size_t count)
  {
    for (std::size_t i = 0; i < count; ++i)
    {
      if (!(input >> data[i]))
      {
        return false;
      }
    }
    return true;
  }

  std::size_t countLocalMax(const int * m, std::size_t rows, std::size_t cols)
  {
    if (rows < 3 || cols < 3)
    {
      return 0;
    }
    std::size_t count = 0;
    for (std::size_t i = 1; i + 1 < rows; ++i)
    {
      for (std::size_t j = 1; j + 1 < cols; ++j)
      {
        const int v = m[i * cols + j];
        bool isMax = true;
        for (std::size_t a = i - 1; a <= i + 1 && isMax; ++a)
        {
          for (std::size_t b = j - 1; b <= j + 1; ++b)
          {
            if ((a != i || b != j) && m[a * cols + b] >= v)
            {
              isMax = false;
              break;
            }
          }
        }
        if (isMax)
        {
          ++count;
        }
      }
    }
    return count;
  }

  bool isLowerTriangular(const int * m, std::size_t rows, std::size_t cols)
  {
    const std::size_t n = (rows < cols) ? rows : cols;
    if (n == 0)
    {
      return false;
    }
    for (std::size_t i = 0; i < n; ++i)
    {
      for (std::size_t j = i + 1; j < n; ++j)
      {
        if (m[i * cols + j] != 0)
        {
          return false;
        }
      }
    }
    return true;
  }

  bool process(const int * m, std::size_t rows, std::size_t cols, std::ostream & output)
  {
    output << countLocalMax(m, rows, cols) << '\n';
    output << (isLowerTriangular(m, rows, cols) ? "true" : "false") << '\n';
    return output.good();
  }

  bool runFixed(std::istream & input, std::ostream & output)
  {
    std::size_t rows = 0;
    std::size_t cols = 0;
    if (!readSize(input, rows, cols) || rows * cols > maxFixedSize)
    {
      return false;
    }
    int data[maxFixedSize] = {};
    if (!readElements(input, data, rows * cols))
    {
      return false;
    }
    return process(data, rows, cols, output);
  }

  bool runDynamic(std::istream & input, std::ostream & output)
  {
    std::size_t rows = 0;
    std::size_t cols = 0;
    if (!readSize(input, rows, cols))
    {
      return false;
    }
    int * data = new (std::nothrow) int[rows * cols];
    if (data == nullptr)
    {
      return false;
    }
    const bool ok = readElements(input, data, rows * cols) && process(data, rows, cols, output);
    delete[] data;
    return ok;
  }
}

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << argv[0] << " num input output\n";
    return 1;
  }

  const char * mode = argv[1];
  if ((mode[0] != '1' && mode[0] != '2') || mode[1] != '\0')
  {
    std::cerr << "Error: first parameter must be 1 or 2\n";
    return 1;
  }
  const char * inputPath = argv[2];
  const char * outputPath = argv[3];

  std::ifstream input(inputPath);
  if (!input)
  {
    std::cerr << "Error: cannot open input file\n";
    return 1;
  }
  std::ofstream output(outputPath);
  if (!output)
  {
    std::cerr << "Error: cannot open output file\n";
    return 1;
  }

  bool ok = false;
  if (mode[0] == '1')
  {
    ok = usanov::runFixed(input, output);
  }
  else
  {
    ok = usanov::runDynamic(input, output);
  }

  if (!ok)
  {
    std::cerr << "Error: input is not a matrix\n";
    return 2;
  }
  return 0;
}
