#include <iostream>

using namespace std;

typedef long long llong;

llong gcd(llong a, llong b);

class RationalNumber {
private:
  llong molecule;
  llong denominator;
  llong integer;
  int sign;
public:
  RationalNumber(llong molecule, llong denominator) {
    this->integer = 0;
    if (molecule < 0) {
      sign = -1;
      molecule = -molecule;
    }
    else {
      this->sign = 1;
    }
    this->molecule = molecule;
    this->denominator = denominator;
  }

  void simplify() {
    if (this->denominator == 0) return;
    this->molecule = this->molecule + this->integer * this->denominator;
    this->integer = this->molecule / this->denominator;
    this->molecule -= this->integer * this->denominator;
    llong r = gcd(this->molecule, this->denominator);
    this->molecule /= r;
    this->denominator /= r;
  }

  void print() {
    bool flag = false;
    if (this->denominator == 0) {
      cout << "Inf";
      return;
    }
    if (sign < 0) cout << "(-";
    if (this->integer > 0) {
      cout << this->integer;
      flag = true;
    }
    if (this->molecule != 0 || this->integer == 0) {
      if (flag) cout << " ";
      cout << this->molecule;
    }
    if (this->molecule != 0 && this->denominator != 1) cout << "/" << this->denominator;
    if (sign < 0) cout << ")";
  }

  RationalNumber* plus(RationalNumber r) {
    llong m1 = this->sign * (this->molecule + this->integer * this->denominator);
    llong m2 = r.sign * (r.molecule + r.integer * r.denominator);
    llong d1 = this->denominator;
    llong d2 = r.denominator;
    llong d = d1 * d2;
    llong m = m1 * d2 + m2 * d1;
    return new RationalNumber(m, d);
  }

  RationalNumber* minus(RationalNumber r) {
    RationalNumber t = r;
    t.sign = -r.sign;
    return plus(t);
  }

  RationalNumber* multiply(RationalNumber r) {
    llong m1 = this->sign * (this->molecule + this->integer * this->denominator);
    llong m2 = r.sign * (r.molecule + r.integer * r.denominator);
    llong d1 = this->denominator;
    llong d2 = r.denominator;
    llong d = d1 * d2;
    llong m = m1 * m2;
    return new RationalNumber(m, d);
  }

  RationalNumber* divide(RationalNumber r) {
    RationalNumber t = r;
    llong m = r.molecule + r.integer * r.denominator;
    llong d = r.denominator;
    t.integer = 0;
    t.molecule = d;
    t.denominator = m;
    return multiply(t);
  }
};

void operation(RationalNumber r1, RationalNumber r2, char op);

int main() {
  llong m1, m2, d1, d2;
  scanf("%lld/%lld %lld/%lld", &m1, &d1, &m2, &d2);
  RationalNumber r1(m1, d1);
  RationalNumber r2(m2, d2);
  r1.simplify();
  r2.simplify();

  operation(r1, r2, '+');
  operation(r1, r2, '-');
  operation(r1, r2, '*');
  operation(r1, r2, '/');

  return 0;
}

llong gcd(llong a, llong b) {
  if (b == 0) {
    return a;
  }
  else {
    return gcd(b, a % b);
  }
}

void operation(RationalNumber r1, RationalNumber r2, char op) {
  RationalNumber* rp;
  if (op == '+') rp = r1.plus(r2);
  if (op == '-') rp = r1.minus(r2);
  if (op == '*') rp = r1.multiply(r2);
  if (op == '/') rp = r1.divide(r2);
  r1.print();
  cout << " " << op << " ";
  r2.print();
  cout << " = ";
  rp->simplify();
  rp->print();
  cout << endl;
}
