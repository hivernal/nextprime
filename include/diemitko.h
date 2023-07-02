#ifndef DIEMITKO_H
#define DIEMITKO_H

#include "bignums.h"

namespace nextprime {
class diemitko : public bignums {
public:
  diemitko();
  diemitko(mpz_class n, mpz_class r, mpz_class a);
  void get_next_prime();
  bool is_prime();
};
}
#endif
