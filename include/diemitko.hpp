#ifndef DIEMITKO_H
#define DIEMITKO_H

#include "bignums.hpp"

namespace nextprime {
class diemitko : public bignums {
public:
  diemitko();
  diemitko(boost::multiprecision::mpz_int n, boost::multiprecision::mpz_int r,
           boost::multiprecision::mpz_int a);
  void get_next_prime();
  bool is_prime();
};
}
#endif
