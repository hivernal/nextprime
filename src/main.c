#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>

#include "gen_nextprime.h"

void print_help() {
  printf("Usage: nextprime PRIME_NUMBER [SIZE]\n");
  printf("Generate prime number bigger than PRIME_NUMBER\n");
}

int main(int argc, char** argv) {
  if (argc < 2 || argc > 3 || strcmp(argv[1], "--help") == 0 ||
      strcmp(argv[1], "-h") == 0) {
    print_help();
    return EXIT_SUCCESS;
  }
  long size = 1;
  if (argc == 3)
    size = strtol(argv[2], NULL, 10);
  if (size < 1) {
    print_help();
    return EXIT_SUCCESS;
  }

  big_nums* diemitko_nums = malloc(sizeof(big_nums));
  mpz_init_set_ui(diemitko_nums->a, 1999);
  mpz_init_set_str(diemitko_nums->n, argv[1], 10);
  mpz_sub_ui(diemitko_nums->deg, diemitko_nums->deg, 1);
  mpz_inits(diemitko_nums->r, diemitko_nums->deg, diemitko_nums->result, NULL);
  fprintf(stdout,"n =\n%s\n\n", argv[1]);
  clock_t begin = clock();
  do {
    gen_nextprime(diemitko_nums);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stdout, "R =\n");
    mpz_out_str(stdout, 10, diemitko_nums->r);
    fprintf(stdout, "\nN =\n");
    mpz_out_str(stdout, 10, diemitko_nums->n);
    fprintf(stdout, "\n");
    if (time_spent < 60.0f)
      fprintf(stdout, "Time = %.4lf seconds\n\n", time_spent);
    else if(time_spent < 3600.0f)
      fprintf(stdout, "Time = %.2lf minutes\n\n", time_spent/60);
  } while (mpz_sizeinbase(diemitko_nums->n, 10) < size);
  mpz_clears(diemitko_nums->n, diemitko_nums->r, diemitko_nums->result,
             diemitko_nums->deg, diemitko_nums->a, NULL);
  free(diemitko_nums);
  return EXIT_SUCCESS;
}
