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
  bool isPrefixUnaryOperator();
  bool isPostfixUnaryOperator();
  virtual Number* compute(Operand* oa1, Operand* oa2);
  virtual Number* compute(Operand* oa1);
  int priority;
protected:
  int code_; // ascii ...
  std::string text_;
  int eleNumber;
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

class Negative : public Operator {
public:
  Negative();
  Number* compute(Operand* oa1);
};

class Mod : public Operator {
public:
  Mod();
  Number* compute(Operand* oa1, Operand* oa2);
};

class Log : public Operator {
public:
  Log();
  Number* compute(Operand* oa1);
};

class Ln : public Operator {
public:
  Ln();
  Number* compute(Operand* oa1);
};

class Sin : public Operator {
public:
  Sin();
  Number* compute(Operand* oa1);
};

class Cos : public Operator {
public:
  Cos();
  Number* compute(Operand* oa1);
};

class Tan : public Operator {
public:
  Tan();
  Number* compute(Operand* oa1);
};

class ArcSin : public Operator {
public:
  ArcSin();
  Number* compute(Operand* oa1);
};

class ArcCos : public Operator {
public:
  ArcCos();
  Number* compute(Operand* oa1);
};

class ArcTan : public Operator {
public:
  ArcTan();
  Number* compute(Operand* oa1);
};

class Factorial : public Operator {
public:
  Factorial();
  Number* compute(Operand* oa1);
};

class Sqrt : public Operator {
public:
  Sqrt();
  Number* compute(Operand* oa1);
};

double Gamma(double x);

#endif
