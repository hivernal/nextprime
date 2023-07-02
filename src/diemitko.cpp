#include "diemitko.h"
#include "thread.h"

Diemitko::Diemitko() {}

Diemitko::Diemitko(mpz_class n, mpz_class r, mpz_class a) : BigNums(n, r, a) {}

void Diemitko::getNextPrime() {
  mpz_class tmp = n;
  r = 4 * n + 2;
  Thread* threads = new Thread[THREADS_NUMBER];
  for (int i = 0; i < THREADS_NUMBER; ++i) {
    threads[i].setN(n);
    threads[i].setA(a);
    threads[i].setR(r - 2 * (i + 1));
  }

  while (true) {
    for (int i = 0; i < THREADS_NUMBER; ++i)
      threads[i].start();
    n = n * r + 1;
    if (isPrime()) {
      delete[] threads;
      return;
    }
    for (int i = 0; i < THREADS_NUMBER; ++i) {
      threads[i].stop();
      if (!threads[i].getStatus())
        continue;
      n = threads[i].getN();
      r = threads[i].getR();
      delete[] threads;
      return;
    }
    n = tmp;
    r -= 2 * (THREADS_NUMBER + 1);
  }
}

bool Diemitko::isPrime() {
  mpz_class result, degree = n - 1;
  mpz_powm(result.get_mpz_t(), a.get_mpz_t(), degree.get_mpz_t(), n.get_mpz_t());
  if (result != 1)
    return false;
  mpz_powm(result.get_mpz_t(), a.get_mpz_t(), r.get_mpz_t(), n.get_mpz_t());
  if (result == 1)
    return false;
  return true;
}
