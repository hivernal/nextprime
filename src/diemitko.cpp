#include "thread.hpp"
#include "diemitko.hpp"

nextprime::diemitko::diemitko() {}

nextprime::diemitko::diemitko(boost::multiprecision::mpz_int n,
                              boost::multiprecision::mpz_int r,
                              boost::multiprecision::mpz_int a)
    : bignums(n, r, a) {}

void nextprime::diemitko::get_next_prime() {
  boost::multiprecision::mpz_int tmp = n;
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
  if (boost::multiprecision::powm(a, n - 1, n) != 1)
    return false;
  if (boost::multiprecision::powm(a, r, n) == 1)
    return false;
  return true;
}

