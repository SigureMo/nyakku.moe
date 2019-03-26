#include <iostream>
#include <cmath>
#include "calc.hpp"

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


Operator::Operator(char ch):ArithmeticUnit(0) {
  this->code_ = ch;
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


Operand::Operand(int value):ArithmeticUnit(1) {
  this->dot_ = 0;
  this->value_ = value;
}

Operand::Operand(char dot):ArithmeticUnit(1) {
  this->dot_ = 1;
  this->value_ = 0;
}

Operand::Operand():ArithmeticUnit(1) {
  this->dot_ = 0;
  this->value_ = 0;
}

bool Operand::isDot() {
  return this->dot_;
}

bool Operand::isVariable() {
  return this->variable_;
}

void Operand::cleanZeros() {
  while (this->value_ % 10 == 0) {
    this->value_ /= 10;
    this->dot_ -= 1;
  }
}


Variable::Variable(char name) {
  this->name_ = name;
  this->variable_ = true;
}

Variable::Change(float value) {
  this->value_ = value * pow(10, 6);
  this->dot_ = 6;
  cleanZeros();
}
