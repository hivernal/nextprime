#include "thread.h"

nextprime::thread::thread() : thr(nullptr), status(false) {}

nextprime::thread::~thread() { stop(); }

nextprime::thread::thread(mpz_class n, mpz_class r, mpz_class a)
    : bignums(n, r, a), thr(nullptr), status(false) {}

void nextprime::thread::thread_func(mpz_class& n, mpz_class& r,
                                    const mpz_class& a, bool& status) {
  mpz_class tmp = n;
  n = n * r + 1;
  mpz_class result, degree = n - 1;
  mpz_powm(result.get_mpz_t(), a.get_mpz_t(), degree.get_mpz_t(), n.get_mpz_t());
  if (result != 1) {
    status = false;
    r -= 2 * (threads_number + 1);
    n = tmp;
    return;
  }
  mpz_powm(result.get_mpz_t(), a.get_mpz_t(), r.get_mpz_t(), n.get_mpz_t());
  if (result == 1) {
    status = false;
    r -= 2 * (threads_number + 1);
    n = tmp;
    return;
  }
  status = true;
}

void nextprime::thread::start() {
  thr = new std::thread(thread_func, std::ref(n), std::ref(r),
                           std::cref(a), std::ref(status));
}

void nextprime::thread::stop() {
  if (thr != nullptr) {
    thr->join();
    delete thr;
    thr = nullptr;
  }
}

bool nextprime::thread::get_status() { return status; }
