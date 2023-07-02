#include "bignums.hpp"

nextprime::bignums::bignums() : n(3), r(0), a(2) {}

nextprime::bignums::bignums(boost::multiprecision::mpz_int n,
                            boost::multiprecision::mpz_int r,
                            boost::multiprecision::mpz_int a)
    : n(n), r(r), a(a) {}

boost::multiprecision::mpz_int nextprime::bignums::get_n() { return n; }

void nextprime::bignums::set_n(boost::multiprecision::mpz_int number) {
  n = number;
}

boost::multiprecision::mpz_int nextprime::bignums::get_r() { return r; }

void nextprime::bignums::set_r(boost::multiprecision::mpz_int number) {
  r = number;
}

boost::multiprecision::mpz_int nextprime::bignums::get_a() { return a; }

void nextprime::bignums::set_a(boost::multiprecision::mpz_int number) {
  a = number;
}
