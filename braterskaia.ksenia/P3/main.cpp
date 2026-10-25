#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>

const int ERR_INPUT = 1;
const std::size_t MAX_DIM = 100;

bool check_args(const int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: expected 3 arguments (mode, input, output)\n";
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

bool run(std::istream& input, std::ostream& output, const int mode)
{
  std::size_t rows = 0;
  std::size_t cols = 0;

  if (!(input >> rows >> cols))
  {
    return false;
  }

  if (rows == 0 || cols == 0)
  {
    output << 0 << '\n';
    return true;
  }

  if (rows > MAX_DIM || cols > MAX_DIM)
  {
    return false;
  }

  std::size_t count = 0;
  const long long start_offset = -(long long)rows + 1;
  const long long end_offset = (long long)cols;

  if (mode == 2)
  {
    int** matrix = new int*[rows];
    for (std::size_t i = 0; i < rows; ++i)
    {
      matrix[i] = new int[cols];
    }

    for (std::size_t i = 0; i < rows; ++i)
    {
      for (std::size_t j = 0; j < cols; ++j)
      {
        input >> matrix[i][j];
      }
    }

    for (long long offset = start_offset; offset < end_offset; ++offset)
    {
      if (offset == 0)
      {
        continue;
      }

      bool has_zero = false;
      bool has_elements = false;

      for (std::size_t i = 0; i < rows; ++i)
      {
        long long j = (long long)i + offset;
        if (j >= 0 && j < (long long)cols)
        {
          has_elements = true;
          if (matrix[i][j] == 0)
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

    output << count << '\n';

    for (std::size_t i = 0; i < rows; ++i)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
  else if (mode == 1)
  {
    int matrix[MAX_DIM][MAX_DIM];

    for (std::size_t i = 0; i < rows; ++i)
    {
      for (std::size_t j = 0; j < cols; ++j)
      {
        input >> matrix[i][j];
      }
    }

    for (long long offset = start_offset; offset < end_offset; ++offset)
    {
      if (offset == 0)
      {
        continue;
      }

      bool has_zero = false;
      bool has_elements = false;

      for (std::size_t i = 0; i < rows; ++i)
      {
        long long j = (long long)i + offset;
        if (j >= 0 && j < (long long)cols)
        {
          has_elements = true;
          if (matrix[i][j] == 0)
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

    output << count << '\n';
  }

  return true;
}

int main(int argc, char* argv[])
{
  if (!check_args(argc, argv))
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

  const int mode = std::stoi(argv[1]);

  if (!run(in_file, out_file, mode))
  {
    std::cerr << "Error: invalid matrix data\n";
    return ERR_INPUT;
  }

  return 0;
}
