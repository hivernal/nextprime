#ifndef BIGNUMS_H
#define BIGNUMS_H

#include <gmp.h>
#include <gmpxx.h>

class BigNums {
protected:
  mpz_class n;
  mpz_class r;
  mpz_class a;
public:
  BigNums();
  BigNums(mpz_class n, mpz_class r, mpz_class a);
  mpz_class getN();
  void setN(mpz_class n);
  mpz_class getR();
  void setR(mpz_class r);
  mpz_class getA();
  void setA(mpz_class a);
};

#endif
