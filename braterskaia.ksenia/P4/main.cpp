#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstddef>

const int ERR_INPUT = 1;
const std::size_t BUF_SIZE = 1024;

void task_shr_sym(const char* src, char* dst)
{
  bool present[128] = {false};
  bool has_upper = false;
  bool has_lower = false;

  for (std::size_t i = 0; src[i] != '\0'; ++i)
  {
    unsigned char c = static_cast<unsigned char>(src[i]);
    if (std::isalpha(c))
    {
      present[c] = true;
      if (std::isupper(c))
      {
        has_upper = true;
      }
      if (std::islower(c))
      {
        has_lower = true;
      }
    }
  }

  std::size_t k = 0;

  if (has_upper)
  {
    for (char c = 'A'; c <= 'Z'; ++c)
    {
      if (!present[static_cast<unsigned char>(c)])
      {
        dst[k++] = c;
      }
    }
  }

  if (has_lower)
  {
    for (char c = 'a'; c <= 'z'; ++c)
    {
      if (!present[static_cast<unsigned char>(c)])
      {
        dst[k++] = c;
      }
    }
  }

  dst[k] = '\0';
}

void task_lat_rmv(const char* src, char* dst)
{
  std::size_t k = 0;
  for (std::size_t i = 0; src[i] != '\0'; ++i)
  {
    if (!std::isalpha(static_cast<unsigned char>(src[i])))
    {
      dst[k++] = src[i];
    }
  }
  dst[k] = '\0';
}

int main()
{
  char* src = static_cast<char*>(std::malloc(BUF_SIZE));
  char* res1 = static_cast<char*>(std::malloc(BUF_SIZE));
  char* res2 = static_cast<char*>(std::malloc(BUF_SIZE));

  if (src == nullptr || res1 == nullptr || res2 == nullptr)
  {
    std::cerr << "Error: memory allocation failed\n";
    std::free(src);
    std::free(res1);
    std::free(res2);
    return ERR_INPUT;
  }

  for (std::size_t i = 0; i < BUF_SIZE; ++i)
  {
    src[i] = '\0';
    res1[i] = '\0';
    res2[i] = '\0';
  }

  std::cin.getline(src, BUF_SIZE, '\n');

  if (!std::cin && !std::cin.eof())
  {
    std::cerr << "Error: invalid input\n";
    std::free(src);
    std::free(res1);
    std::free(res2);
    return ERR_INPUT;
  }

  task_shr_sym(src, res1);
  task_lat_rmv(src, res2);

  std::cout << res1 << '\n';
  std::cout << res2 << '\n';

  std::free(src);
  std::free(res1);
  std::free(res2);

  return 0;
}
