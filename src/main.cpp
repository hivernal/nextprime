#include <iostream>
#include <fstream>
#include "diemitko.h"

#define HELP                                                                   \
  "Usage: nextprime [OPTION] PRIME_NUMBER.\n"                                  \
  "Generates a prime number greater than PRIME_NUMBER using Diemitko's "       \
  "theorem.\n\n"                                                               \
  "  -f FILE\t\toutput file\n"                                                 \
  "  -s SIZE\t\tsize of number\n"

int main(int argc, char** argv) {
  const char* optionSize = nullptr;
  const char* optionFile = nullptr;
    while (--argc > 0 && (*++argv)[0] == '-') {
    char option = *++argv[0];
    switch(option) {
      case 'f':
        if (--argc > 0 && (*++argv)[0] != '-') {
          optionFile = *argv;
          break;
        }
        std::cout << HELP;
        return EXIT_FAILURE;
      case 's':
        if (--argc > 0 && (*++argv)[0] != '-') {
          optionSize = *argv;
          break;
        }
      default:
        std::cout << HELP;
        return EXIT_FAILURE;
    }
  }
  if (argc != 1) {
    std::cout << HELP;
    return EXIT_FAILURE;
  }

  long size = 1;
  if (optionSize != nullptr && (size = std::strtol(optionSize, nullptr, 10)) <= 0) {
    std::cout << HELP;
    return EXIT_FAILURE;
  }
  mpz_class prime;
  prime.set_str(*argv, 10);
  if(prime == 0) {
    std::cout << HELP;
    return EXIT_FAILURE;
  }
  std::ostream outStream(std::cout.rdbuf());
  std::ofstream outFile(optionFile);
  if (!outFile.fail())
    outStream.rdbuf(outFile.rdbuf());
  Diemitko diemitko_nums(prime, 0, 1999);

  outStream << "N =" << std::endl << diemitko_nums.getN() << std::endl << std::endl;
  do {
    diemitko_nums.getNextPrime();
    outStream << "R =" << std::endl;
    outStream << diemitko_nums.getR() << std::endl;
    outStream << "N =" << std::endl;
    outStream << diemitko_nums.getN() << std::endl << std::endl;
  } while (diemitko_nums.getN().get_str().length() < size);

  if (outFile.is_open())
    outFile.close();
  return EXIT_SUCCESS;
}
