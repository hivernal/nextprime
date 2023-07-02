#include "diemitko.h"
#include "thread.h"

nextprime::diemitko::diemitko() {}

nextprime::diemitko::diemitko(mpz_class n, mpz_class r, mpz_class a)
    : bignums(n, r, a) {}

void nextprime::diemitko::get_next_prime() {
  mpz_class tmp = n;
  r = 4 * n + 2;
  nextprime::thread* threads = new nextprime::thread[THREADS_NUMBER];
  for (int i = 0; i < THREADS_NUMBER; ++i) {
    threads[i].set_n(n);
    threads[i].set_a(a);
    threads[i].set_r(r - 2 * (i + 1));
  }

  while (true) {
    for (int i = 0; i < THREADS_NUMBER; ++i)
      threads[i].start();
    n = n * r + 1;
    if (is_prime()) {
      delete[] threads;
      return;
    }
    for (int i = 0; i < THREADS_NUMBER; ++i) {
      threads[i].stop();
      if (!threads[i].get_status())
        continue;
      n = threads[i].get_n();
      r = threads[i].get_r();
      delete[] threads;
      return;
    }
    r -= 2 * (THREADS_NUMBER + 1);
    n = tmp;
  }
}

bool nextprime::diemitko::is_prime() {
  mpz_class result, degree = n - 1;
  mpz_powm(result.get_mpz_t(), a.get_mpz_t(), degree.get_mpz_t(),
           n.get_mpz_t());
  if (result != 1)
    return false;
  mpz_powm(result.get_mpz_t(), a.get_mpz_t(), r.get_mpz_t(), n.get_mpz_t());
  if (result == 1)
    return false;
  return true;
}
