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

Number* Operator::compute(Operand* oa1, Operand* oa2) {};
Number* Operator::compute(Operand* oa1) {};


Plus::Plus():Operator('+') {
  this->text_ = '+';
  this->precedence = 1;
  this->varNum_ = 2;
}

Number* Plus::compute(Operand* oa1, Operand* oa2) {
  int nums;
  Operand *inaccuracy, *accuracy;
  Number *oa;
  if (oa1->dot < oa2->dot) {
    accuracy = oa2;
    inaccuracy = oa1;
  }
  else {
    accuracy = oa1;
    inaccuracy = oa2;
  }
  nums = accuracy->nums + inaccuracy->nums*pow(10, accuracy->dot-inaccuracy->dot);
  oa = new Number(nums, accuracy->dot);
  return oa;
}

Minus::Minus():Operator('-') {
  this->text_ = '-';
  this->precedence = 1;
  this->varNum_ = 2;
}

Number* Minus::compute(Operand* oa1, Operand* oa2) {
  Plus plus;
  Number *oa3, *res;
  oa3 = new Number(-(oa2->nums), oa2->dot);
  res = plus.compute(oa1, oa3);
  // delete &plus;
  return res;
}

Multiply::Multiply():Operator('*') {
  this->text_ = '*';
  this->precedence = 2;
  this->varNum_ = 2;
}

Number* Multiply::compute(Operand* oa1, Operand* oa2) {
  return new Number(oa1->nums * oa2->nums, oa1->dot + oa2->dot);
}

Divide::Divide():Operator('/') {
  this->text_ = '/';
  this->precedence = 2;
  this->varNum_ = 2;
}

Number* Divide::compute(Operand* oa1, Operand* oa2) {
  return new Number(oa1->getValue() / oa2->getValue());
}

Power::Power():Operator('^') {
  this->text_ = '^';
  this->precedence = 3;
  this->varNum_ = 2;
}

Number* Power::compute(Operand* oa1, Operand* oa2) {
  return new Number(pow(oa1->getValue(), oa2->getValue()));
}

LeftBracket::LeftBracket():Operator('(') {
  this->text_ = '(';
  this->precedence = 99;
}

RightBracket::RightBracket():Operator(')') {
  this->text_ = ')';
  this->precedence = 0;
}
