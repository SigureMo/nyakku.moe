#include "operand.hpp"

Operand::Operand(int oaType):ArithmeticUnit(1) {
  this->oaType_ = oaType;
  this->dot = 0;
  this->nums = 0;
}

bool Operand::isDigit() {
  return this->oaType_ == 0;
}

bool Operand::isVariable() {
  return this->oaType_ == 1;
}

bool Operand::isDot() {
  return this->oaType_ == 3;
}

bool Operand::isNumber() {
  return this->oaType_ == 2;
}

bool Operand::isConstant() {
  return this->oaType_ == 4;
}

void Operand::cleanZeros() {
  while (this->nums % 10 == 0 && this->nums!=0) {
    this->nums /= 10;
    this->dot -= 1;
  }
}

double Operand::getValue() {
  return this->nums / pow(10, this->dot);
}

void Operand::setValue(double value) {
  this->nums = value * pow(10, 6);
  this->dot = 6;
  cleanZeros();
}


Digit::Digit(char name):Operand(0) {
  this->name_ = name;
  this->nums = name - 48;
}


Variable::Variable(char name):Operand(1) {
  this->name_ = name;
}


Number::Number(ll nums, int dot):Operand(2) {
  this->name_ = 0;
  this->nums = nums;
  this->dot = dot;
  cleanZeros();
}

Number::Number(double value):Operand(2) {
  this->name_ = 0;
  this->setValue(value);
}

void Number::multiply(double value) {
  double newValue = this->getValue() * value;
  this->setValue(newValue);
}


Dot::Dot(char name):Operand(3) {
  this->name_ = name;
}


Constant::Constant(char name):Operand(4) {
  this->name_ = name;
}


PI::PI():Constant('p') {
  this->value = M_PI;
}


Exp::Exp():Constant('e') {
  this->value = exp(1);
}
