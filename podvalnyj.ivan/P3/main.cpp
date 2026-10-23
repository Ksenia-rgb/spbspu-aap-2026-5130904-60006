#include <iostream>
#include <cstddef>
#include <fstream>
#include <new>
#include <stdexcept>

namespace podvalnyj
{
  const std::size_t MAKS_RAZMER = 10000;

  void proverkaKolva(int argc)
  {
    if (argc < 4)
    {
      throw std::logic_error("Not enough arguments");
    }
    if (argc > 4)
    {
      throw std::logic_error("Too many arguments");
    }
  }

  bool etoChislo(const char * argument)
  {
    if (argument[0] == '\0')
    {
      return false;
    }
    for (std::size_t i = 0; argument[i] != '\0'; ++i)
    {
      if (argument[i] < '0' || argument[i] > '9')
      {
        return false;
      }
    }
    return true;
  }

  int poluchitNomer(const char * argument)
  {
    if (!etoChislo(argument))
    {
      throw std::logic_error("First parameter is not a number");
    }
    if (argument[1] != '\0' || (argument[0] != '1' && argument[0] != '2'))
    {
      throw std::logic_error("First parameter is out of range");
    }
    return argument[0] - '0';
  }

  void chtenieRazmera(std::ifstream & vhod, std::size_t & kolvo_strok, std::size_t & kolvo_stolbcov)
  {
    int chislo_strok = 0;
    int chislo_stolbcov = 0;
    vhod >> chislo_strok >> chislo_stolbcov;
    if (vhod.fail() || chislo_strok < 0 || chislo_stolbcov < 0)
    {
      throw std::logic_error("Invalid matrix size");
    }
    if ((chislo_strok == 0) != (chislo_stolbcov == 0))
    {
      throw std::logic_error("Invalid matrix size");
    }
    kolvo_strok = chislo_strok;
    kolvo_stolbcov = chislo_stolbcov;
  }

  void chtenieMatricy(std::ifstream & vhod, int * matrica, std::size_t razmer)
  {
    for (std::size_t i = 0; i < razmer; ++i)
    {
      vhod >> matrica[i];
      if (vhod.fail())
      {
        throw std::logic_error("Invalid matrix elements");
      }
    }
    char lishnee = 0;
    vhod >> lishnee;
    if (!vhod.eof())
    {
      throw std::logic_error("Extra data in input file");
    }
  }

  int * sozdatMatricu(std::size_t razmer)
  {
    return new int[razmer];
  }

  void udalitMatricu(const int * matrica)
  {
    delete[] matrica;
  }

  bool estOdinakovye(const int * stroka, std::size_t kolvo_stolbcov)
  {
    for (std::size_t j = 1; j < kolvo_stolbcov; ++j)
    {
      if (stroka[j] == stroka[j - 1])
      {
        return true;
      }
    }
    return false;
  }

  std::size_t dlinaSerii(const int * stroka, std::size_t kolvo_stolbcov)
  {
    if (kolvo_stolbcov == 0)
    {
      return 0;
    }
    std::size_t tekushaya = 1;
    std::size_t maks_dlina = 1;
    for (std::size_t j = 1; j < kolvo_stolbcov; ++j)
    {
      if (stroka[j] == stroka[j - 1])
      {
        ++tekushaya;
      }
      else
      {
        tekushaya = 1;
      }
      if (tekushaya > maks_dlina)
      {
        maks_dlina = tekushaya;
      }
    }
    return maks_dlina;
  }

  std::size_t strokiBezPovtorov(const int * matrica, std::size_t kolvo_strok, std::size_t kolvo_stolbcov)
  {
    std::size_t kolvo = 0;
    for (std::size_t i = 0; i < kolvo_strok; ++i)
    {
      if (!estOdinakovye(matrica + i * kolvo_stolbcov, kolvo_stolbcov))
      {
        ++kolvo;
      }
    }
    return kolvo;
  }

  std::size_t nomerStrokiSeriya(const int * matrica, std::size_t kolvo_strok, std::size_t kolvo_stolbcov)
  {
    std::size_t nomer = 0;
    std::size_t maks_dlina = 0;
    for (std::size_t i = 0; i < kolvo_strok; ++i)
    {
      const std::size_t dlina = dlinaSerii(matrica + i * kolvo_stolbcov, kolvo_stolbcov);
      if (dlina > maks_dlina)
      {
        maks_dlina = dlina;
        nomer = i + 1;
      }
    }
    return nomer;
  }

  void zapisRezultata(const char * imya_fayla, const int * matrica, std::size_t kolvo_strok, std::size_t kolvo_stolbcov)
  {
    std::ofstream vyhod(imya_fayla);
    if (!vyhod.is_open())
    {
      throw std::logic_error("Cannot open output file");
    }
    vyhod << nomerStrokiSeriya(matrica, kolvo_strok, kolvo_stolbcov) << "\n";
    vyhod << strokiBezPovtorov(matrica, kolvo_strok, kolvo_stolbcov) << "\n";
    vyhod.close();
    if (vyhod.fail())
    {
      throw std::logic_error("Cannot write output file");
    }
  }

  void fiksirovanniyMassiv(
      std::ifstream & vhod, const char * imya_fayla, std::size_t kolvo_strok, std::size_t kolvo_stolbcov)
  {
    if (kolvo_stolbcov != 0 && kolvo_strok > MAKS_RAZMER / kolvo_stolbcov)
    {
      throw std::logic_error("Matrix is too big");
    }
    int matrica[MAKS_RAZMER] = {};
    chtenieMatricy(vhod, matrica, kolvo_strok * kolvo_stolbcov);
    zapisRezultata(imya_fayla, matrica, kolvo_strok, kolvo_stolbcov);
  }

  void dinamicheskiyMassiv(
      std::ifstream & vhod, const char * imya_fayla, std::size_t kolvo_strok, std::size_t kolvo_stolbcov)
  {
    int * const matrica = sozdatMatricu(kolvo_strok * kolvo_stolbcov);
    try
    {
      chtenieMatricy(vhod, matrica, kolvo_strok * kolvo_stolbcov);
      zapisRezultata(imya_fayla, matrica, kolvo_strok, kolvo_stolbcov);
    }
    catch (...)
    {
      udalitMatricu(matrica);
      throw;
    }
    udalitMatricu(matrica);
  }

  void obrabotka(int nomer_zadaniya, const char * imya_vhoda, const char * imya_vyhoda)
  {
    std::ifstream vhod(imya_vhoda);
    if (!vhod.is_open())
    {
      throw std::logic_error("Cannot open input file");
    }
    std::size_t kolvo_strok = 0;
    std::size_t kolvo_stolbcov = 0;
    chtenieRazmera(vhod, kolvo_strok, kolvo_stolbcov);
    if (nomer_zadaniya == 1)
    {
      fiksirovanniyMassiv(vhod, imya_vyhoda, kolvo_strok, kolvo_stolbcov);
    }
    else
    {
      dinamicheskiyMassiv(vhod, imya_vyhoda, kolvo_strok, kolvo_stolbcov);
    }
  }
}

int main(int argc, char ** argv)
{
  int nomer_zadaniya = 0;
  try
  {
    podvalnyj::proverkaKolva(argc);
    nomer_zadaniya = podvalnyj::poluchitNomer(argv[1]);
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  try
  {
    podvalnyj::obrabotka(nomer_zadaniya, argv[2], argv[3]);
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Not enough memory\n";
    return 2;
  }
  return 0;
}
