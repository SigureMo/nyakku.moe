#include <iostream>
#include <cmath>
#include "arithmetic_unit.hpp"
#include "operand.hpp"
#include "operator.hpp"

using namespace std;

int main(void) {
  Operand oa(0);
  Operator ot(0);
  Plus plus;
  Number num1(1000, 3);
  Number num2(20, 2);
  Number* num3 = plus.compute(num1, num2);
  cout << 1.0*num3->value / pow(10, num3->dot) << endl;
  // cout << oa.isOperand() << endl;
  return 0;
}
