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
  const char* option_size = nullptr;
  const char* option_file = nullptr;
  while (--argc > 0 && (*++argv)[0] == '-') {
    char option = *++argv[0];
    switch (option) {
    case 'f':
      if (--argc > 0 && (*++argv)[0] != '-') {
        option_file = *argv;
        break;
      }
      std::cout << HELP;
      return EXIT_FAILURE;
    case 's':
      if (--argc > 0 && (*++argv)[0] != '-') {
        option_size = *argv;
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
  if (option_size != nullptr &&
      (size = std::strtol(option_size, nullptr, 10)) <= 0) {
    std::cout << HELP;
    return EXIT_FAILURE;
  }
  nextprime::diemitko diemitko_nums(0, 0, 1999);
  try {
    diemitko_nums.set_n(mpz_class(*argv));
  } catch(std::invalid_argument) {
    std::cout << HELP;
    return EXIT_FAILURE;
  }
  std::ostream out_stream(std::cout.rdbuf());
  std::ofstream out_file(option_file);
  if (!out_file.fail())
    out_stream.rdbuf(out_file.rdbuf());

  out_stream << "N =" << std::endl << diemitko_nums.get_n() << std::endl << std::endl;
  do {
    diemitko_nums.get_next_prime();
    out_stream << "R =" << std::endl;
    out_stream << diemitko_nums.get_r() << std::endl;
    out_stream << "N =" << std::endl;
    out_stream << diemitko_nums.get_n() << std::endl << std::endl;
  } while (diemitko_nums.get_n().get_str().length() < size);

  if (out_file.is_open())
    out_file.close();
  return EXIT_SUCCESS;
}
