#ifndef THREAD_H
#define THREAD_H

#define THREADS_NUMBER 3

#include "bignums.hpp"
#include <boost/thread.hpp>

namespace nextprime {
class thread : public bignums {
  boost::thread* thr;
  bool status;
public:
  thread();
  thread(boost::multiprecision::mpz_int n, boost::multiprecision::mpz_int r,
         boost::multiprecision::mpz_int a);
  ~thread();
  static void thread_func(boost::multiprecision::mpz_int& n,
                          boost::multiprecision::mpz_int& r,
                          const boost::multiprecision::mpz_int& a, bool& status);
  void start();
  void stop();
  bool get_status();
};
}

#endif
