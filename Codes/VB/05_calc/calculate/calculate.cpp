#include <iostream>
#include <cmath>
#include "arithmetic_unit.hpp"
#include "operand.hpp"
#include "operator.hpp"
#include "compute.hpp"

using namespace std;

int main(void) {
  // test1
  Plus plus;
  Number num1(1000, 3);
  Number num2(20, 2);
  Number* num3 = plus.compute(&num1, &num2);
  cout << num3->getValue() << endl;

  // test2
  // Support +-*/^()
  checkVars();
  fillArithmeticUnitVector("(1-17.5)*3-3^2=");
  cout << computeValue() << endl;
  checkVars();

  // TODO
  // 1. 垃圾回收问题
  // 2. 负号的问题
  // 3. 变量的支持
  return 0;
}
