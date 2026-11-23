#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>

const int ERR_INPUT = 1;
const int ERR_MATRIX = 2;
const std::size_t MAX_DIM = 100;

bool checkArgs(const int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: wrong number of arguments\n";
    return false;
  }

  const std::string mode = argv[1];
  if (mode != "1" && mode != "2")
  {
    std::cerr << "Error: mode must be 1 or 2\n";
    return false;
  }

  return true;
}

bool readMatrix(std::istream& in, int* matrix, const std::size_t rows, const std::size_t cols)
{
  for (std::size_t i = 0; i < rows; ++i)
  {
    for (std::size_t j = 0; j < cols; ++j)
    {
      if (!(in >> matrix[i * cols + j]))
      {
        return false;
      }
    }
  }
  return true;
}

void transformSpiral(int* matrix, const std::size_t rows, const std::size_t cols)
{
  int top = 0;
  int bottom = static_cast< int >(rows) - 1;
  int left = 0;
  int right = static_cast< int >(cols) - 1;
  int counter = 1;

  while (top <= bottom && left <= right)
  {
    for (int i = top; i <= bottom; ++i)
    {
      matrix[i * cols + left] += counter++;
    }
    left++;

    for (int i = left; i <= right; ++i)
    {
      matrix[bottom * cols + i] += counter++;
    }
    bottom--;

    if (left <= right)
    {
      for (int i = bottom; i >= top; --i)
      {
        matrix[i * cols + right] += counter++;
      }
      right--;
    }

    if (top <= bottom)
    {
      for (int i = right; i >= left; --i)
      {
        matrix[top * cols + i] += counter++;
      }
      top++;
    }
  }
}

int countDiagonals(const int* matrix, const std::size_t rows, const std::size_t cols)
{
  int count = 0;
  const long long startOffset = -static_cast< long long >(rows) + 1;
  const long long endOffset = static_cast< long long >(cols);

  for (long long offset = startOffset; offset < endOffset; ++offset)
  {
    if (offset == 0)
    {
      continue;
    }

    bool has_zero = false;
    bool has_elements = false;

    for (std::size_t i = 0; i < rows; ++i)
    {
      const long long j = static_cast< long long >(i) + offset;
      if (j >= 0 && j < static_cast< long long >(cols))
      {
        has_elements = true;
        if (matrix[i * cols + static_cast< std::size_t >(j)] == 0)
        {
          has_zero = true;
          break;
        }
      }
    }

    if (has_elements && !has_zero)
    {
      ++count;
    }
  }
  return count;
}

int main(int argc, char* argv[])
{
  if (!checkArgs(argc, argv))
  {
    return ERR_INPUT;
  }

  std::ifstream in_file(argv[2]);
  if (!in_file)
  {
    std::cerr << "Error: cannot open input file\n";
    return ERR_INPUT;
  }

  std::ofstream out_file(argv[3]);
  if (!out_file)
  {
    std::cerr << "Error: cannot open output file\n";
    return ERR_INPUT;
  }

  std::size_t rows = 0;
  std::size_t cols = 0;

  if (!(in_file >> rows >> cols))
  {
    std::cerr << "Error: cannot read matrix dimensions\n";
    return ERR_MATRIX;
  }

  if (rows == 0 || cols == 0)
  {
    out_file << 0 << '\n';
    return 0;
  }

  if (rows > MAX_DIM || cols > MAX_DIM)
  {
    std::cerr << "Error: matrix is too large\n";
    return ERR_MATRIX;
  }

  const int mode = std::stoi(argv[1]);

  if (mode == 1)
  {
    int matrix[MAX_DIM * MAX_DIM];

    if (!readMatrix(in_file, matrix, rows, cols))
    {
      std::cerr << "Error: invalid matrix data\n";
      return ERR_MATRIX;
    }

    transformSpiral(matrix, rows, cols);
    const int result = countDiagonals(matrix, rows, cols);
    out_file << result << '\n';
  }
  else if (mode == 2)
  {
    int* const matrix = new int[rows * cols];

    if (!readMatrix(in_file, matrix, rows, cols))
    {
      delete[] matrix;
      std::cerr << "Error: invalid matrix data\n";
      return ERR_MATRIX;
    }

    transformSpiral(matrix, rows, cols);
    const int result = countDiagonals(matrix, rows, cols);
    out_file << result << '\n';

    delete[] matrix;
  }

  return 0;
}
