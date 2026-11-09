#include <iostream>
#include <fstream>
#include <new>
#include <limits>

namespace zakirov {

  const int arg_error = 1;
  const int data_error = 2;
  const int max_size = 10000;

  int countCols(const int* data, int rows, int cols)
  {
    if (rows < 2) {
      return cols;
    }
    int count = 0;
    for (int col = 0; col < cols; ++col) {
      bool good = true;
      for (int row = 1; row < rows; ++row) {
        const long long pos = static_cast< long long >(row) * cols + col;
        const long long prev = static_cast< long long >(row - 1) * cols + col;
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

  bool addLayers(int* data, int rows, int cols)
  {
    if (rows == 0 || cols == 0) {
      return true;
    }
    for (int row = 0; row < rows; ++row) {
      for (int col = 0; col < cols; ++col) {
        int layer = row;
        if (col < layer) {
          layer = col;
        }
        if (rows - row - 1 < layer) {
          layer = rows - row - 1;
        }
        if (cols - col - 1 < layer) {
          layer = cols - col - 1;
        }

        const long long pos = static_cast< long long >(row) * cols + col;
        const long long value = static_cast< long long >(data[pos]) + layer + 1;
        if (value > std::numeric_limits< int >::max()) {
          return false;
        }
        data[pos] = static_cast< int >(value);
      }
    }
    return true;
  }

  void write(std::ofstream& output, const int* data, int rows, int cols, int count)
  {
    output << count << '\n';
    output << rows << ' ' << cols << '\n';
    if (cols == 0) {
      return;
    }
    for (int row = 0; row < rows; ++row) {
      for (int col = 0; col < cols; ++col) {
        if (col > 0) {
          output << ' ';
        }
        output << data[static_cast< long long >(row) * cols + col];
      }
      output << '\n';
    }
  }

  int run(int array_type, const char* input_name, const char* output_name)
  {
    std::ifstream input(input_name);
    if (!input) {
      std::cerr << "Не удалось открыть файл с матрицей\n";
      return arg_error;
    }

    int rows = 0;
    int cols = 0;
    if (!(input >> rows >> cols) || rows < 0 || cols < 0) {
      std::cerr << "Не получилось прочитать размеры матрицы\n";
      return data_error;
    }
    const long long size = static_cast< long long >(rows) * cols;
    if (array_type == 1 && size > max_size) {
      std::cerr << "В обычном массиве помещается не больше 10000 чисел\n";
      return data_error;
    }

    int fixed[max_size];
    int* data = fixed;
    if (array_type == 2) {
      data = new (std::nothrow) int[size];
      if (data == nullptr) {
        std::cerr << "Не хватило памяти для матрицы\n";
        return data_error;
      }
    }

    bool good = true;
    for (long long i = 0; i < size; ++i) {
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
      if (array_type == 2) {
        delete[] data;
      }
      std::cerr << "Не получилось прочитать матрицу из файла\n";
      return data_error;
    }

    const int count = countCols(data, rows, cols);
    if (!addLayers(data, rows, cols)) {
      if (array_type == 2) {
        delete[] data;
      }
      std::cerr << "После увеличения получилось слишком большое число\n";
      return data_error;
    }

    std::ofstream output(output_name);
    if (!output) {
      if (array_type == 2) {
        delete[] data;
      }
      std::cerr << "Не удалось открыть файл для результата\n";
      return arg_error;
    }
    write(output, data, rows, cols, count);
    output.close();
    if (array_type == 2) {
      delete[] data;
    }
    if (!output) {
      std::cerr << "Не удалось записать результат в файл\n";
      return arg_error;
    }
    return 0;
  }

}

int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "Нужно указать три аргумента: 1 или 2, входной файл и выходной файл\n";
    return zakirov::arg_error;
  }

  int array_type = 0;
  if (argv[1][0] == '1' && argv[1][1] == '\0') {
    array_type = 1;
  } else if (argv[1][0] == '2' && argv[1][1] == '\0') {
    array_type = 2;
  } else {
    std::cerr << "Первый аргумент должен быть 1 или 2\n";
    return zakirov::arg_error;
  }

  return zakirov::run(array_type, argv[2], argv[3]);
}
