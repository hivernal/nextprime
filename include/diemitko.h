#ifndef DIEMITKO_H
#define DIEMITKO_H

#include <gmp.h>

enum {
  NOT_PRIME,
  PRIME
};

typedef struct {
  mpz_t n;
  mpz_t r;
  mpz_t a;
} bignums_t;

int is_prime(bignums_t* diemitko_nums);
void gen_nextprime(bignums_t* diemitko_nums);

#endif
