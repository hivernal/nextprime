#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "diemitko.h"

void* thread_func(void* thread_data) {
  bignums_t* diemitko_nums = (bignums_t*)thread_data;
  mpz_t tmp;
  mpz_init_set(tmp, diemitko_nums->n);
  mpz_mul(diemitko_nums->n, diemitko_nums->n, diemitko_nums->r);
  mpz_add_ui(diemitko_nums->n, diemitko_nums->n, 1);
  if (is_prime(diemitko_nums)) {
    mpz_clear(tmp);
    pthread_exit((void*)PRIME);
  }
  mpz_sub_ui(diemitko_nums->r, diemitko_nums->r, 4);
  mpz_set(diemitko_nums->n, tmp);
  mpz_clear(tmp);
  pthread_exit((void*)NOT_PRIME);
}

void gen_nextprime(bignums_t* diemitko_nums) {
  mpz_t tmp;
  mpz_init_set(tmp, diemitko_nums->n);
  mpz_mul_ui(diemitko_nums->r, diemitko_nums->n, 4);
  mpz_add_ui(diemitko_nums->r, diemitko_nums->r, 2);

  bignums_t thread_data;
  mpz_init_set(thread_data.n, tmp);
  mpz_init(thread_data.r);
  mpz_init_set(thread_data.a, diemitko_nums->a);
  mpz_sub_ui(thread_data.r, diemitko_nums->r, 2);
  while(1) {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, &thread_data);
    mpz_mul(diemitko_nums->n, diemitko_nums->n, diemitko_nums->r);
    mpz_add_ui(diemitko_nums->n, diemitko_nums->n, 1);
    if (is_prime(diemitko_nums)) {
      pthread_join(thread, NULL);
      break;
    }
    int status = 0;
    pthread_join(thread, (void*)&status);
    if (status) {
      mpz_set(diemitko_nums->n, thread_data.n);
      mpz_set(diemitko_nums->r, thread_data.r);
      break;
    }
    mpz_sub_ui(diemitko_nums->r, diemitko_nums->r, 4);
    mpz_set(diemitko_nums->n, tmp);
  }
  mpz_clear(tmp);
  mpz_clears(thread_data.n, thread_data.r, thread_data.a, NULL);
}

int is_prime(bignums_t* diemitko_nums) {
  mpz_t result, degree;
  mpz_inits(result, degree, NULL);
  mpz_sub_ui(degree, diemitko_nums->n, 1);
  mpz_powm(result, diemitko_nums->a, degree, diemitko_nums->n);
  if (mpz_cmp_si(result, 1) != 0) {
    mpz_clears(result, degree, NULL);
    return NOT_PRIME;
  }
  mpz_powm(result, diemitko_nums->a, diemitko_nums->r, diemitko_nums->n);
  if (mpz_cmp_si(result, 1) == 0) {
    mpz_clears(result, degree, NULL);
    return NOT_PRIME;
  }
  mpz_clears(result, degree, NULL);
  return PRIME;
}
