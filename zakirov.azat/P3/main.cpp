#include <iostream>
#include <fstream>
#include <new>
#include <limits>
#include <cstddef>

namespace zakirov {

  const int arg_error = 1;
  const int data_error = 2;
  const int fixed_array_type = 1;
  const int dynamic_array_type = 2;
  const int required_argc = 4;
  const std::size_t max_size = 10000;

  std::size_t countCols(const int* data, std::size_t rows, std::size_t cols)
  {
    if (rows < 2) {
      return cols;
    }
    std::size_t count = 0;
    for (std::size_t col = 0; col < cols; ++col) {
      bool good = true;
      for (std::size_t row = 1; row < rows; ++row) {
        const std::size_t pos = row * cols + col;
        const std::size_t prev = (row - 1) * cols + col;
        if (data[pos] == data[prev]) {
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

  bool addLayers(int* data, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return true;
    }
    for (std::size_t row = 0; row < rows; ++row) {
      for (std::size_t col = 0; col < cols; ++col) {
        std::size_t layer = row;
        if (col < layer) {
          layer = col;
        }
        if (rows - row - 1 < layer) {
          layer = rows - row - 1;
        }
        if (cols - col - 1 < layer) {
          layer = cols - col - 1;
        }

        const std::size_t pos = row * cols + col;
        const long long value = static_cast< long long >(data[pos]) + static_cast< long long >(layer) + 1;
        if (value > std::numeric_limits< int >::max()) {
          return false;
        }
        data[pos] = static_cast< int >(value);
      }
    }
    return true;
  }

  void write(std::ofstream& output, const int* data, std::size_t rows, std::size_t cols, std::size_t count)
  {
    output << count << '\n';
    output << rows << ' ' << cols << '\n';
    if (cols == 0) {
      return;
    }
    for (std::size_t row = 0; row < rows; ++row) {
      for (std::size_t col = 0; col < cols; ++col) {
        if (col > 0) {
          output << ' ';
        }
        output << data[row * cols + col];
      }
      output << '\n';
    }
  }

  int process(std::ifstream& input, int* data, std::size_t rows, std::size_t cols, const char* output_name)
  {
    const std::size_t size = rows * cols;
    bool good = true;
    for (std::size_t i = 0; i < size; ++i) {
      if (!(input >> data[i])) {
        good = false;
        break;
      }
    }
    if (good) {
      char extra = 0;
      if (input >> extra) {
        good = false;
      }
    }
    if (!good) {
      std::cerr << "не получилось прочитать матрицу из файла\n";
      return data_error;
    }

    const std::size_t count = countCols(data, rows, cols);
    if (!addLayers(data, rows, cols)) {
      std::cerr << "после увеличения получилось слишком большое число\n";
      return data_error;
    }

    std::ofstream output(output_name);
    if (!output) {
      std::cerr << "не удалось открыть файл для результата\n";
      return arg_error;
    }
    write(output, data, rows, cols, count);
    if (!output) {
      std::cerr << "не удалось записать результат в файл\n";
      return arg_error;
    }
    return 0;
  }

  int runFixed(std::ifstream& input, std::size_t rows, std::size_t cols, const char* output_name)
  {
    int data[max_size];
    return process(input, data, rows, cols, output_name);
  }

  int run(const int array_type, const char* input_name, const char* output_name)
  {
    std::ifstream input(input_name);
    if (!input) {
      std::cerr << "не удалось открыть файл с матрицей\n";
      return arg_error;
    }

    int input_rows = 0;
    int input_cols = 0;
    if (!(input >> input_rows >> input_cols) || input_rows < 0 || input_cols < 0) {
      std::cerr << "не получилось прочитать размеры матрицы\n";
      return data_error;
    }
    const std::size_t rows = static_cast< std::size_t >(input_rows);
    const std::size_t cols = static_cast< std::size_t >(input_cols);
    if (cols != 0 && rows > std::numeric_limits< std::size_t >::max() / cols) {
      std::cerr << "не хватило памяти для матрицы\n";
      return data_error;
    }
    const std::size_t size = rows * cols;
    if (array_type == fixed_array_type) {
      if (size > max_size) {
        std::cerr << "в обычном массиве помещается не больше 10000 чисел\n";
        return data_error;
      }
      return runFixed(input, rows, cols, output_name);
    }

    int* const data = new (std::nothrow) int[size];
    if (data == nullptr) {
      std::cerr << "не хватило памяти для матрицы\n";
      return data_error;
    }
    const int result = process(input, data, rows, cols, output_name);
    delete[] data;
    return result;
  }

}

int main(int argc, char* argv[])
{
  if (argc != zakirov::required_argc) {
    std::cerr << "нужно указать три аргумента: 1 или 2, входной файл и выходной файл\n";
    return zakirov::arg_error;
  }

  const int array_type = argv[1][0] - '0';
  const bool valid_type = array_type == zakirov::fixed_array_type || array_type == zakirov::dynamic_array_type;
  if (!valid_type || argv[1][1] != '\0') {
    std::cerr << "первый аргумент должен быть 1 или 2\n";
    return zakirov::arg_error;
  }

  return zakirov::run(array_type, argv[2], argv[3]);
}
