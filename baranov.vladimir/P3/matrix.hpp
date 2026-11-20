#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <iosfwd>

namespace baranov
{
  std::size_t countLocalMax(const int* matrix, std::size_t rows, std::size_t cols);
  long long maxSumParallelMain(const int* matrix, std::size_t rows, std::size_t cols);
  bool readAndProcess(std::istream& input, bool dynamic, std::size_t& result, long long& diagonal_sum, bool& empty);
}

#endif
