#include "thread.h"

Thread::Thread() : thread(nullptr), status(false) {}

Thread::Thread(mpz_class n, mpz_class r, mpz_class a) : BigNums(n, r, a),
                                                        thread(nullptr),
                                                        status(false) {}

Thread::~Thread() {
  stop();
}

void Thread::threadFunc(mpz_class &n, mpz_class &r,
                        const mpz_class &a, bool &status) {
  mpz_class tmp = n;
  n = n * r + 1;
  mpz_class result, degree = n - 1;
  mpz_powm(result.get_mpz_t(), a.get_mpz_t(), degree.get_mpz_t(), n.get_mpz_t());
  if (result != 1) {
    status = false;
    r -= 2 * (THREADS_NUMBER + 1);
    n = tmp;
    return;
  }
  mpz_powm(result.get_mpz_t(), a.get_mpz_t(), r.get_mpz_t(), n.get_mpz_t());
  if (result == 1) {
    status = false;
    r -= 2 * (THREADS_NUMBER + 1);
    n = tmp;
    return;
  }
  status = true;
}

void Thread::start() {
  thread = new std::thread(threadFunc, std::ref(n), std::ref(r),
                           std::cref(a), std::ref(status));
}

void Thread::stop() {
  if (thread != nullptr) {
    thread->join();
    delete thread;
    thread = nullptr;
  }
}

bool Thread::getStatus() {
  return status;
}
