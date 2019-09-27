#include <cmath>
#include <iostream>
#include "operator.hpp"
#include "operand.hpp"

using namespace std;

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
  return this->eleNumber == 1 or this->eleNumber == -1;
}

bool Operator::isBinaryOperator() {
  return this->eleNumber == 2;
}

bool Operator::isPrefixUnaryOperator() {
  return this->eleNumber == 1;
}

bool Operator::isPostfixUnaryOperator() {
  return this->eleNumber == -1;
}

Number* Operator::compute(Operand* oa1, Operand* oa2) {return new Number(0);};
Number* Operator::compute(Operand* oa1) {return new Number(0);};


Plus::Plus():Operator('+') {
  this->text_ = '+';
  this->priority = 1;
  this->eleNumber = 2;
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
  this->priority = 1;
  this->eleNumber = 2;
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
  this->priority = 2;
  this->eleNumber = 2;
}

Number* Multiply::compute(Operand* oa1, Operand* oa2) {
  return new Number(oa1->nums * oa2->nums, oa1->dot + oa2->dot);
}

Divide::Divide():Operator('/') {
  this->text_ = '/';
  this->priority = 2;
  this->eleNumber = 2;
}

Number* Divide::compute(Operand* oa1, Operand* oa2) {
  return new Number(oa1->getValue() / oa2->getValue());
}

Power::Power():Operator('^') {
  this->text_ = '^';
  this->priority = 3;
  this->eleNumber = 2;
}

Number* Power::compute(Operand* oa1, Operand* oa2) {
  return new Number(pow(oa1->getValue(), oa2->getValue()));
}

LeftBracket::LeftBracket():Operator('(') {
  this->text_ = '(';
  this->priority = 99;
}

RightBracket::RightBracket():Operator(')') {
  this->text_ = ')';
  this->priority = 0;
}

Negative::Negative():Operator('-') {
  this->text_ = '-';
  this->priority = 9;
  this->eleNumber = 1;
}

Number* Negative::compute(Operand* oa1) {
  return new Number(-oa1->nums, oa1->dot);
}

Mod::Mod():Operator('%') {
  this->text_ = '%';
  this->priority = 2;
  this->eleNumber = 2;
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
  nums = (llong)(oa1->nums * pow(10, maxdot-oa1->dot)) % (llong)(oa2->nums * pow(10, maxdot-oa2->dot));
  oa = new Number(nums, maxdot);
  return oa;
}

Log::Log():Operator('l') {
  this->text_ = 'l';
  this->priority = 9;
  this->eleNumber = 1;
}

Number* Log::compute(Operand* oa1) {
  return new Number(log(oa1->getValue()) / log(10));
}

Ln::Ln():Operator('n') {
  this->text_ = 'n';
  this->priority = 9;
  this->eleNumber = 1;
}

Number* Ln::compute(Operand* oa1) {
  return new Number(log(oa1->getValue()));
}

Sin::Sin():Operator('s') {
  this->text_ = 's';
  this->priority = 9;
  this->eleNumber = 1;
}

Number* Sin::compute(Operand* oa1) {
  return new Number(sin(oa1->getValue()));
}

Cos::Cos():Operator('o') {
  this->text_ = 'o';
  this->priority = 9;
  this->eleNumber = 1;
}

Number* Cos::compute(Operand* oa1) {
  return new Number(cos(oa1->getValue()));
}

Tan::Tan():Operator('t') {
  this->text_ = 't';
  this->priority = 9;
  this->eleNumber = 1;
}

Number* Tan::compute(Operand* oa1) {
  return new Number(tan(oa1->getValue()));
}

ArcSin::ArcSin():Operator('S') {
  this->text_ = 'S';
  this->priority = 9;
  this->eleNumber = 1;
}

Number* ArcSin::compute(Operand* oa1) {
  return new Number(asin(oa1->getValue()));
}

ArcCos::ArcCos():Operator('O') {
  this->text_ = 'O';
  this->priority = 9;
  this->eleNumber = 1;
}

Number* ArcCos::compute(Operand* oa1) {
  return new Number(acos(oa1->getValue()));
}

ArcTan::ArcTan():Operator('T') {
  this->text_ = 'T';
  this->priority = 9;
  this->eleNumber = 1;
}

Number* ArcTan::compute(Operand* oa1) {
  return new Number(atan(oa1->getValue()));
}

Factorial::Factorial():Operator('!') {
  this->text_ = '!';
  this->priority = 9;
  this->eleNumber = -1;
}

Number* Factorial::compute(Operand* oa1) {
  double res = 1;
  double num;
  for (num = oa1->getValue(); num > 1; num--) {
    res *= num;
  }
  if (num == 0) {
    res = 1;
  }
  else if (num < 1) {
    res *= Gamma(num + 1);
  }
  return new Number(res);
}

Sqrt::Sqrt():Operator('@') {
  this->text_ = '@';
  this->priority = 9;
  this->eleNumber = 1;
}

Number* Sqrt::compute(Operand* oa1) {
  return new Number(sqrt(oa1->getValue()));
}

double Gamma(double x) {
  // $\Gamma(x) = \int_0^{+\infty}t^{x-1}e^{-t}dt$
  int i = 0;
  double delta = 1e-6;
  double res = 0;
  while (i < 1e7) {
    res += pow(i * delta, x - 1) * exp(-i * delta) * delta;
    i++;
  }
  return res;
}
