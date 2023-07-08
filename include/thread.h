#ifndef THREAD_H
#define THREAD_H


#include "bignums.h"
#include <thread>

namespace nextprime {
enum { 
  threads_number = 3
};

class thread : public bignums {
  std::thread* thr;
  bool status;
public:
  thread();
  thread(mpz_class n, mpz_class r, mpz_class a);
  ~thread();
  static void thread_func(mpz_class& n, mpz_class& r, const mpz_class& a,
                          bool& status);
  void start();
  void stop();
  bool get_status();
};
}

#endif
