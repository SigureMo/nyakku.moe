#include "operand.hpp"

Operand::Operand(int oaType):ArithmeticUnit(1) {
  this->oaType_ = oaType;
  this->dot = 0;
  this->nums = 0;
}

bool Operand::isDigit() {
  return this->oaType_ == DIGHT;
}

bool Operand::isVariable() {
  return this->oaType_ == VARIABLE;
}

bool Operand::isDot() {
  return this->oaType_ == DOT;
}

bool Operand::isNumber() {
  return this->oaType_ == NUMBER;
}

bool Operand::isConstant() {
  return this->oaType_ == CONSTRAINT;
}

void Operand::cleanZeros() {
  while (this->nums % 10 == 0 && this->nums!=0 && this->dot > 0) {
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


Digit::Digit(char name):Operand(DIGHT) {
  this->name_ = name;
  this->nums = name - 48;
}


Variable::Variable(char name):Operand(VARIABLE) {
  this->name_ = name;
}


Number::Number(llong nums, int dot):Operand(DOT) {
  this->name_ = 0;
  this->nums = nums;
  this->dot = dot;
  cleanZeros();
}

Number::Number(double value):Operand(NUMBER) {
  this->name_ = 0;
  this->setValue(value);
}

void Number::multiply(double value) {
  double newValue = this->getValue() * value;
  this->setValue(newValue);
}


Dot::Dot(char name):Operand(DOT) {
  this->name_ = name;
}


Constant::Constant(char name):Operand(CONSTRAINT) {
  this->name_ = name;
}


Pi::Pi():Constant('p') {
  this->value = PI;
}


Exp::Exp():Constant('e') {
  this->value = exp(1);
}
