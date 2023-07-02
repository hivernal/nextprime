#ifndef BIGNUMS_H
#define BIGNUMS_H

#include <boost/multiprecision/gmp.hpp>

namespace nextprime {
class bignums {
protected:
  boost::multiprecision::mpz_int n;
  boost::multiprecision::mpz_int r;
  boost::multiprecision::mpz_int a;
public:
  bignums();
  bignums(boost::multiprecision::mpz_int n, boost::multiprecision::mpz_int r,
          boost::multiprecision::mpz_int a);
  boost::multiprecision::mpz_int get_n();
  void set_n(boost::multiprecision::mpz_int number);
  boost::multiprecision::mpz_int get_r();
  void set_r(boost::multiprecision::mpz_int number);
  boost::multiprecision::mpz_int get_a();
  void set_a(boost::multiprecision::mpz_int number);
};
}

#endif
