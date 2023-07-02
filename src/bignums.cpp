#include "bignums.h"

nextprime::bignums::bignums() : n(3), r(0), a(2) {}

nextprime::bignums::bignums(mpz_class n, mpz_class r, mpz_class a)
    : n(n), r(r), a(a) {}

mpz_class nextprime::bignums::get_n() { return n; }

void nextprime::bignums::set_n(mpz_class number) { n = number; }

mpz_class nextprime::bignums::get_r() { return r; }

void nextprime::bignums::set_r(mpz_class number) { r = number; }

mpz_class nextprime::bignums::get_a() { return a; }

void nextprime::bignums::set_a(mpz_class number) { a = number; }
