#include "bignums.h"

BigNums::BigNums() : n(3), r(0), a(2) {}

BigNums::BigNums(mpz_class n, mpz_class r, mpz_class a) : n(n), r(r), a(a) {}

mpz_class BigNums::getN() {
  return n;
}

void BigNums::setN(mpz_class n) {
  this->n = n;
}

mpz_class BigNums::getR() {
  return r;
}

void BigNums::setR(mpz_class r) {
  this->r = r;
}

mpz_class BigNums::getA() {
  return a;
}

void BigNums::setA(mpz_class a) {
  this->a = a;
}
