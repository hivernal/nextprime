#include "thread.hpp"

nextprime::thread::thread() : thr(nullptr), status(false) {}

nextprime::thread::~thread() { stop(); }

nextprime::thread::thread(boost::multiprecision::mpz_int n,
                          boost::multiprecision::mpz_int r,
                          boost::multiprecision::mpz_int a)
    : bignums(n, r, a), thr(nullptr), status(false) {}

void nextprime::thread::thread_func(boost::multiprecision::mpz_int& n,
                                    boost::multiprecision::mpz_int& r,
                                    const boost::multiprecision::mpz_int& a,
                                    bool& status) {
  boost::multiprecision::mpz_int tmp = n;
  n = n * r + 1;
  if (boost::multiprecision::powm(a, n - 1, n) == 1 &&
      boost::multiprecision::powm(a, r, n) != 1) {
    status = true;
    return;
  }
  status = false;
  r -= 2 * (THREADS_NUMBER + 1);
  n = tmp;
}

void nextprime::thread::start() {
  thr = new boost::thread(thread_func, boost::ref(n), boost::ref(r),
                          boost::cref(a), boost::ref(status));
}

void nextprime::thread::stop() {
  if (thr != nullptr) {
    thr->join();
    delete thr;
  }
  thr = nullptr;
}

bool nextprime::thread::get_status() { return status; }
