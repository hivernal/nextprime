#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include "gen_nextprime.h"

#define HELP                                                                   \
  "Usage: nextprime [OPTION] PRIME_NUMBER.\n"                                  \
  "Generates a prime number greater than PRIME_NUMBER using Diemitko's "       \
  "theorem.\n\n"                                                               \
  "  -f FILE\t\toutput file\n"                                                 \
  "  -s SIZE\t\tsize of number\n"

int main(int argc, char** argv) {
  const char* option_size = NULL;
  const char* option_file = NULL;
    while (--argc > 0 && (*++argv)[0] == '-') {
    char option = *++argv[0];
    switch(option) {
      case 'f':
        if (--argc > 0 && (*++argv)[0] != '-') {
          option_file = *argv;
          break;
        }
        printf(HELP);
        return EXIT_FAILURE;
      case 's':
        if (--argc > 0 && (*++argv)[0] != '-') {
          option_size = *argv;
          break;
        }
      default:
        printf(HELP);
        return EXIT_FAILURE;
    }
  }
  if (argc != 1) {
    printf(HELP);
    return EXIT_FAILURE;
  }

  long size = 1;
  if (option_size != NULL && (size = strtol(option_size, NULL, 10)) <= 0) {
    printf(HELP);
    return EXIT_FAILURE;
  }
  FILE* ouput_stream = stdout;
  if (option_file != NULL && (ouput_stream = fopen(option_file, "w")) == NULL) {
    printf("Error to open file\n");
    return EXIT_FAILURE;
  }
  big_nums diemitko_nums;
  mpz_init_set_str(diemitko_nums.n, *argv, 10);
  if(mpz_cmp_ui(diemitko_nums.n, 0) == 0) {
    printf(HELP);
    if (option_file != NULL)
      fclose(ouput_stream);
    return EXIT_FAILURE;
  }
  mpz_init_set_ui(diemitko_nums.a, 1999);
  mpz_init(diemitko_nums.r);
  fprintf(ouput_stream,"n =\n%s\n\n", *argv);

  do {
    gen_nextprime(&diemitko_nums);
    fprintf(ouput_stream, "R =\n");
    mpz_out_str(ouput_stream, 10, diemitko_nums.r);
    fprintf(ouput_stream, "\nN =\n");
    mpz_out_str(ouput_stream, 10, diemitko_nums.n);
    fprintf(ouput_stream, "\n\n");
  } while (mpz_sizeinbase(diemitko_nums.n, 10) < size);

  mpz_clears(diemitko_nums.n, diemitko_nums.r, diemitko_nums.a, NULL);
  if (option_file != NULL)
    fclose(ouput_stream);
  return EXIT_SUCCESS;
}
