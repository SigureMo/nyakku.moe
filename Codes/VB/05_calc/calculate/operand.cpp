#include "operand.hpp"

Operand::Operand(int oaType):ArithmeticUnit(1) {
  this->oaType_ = oaType;
  this->dot = 0;
  this->nums = 0;
}

bool Operand::isConstant() {
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

void Operand::cleanZeros() {
  while (this->nums % 10 == 0 && this->nums!=0) {
    this->nums /= 10;
    this->dot -= 1;
  }
}

float Operand::getValue() {
  return this->nums / pow(10, this->dot);
}


Constant::Constant(char name):Operand(0) {
  this->name_ = name;
  this->nums = name - 48;
}


Variable::Variable(char name):Operand(1) {
  this->name_ = name;
}

Variable::Change(float value) {
  this->nums = value * pow(10, 6);
  this->dot = 6;
  cleanZeros();
}


Number::Number(int nums, int dot):Operand(2) {
  this->name_ = 0;
  this->nums = nums;
  this->dot = dot;
  cleanZeros();
}

Number::Number(float value):Operand(2) {
  this->name_ = 0;
  this->nums = value * pow(10, 6);
  this->dot = 6;
  cleanZeros();
}


Dot::Dot(char name):Operand(3) {
  this->name_ = name;
}
