#include <iostream>
#include "arithmetic_unit.hpp"

using namespace std;

ArithmeticUnit::ArithmeticUnit(int opType) {
  this->opType_ = opType;
}

bool ArithmeticUnit::isOperator() {
  return opType_ == 0;
}

bool ArithmeticUnit::isOperand() {
  return opType_ == 1;
}
