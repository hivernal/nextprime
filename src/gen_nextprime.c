#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <pthread.h>
#include <time.h>

#include "gen_nextprime.h"

void* thread_func(void* thread_data) {
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  mpz_t result;
  mpz_init(result);
  const big_nums* diemitko_nums = (big_nums*)thread_data;
  mpz_powm(result, diemitko_nums->a, diemitko_nums->r, diemitko_nums->n);
  if (mpz_cmp_si(result, 1) != 0) {
    mpz_clear(result);
    pthread_exit((void*)PRIME);
  }
  mpz_clear(result);
  pthread_exit((void*)NOT_PRIME);
}

void gen_nextprime(big_nums* diemitko_nums) {
  // gmp_randstate_t rand;
  // gmp_randinit_mt(rand);
  // long seed;
  // gmp_randseed_ui(rand, seed);
  // mpz_t r_max;
  // mpz_init_set(r_max, diemitko_nums->n);
  // mpz_mul_ui(r_max, r_max, 4);
  // mpz_add_ui(r_max, r_max, 4);
  mpz_set(diemitko_nums->r, diemitko_nums->n);
  mpz_mul_ui(diemitko_nums->r, diemitko_nums->r, 4);
  mpz_add_ui(diemitko_nums->r, diemitko_nums->r, 2);
  mpz_t tmp;
  mpz_init_set(tmp, diemitko_nums->n);
  while(1) {
    // mpz_urandomm(diemitko_nums->r, rand, r_max);
    // mpz_clrbit(diemitko_nums->r, 0);
    // if (mpz_cmp_ui(diemitko_nums->r, 2) < 0)
    //   mpz_add_ui(diemitko_nums->r, diemitko_nums->r, 2);
    mpz_mul(diemitko_nums->n, diemitko_nums->n, diemitko_nums->r);
    mpz_add_ui(diemitko_nums->n, diemitko_nums->n, 1);
    mpz_set(diemitko_nums->deg, diemitko_nums->n);
    mpz_sub_ui(diemitko_nums->deg, diemitko_nums->deg, 1);
    if (is_prime(diemitko_nums))
        break;
    mpz_sub_ui(diemitko_nums->r, diemitko_nums->r, 2);
    mpz_set(diemitko_nums->n, tmp);
  }
  mpz_clear(tmp);
  // mpz_clear(r_max);
  // gmp_randclear(rand);
}

int is_prime(big_nums* diemitko_nums) {
  // pthread_t thread;
  // pthread_create(&thread, NULL, thread_func, (void*)diemitko_nums);
  // mpz_init(result);
  // mpz_init_set(deg, diemitko_nums->n);
  // mpz_sub_ui(deg, deg, 1);
  mpz_powm(diemitko_nums->result, diemitko_nums->a, diemitko_nums->deg, diemitko_nums->n);
  if (mpz_cmp_si(diemitko_nums->result, 1) != 0 ) {
    // pthread_cancel(thread);
    // mpz_clears(result, deg, NULL);
    return NOT_PRIME;
  }
  // int thread_result;
  // pthread_join(thread, (void*)&thread_result);
  // if (!thread_result)
  //   return NOT_PRIME;
  mpz_powm(diemitko_nums->result, diemitko_nums->a, diemitko_nums->r, diemitko_nums->n);
  if (mpz_cmp_si(diemitko_nums->result, 1) == 0) {
    // mpz_clears(result, deg, NULL);
    return NOT_PRIME;
  }
  // mpz_clears(result, deg, NULL);
  return PRIME;
}
