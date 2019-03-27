#include <cmath>
#include <iostream>
#include "operator.hpp"
#include "operand.hpp"

Operator::Operator(int code):ArithmeticUnit(0) {
  this->code_ = code;
}

bool Operator::isLeftBracket() {
  return this->code_ == 40;
}

bool Operator::isRightBracket() {
  return this->code_ == 41;
}

bool Operator::isEqual() {
  return this->code_ == 61;
}

bool Operator::isCE() {
  return this->code_ == 127; // Key 'delete'
}

bool Operator::isC() {
  return this->code_ == 27; // Key 'Esc'
}

bool Operator::isBackSpace() {
  return this->code_ == 8;
}

bool Operator::isUnaryOperator() {
  return this->varNum_ == 1;
}

bool Operator::isBinaryOperator() {
  return this->varNum_ == 2;
}

Plus::Plus():Operator('+') {
  this->text_ = '+';
  this->precedence_ = 1;
  this->varNum_ = 2;
}

void Plus::test() {
  int i = 1;
}

Number* Plus::compute(Operand &oa1, Operand &oa2) {
  int value;
  Operand *inaccuracy, *accuracy;
  Number *oa;
  if (oa1.dot < oa2.dot) {
    accuracy = &oa2;
    inaccuracy = &oa1;
  }
  else {
    accuracy = &oa1;
    inaccuracy = &oa2;
  }
  value = accuracy->value + inaccuracy->value*pow(10, accuracy->dot-inaccuracy->dot);
  oa = new Number(value, accuracy->dot);
  return oa;
}
