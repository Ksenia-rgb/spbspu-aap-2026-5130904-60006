#include <iostream>
#include <fstream>
#include <cstddef>

namespace chizhova
{
  static int run_task_16()
  {
    int x = 0;
    int min_val = 0;
    std::size_t count = 0;
    bool is_first = true;

    std::cout << "Enter sequence (ends with 0):\n";
    while (std::cin >> x)
    {
      if (x == 0) break;
      if (is_first)
      {
        min_val = x;
        count = 1;
        is_first = false;
      }
      else
      {
        if (x < min_val)
        {
          min_val = x;
          count = 1;
        }
        else if (x == min_val) ++count;
      }
    }
    if (std::cin.bad() || (std::cin.fail() && !std::cin.eof()))
    {
      std::cerr << "Error: invalid sequence input\n";
      return 2;
    }
    std::cout << count << '\n';
    return 0;
  }

  static std::size_t get_cnt_col_nsm(const int* const* matrix, const std::size_t rows, const std::size_t cols)
  {
    std::size_t count = 0;
    for (std::size_t c = 0; c < cols; ++c)
    {
      bool has_identical = false;
      for (std::size_t r = 1; r < rows; ++r)
      {
        if (matrix[r][c] == matrix[r - 1][c])
        {
          has_identical = true;
          break;
        }
      }
      if (!has_identical) ++count;
    }
    return count;
  }

  static int process_matrix(std::istream& input, std::ostream& output, const bool use_dynamic)
  {
    std::size_t rows = 0;
    std::size_t cols = 0;

    if (!(input >> rows >> cols)) return 2;
    if (rows == 0 || cols == 0)
    {
      if (rows == 0 && cols == 0)
      {
        output << 0 << '\n';
        return 0;
      }
      return 2;
    }
    const std::size_t max_stack_elements = 10000;
    if (!use_dynamic && rows * cols > max_stack_elements) return 2;

    int* flat_matrix = nullptr;
    int** matrix = nullptr;
    int static_flat[max_stack_elements];
    int* static_rows[max_stack_elements];

    if (use_dynamic)
    {
      flat_matrix = new int[rows * cols];
      matrix = new int*[rows];
      for (std::size_t i = 0; i < rows; ++i) matrix[i] = flat_matrix + i * cols;
    }
    else
    {
      flat_matrix = static_flat;
      matrix = static_rows;
      for (std::size_t i = 0; i < rows; ++i) matrix[i] = flat_matrix + i * cols;
    }

    bool read_success = true;
    for (std::size_t r = 0; r < rows; ++r)
    {
      for (std::size_t c = 0; c < cols; ++c)
      {
        if (!(input >> matrix[r][c]))
        {
          read_success = false;
          break;
        }
      }
      if (!read_success) break;
    }
    if (!read_success)
    {
      if (use_dynamic)
      {
        delete[] matrix;
        delete[] flat_matrix;
      }
      return 2;
    }
    std::size_t cnt_col = get_cnt_col_nsm(matrix, rows, cols);
    output << cnt_col << '\n';
    if (use_dynamic)
    {
      delete[] matrix;
      delete[] flat_matrix;
    }
    return 0;
  }
}

int main(int argc, char** argv)
{
  if (argc == 1)
  {
    std::cout << "Select task:\n1 - Sequence (P1)\n2 - Matrix (P3)\nChoice: ";
    int choice = 0;
    if (!(std::cin >> choice)) return 1;
    std::cin.ignore(); // Очистка буфера после ввода числа

    if (choice == 1) return chizhova::run_task_16();
    
    if (choice == 2)
    {
      std::cout << "Select mode (1 - static, 2 - dynamic): ";
      int mode = 0;
      if (!(std::cin >> mode)) return 1;
      std::cin.ignore();
      bool use_dynamic = (mode == 2);
      
      std::cout << "Enter input filename: ";
      char in_name[256];
      std::cin >> in_name;
      std::cout << "Enter output filename: ";
      char out_name[256];
      std::cin >> out_name;

      std::ifstream input(in_name);
      if (!input) { std::cerr << "Error: cannot open input\n"; return 2; }
      std::ofstream output(out_name);
      if (!output) { std::cerr << "Error: cannot open output\n"; return 2; }

      int result = chizhova::process_matrix(input, output, use_dynamic);
      if (result != 0) std::cerr << "Error: invalid matrix data\n";
      return result;
    }
    std::cerr << "Error: invalid choice\n";
    return 1;
  }

  if (argc != 4) return 1;
  const char* mode_str = argv[1];
  if (mode_str[0] == '\0' || mode_str[1] != '\0') return 1;
  bool use_dynamic = false;
  if (mode_str[0] == '1') use_dynamic = false;
  else if (mode_str[0] == '2') use_dynamic = true;
  else return 1;

  std::ifstream input(argv[2]);
  if (!input) return 2;
  std::ofstream output(argv[3]);
  if (!output) return 2;
  return chizhova::process_matrix(input, output, use_dynamic);
}