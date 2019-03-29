#include <iostream>
#include "arithmetic_unit.hpp"
#include "operand.hpp"

#ifndef OPERATOR_H
#define OPERATOR_H

class Operand;

class Operator : public ArithmeticUnit {
public:
  Operator(int code);
  bool isLeftBracket();
  bool isRightBracket();
  bool isEqual();
  bool isCE();
  bool isC();
  bool isBackSpace();
  bool isUnaryOperator();
  bool isBinaryOperator();
  virtual Number* compute(Operand &oa1, Operand &oa2)=0;
  int precedence;
protected:
  int code_; // ascii ...
  std::string text_;
  int varNum_;
};

class Plus : public Operator {
public:
  Plus();
  void test();
  Number* compute(Operand &oa1, Operand &oa2);
};

#endif
