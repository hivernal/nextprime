enum {
  NOT_PRIME,
  PRIME
};

typedef struct {
  mpz_t n;
  mpz_t r;
  mpz_t a;
} big_nums;

int is_prime(big_nums* diemitko_nums);
void gen_nextprime(big_nums* diemitko_nums);
