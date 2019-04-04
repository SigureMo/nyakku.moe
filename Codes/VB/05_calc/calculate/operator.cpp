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

Negative::Negative():Operator('-') {
  this->text_ = '-';
  this->precedence = 5;
  this->varNum_ = 1;
}

Number* Negative::compute(Operand* oa1) {
  return new Number(-oa1->nums, oa1->dot);
}

Mod::Mod():Operator('%') {
  this->text_ = '%';
  this->precedence = 2;
  this->varNum_ = 2;
}

Number* Mod::compute(Operand* oa1, Operand* oa2) {
  int nums, maxdot;
  Number *oa;
  if (oa1->dot > oa2->dot) {
    maxdot = oa1->dot;
  }
  else {
    maxdot = oa2->dot;
  }
  nums = (ll)(oa1->nums * pow(10, maxdot-oa1->dot)) % (ll)(oa2->nums * pow(10, maxdot-oa2->dot));
  oa = new Number(nums, maxdot);
  return oa;
}

Log::Log():Operator('l') {
  this->text_ = 'l';
  this->precedence = 5;
  this->varNum_ = 1;
}

Number* Log::compute(Operand* oa1) {
  return new Number(log(oa1->getValue()) / log(10));
}

Ln::Ln():Operator('n') {
  this->text_ = 'n';
  this->precedence = 5;
  this->varNum_ = 1;
}

Number* Ln::compute(Operand* oa1) {
  return new Number(log(oa1->getValue()));
}

Sin::Sin():Operator('s') {
  this->text_ = 's';
  this->precedence = 5;
  this->varNum_ = 1;
}

Number* Sin::compute(Operand* oa1) {
  return new Number(sin(oa1->getValue()));
}

Cos::Cos():Operator('o') {
  this->text_ = 'o';
  this->precedence = 5;
  this->varNum_ = 1;
}

Number* Cos::compute(Operand* oa1) {
  return new Number(cos(oa1->getValue()));
}

Tan::Tan():Operator('t') {
  this->text_ = 't';
  this->precedence = 5;
  this->varNum_ = 1;
}

Number* Tan::compute(Operand* oa1) {
  return new Number(tan(oa1->getValue()));
}

ArcSin::ArcSin():Operator('S') {
  this->text_ = 'S';
  this->precedence = 5;
  this->varNum_ = 1;
}

Number* ArcSin::compute(Operand* oa1) {
  return new Number(asin(oa1->getValue()));
}

ArcCos::ArcCos():Operator('O') {
  this->text_ = 'O';
  this->precedence = 5;
  this->varNum_ = 1;
}

Number* ArcCos::compute(Operand* oa1) {
  return new Number(acos(oa1->getValue()));
}

ArcTan::ArcTan():Operator('T') {
  this->text_ = 'T';
  this->precedence = 5;
  this->varNum_ = 1;
}

Number* ArcTan::compute(Operand* oa1) {
  return new Number(atan(oa1->getValue()));
}
