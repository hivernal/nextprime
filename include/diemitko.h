#ifndef DIEMITKO_H
#define DIEMITKO_H

#include "bignums.h"

class Diemitko : public BigNums {
public:
  Diemitko();
  Diemitko(mpz_class n, mpz_class r, mpz_class a);
  bool isPrime();
  void getNextPrime();
};

#endif
