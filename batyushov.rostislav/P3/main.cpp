#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace batyushov
{
  const size_t MAX_SIZE = 10000;
  const int arg_err = 1;
  const int data_err = 2;

  bool sub(int & value, long long step)
  {
    const long long result = static_cast< long long >(value) - step;
    if (result < std::numeric_limits< int >::min())
    {
      return false;
    }
    value = static_cast< int >(result);
    return true;
  }

  bool spiral(int * m, size_t rows, size_t cols)
  {
    size_t top = 0;
    size_t left = 0;
    size_t bottom = rows;
    size_t right = cols;
    long long step = 1;
    while (top < bottom && left < right)
    {
      for (size_t j = left; j < right; ++j)
      {
        if (!sub(m[top * cols + j], step++))
        {
          return false;
        }
      }
      ++top;
      for (size_t i = top; i < bottom; ++i)
      {
        if (!sub(m[i * cols + (right - 1)], step++))
        {
          return false;
        }
      }
      --right;
      if (top < bottom)
      {
        for (size_t j = right; j > left; --j)
        {
          if (!sub(m[(bottom - 1) * cols + (j - 1)], step++))
          {
            return false;
          }
        }
        --bottom;
      }
      if (left < right)
      {
        for (size_t i = bottom; i > top; --i)
        {
          if (!sub(m[(i - 1) * cols + left], step++))
          {
            return false;
          }
        }
        ++left;
      }
    }
    return true;
  }

  size_t longestRow(const int * m, size_t rows, size_t cols)
  {
    size_t maxLen = 0;
    size_t maxRow = 0;
    for (size_t i = 0; i < rows; ++i)
    {
      size_t run = 0;
      for (size_t j = 0; j < cols; ++j)
      {
        if (j > 0 && m[i * cols + j] == m[i * cols + j - 1])
        {
          ++run;
        }
        else
        {
          run = 1;
        }
        if (run > maxLen)
        {
          maxLen = run;
          maxRow = i + 1;
        }
      }
    }
    return maxRow;
  }

  int run(int * data, size_t rows, size_t cols, size_t size, std::istream & in, const char * outFile)
  {
    for (size_t i = 0; i < size; ++i)
    {
      if (!(in >> data[i]))
      {
        std::cerr << "Не получилось прочитать матрицу\n";
        return data_err;
      }
    }

    size_t row = longestRow(data, rows, cols);
    if (!spiral(data, rows, cols))
    {
      std::cerr << "Число получилось слишком маленьким\n";
      return data_err;
    }

    std::ofstream out(outFile);
    out << rows << " " << cols;
    for (size_t i = 0; i < size; ++i)
    {
      out << " " << data[i];
    }
    out << "\n" << row << "\n";
    if (!out)
    {
      std::cerr << "Не удалось записать результат\n";
      return data_err;
    }
    return 0;
  }
}

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Нужно 3 аргумента: номер, входной файл, выходной файл\n";
    return batyushov::arg_err;
  }

  char * end = nullptr;
  long num = std::strtol(argv[1], &end, 10);
  if (end == argv[1] || *end != '\0' || (num != 1 && num != 2))
  {
    std::cerr << "Первый аргумент должен быть 1 или 2\n";
    return batyushov::arg_err;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Не удалось открыть входной файл\n";
    return batyushov::data_err;
  }

  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols) || rows < 0 || cols < 0)
  {
    std::cerr << "Не получилось прочитать матрицу\n";
    return batyushov::data_err;
  }

  const size_t r = static_cast< size_t >(rows);
  const size_t c = static_cast< size_t >(cols);
  if (c != 0 && r > std::numeric_limits< size_t >::max() / c)
  {
    std::cerr << "Матрица слишком большая\n";
    return batyushov::data_err;
  }
  const size_t size = r * c;

  if (num == 1)
  {
    if (size > batyushov::MAX_SIZE)
    {
      std::cerr << "Матрица слишком большая\n";
      return batyushov::data_err;
    }
    int stack[batyushov::MAX_SIZE] = {};
    return batyushov::run(stack, r, c, size, input, argv[3]);
  }

  int * heap = new (std::nothrow) int[size];
  if (heap == nullptr)
  {
    std::cerr << "Не хватило памяти\n";
    return batyushov::data_err;
  }
  int result = batyushov::run(heap, r, c, size, input, argv[3]);
  delete[] heap;
  return result;
}