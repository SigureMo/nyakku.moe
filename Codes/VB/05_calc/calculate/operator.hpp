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
  virtual Number* compute(Operand* oa1, Operand* oa2);
  virtual Number* compute(Operand* oa1);
  int precedence;
protected:
  int code_; // ascii ...
  std::string text_;
  int varNum_;
};

class Plus : public Operator {
public:
  Plus();
  Number* compute(Operand* oa1, Operand* oa2);
};

class Minus : public Operator {
public:
  Minus();
  Number* compute(Operand* oa1, Operand* oa2);
};

class Multiply : public Operator {
public:
  Multiply();
  Number* compute(Operand* oa1, Operand* oa2);
};

class Divide : public Operator {
public:
  Divide();
  Number* compute(Operand* oa1, Operand* oa2);
};

class Power : public Operator {
public:
  Power();
  Number* compute(Operand* oa1, Operand* oa2);
};

class LeftBracket : public Operator {
public:
  LeftBracket();
};

class RightBracket : public Operator {
public:
  RightBracket();
};

#endif
