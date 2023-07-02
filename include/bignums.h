#ifndef BIGNUMS_H
#define BIGNUMS_H

#include <gmp.h>
#include <gmpxx.h>

namespace nextprime {
class bignums {
protected:
  mpz_class n;
  mpz_class r;
  mpz_class a;
public:
  bignums();
  bignums(mpz_class n, mpz_class r, mpz_class a);
  mpz_class get_n();
  void set_n(mpz_class number);
  mpz_class get_r();
  void set_r(mpz_class number);
  mpz_class get_a();
  void set_a(mpz_class number);
};
}

#endif
