#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "diemitko.h"

#define N_THREADS 3

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
  mpz_sub_ui(diemitko_nums->r, diemitko_nums->r, 2 * (N_THREADS + 1));
  mpz_set(diemitko_nums->n, tmp);
  mpz_clear(tmp);
  pthread_exit((void*)NOT_PRIME);
}

void gen_nextprime(bignums_t* diemitko_nums) {
  mpz_t tmp;
  mpz_init_set(tmp, diemitko_nums->n);
  mpz_mul_ui(diemitko_nums->r, diemitko_nums->n, 4);
  mpz_add_ui(diemitko_nums->r, diemitko_nums->r, 2);

  bignums_t* threads_data = malloc(sizeof(bignums_t) * N_THREADS);
  for (int i = 0; i < N_THREADS; ++i) {
    mpz_init_set(threads_data[i].n, tmp);
    mpz_init(threads_data[i].r);
    mpz_init_set(threads_data[i].a, diemitko_nums->a);
    mpz_sub_ui(threads_data[i].r, diemitko_nums->r, 2*(i + 1));
  }

  pthread_t* threads = malloc(sizeof(pthread_t) * N_THREADS);
  while(1) {
    for (int i = 0; i < N_THREADS; ++i)
      pthread_create(&threads[i], NULL, thread_func, &threads_data[i]);

    mpz_mul(diemitko_nums->n, diemitko_nums->n, diemitko_nums->r);
    mpz_add_ui(diemitko_nums->n, diemitko_nums->n, 1);
    if (is_prime(diemitko_nums)) {
      for (int i = 0; i < N_THREADS; ++i)
        pthread_join(threads[i], NULL);
      break;
    }

    int status = 0;
    for (int i = 0; i < N_THREADS; ++i) {
      pthread_join(threads[i], (void*)&status);
      if (!status)
        continue;
      mpz_set(diemitko_nums->n, threads_data[i].n);
      mpz_set(diemitko_nums->r, threads_data[i].r);
      ++i;
      for(; i < N_THREADS; ++i)
        pthread_join(threads[i], NULL);
      break;
    }
    if (status)
      break;
    mpz_sub_ui(diemitko_nums->r, diemitko_nums->r, 2 * (N_THREADS + 1));
    mpz_set(diemitko_nums->n, tmp);
  }

  mpz_clear(tmp);
  for (int i = 0; i < N_THREADS; ++i)
    mpz_clears(threads_data[i].n, threads_data[i].r, threads_data[i].a, NULL);
  free(threads_data);
  free(threads);
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
