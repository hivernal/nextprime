#ifndef THREAD_H
#define THREAD_H

#include "bignums.h"
#include <thread>

#define THREADS_NUMBER 3

class Thread : public BigNums {
  std::thread* thread;
  bool status;
public:
  Thread();
  Thread(mpz_class n, mpz_class r, mpz_class a);
  ~Thread();
  static void threadFunc(mpz_class& n, mpz_class& r,
                         const mpz_class& a, bool& status);
  void start();
  void stop();
  bool getStatus();
};

#endif
