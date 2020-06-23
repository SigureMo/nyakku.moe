#include <cmath>
#include "arithmetic_unit.hpp"
#define PI 3.14159265358979323846
#define DIGHT 0
#define VARIABLE 1
#define NUMBER 2
#define DOT 3
#define CONSTRAINT 4

#ifndef OPERAND_H
#define OPERAND_H

class Operator;

class Operand : public ArithmeticUnit {
public:
  Operand(int oaType);
  friend Operator;
  bool isDot();
  bool isDigit();
  bool isNumber();
  bool isVariable();
  bool isConstant();
  void cleanZeros(); // clean zeros that behind the dot
  double getValue();
  void setValue(double value);
  llong nums; // number
  int dot; // position of dot
protected:
  int oaType_;
  int name_; // char
};

class Digit : public Operand {
public:
  Digit(char name);
};

class Variable : public Operand {
public:
  Variable(char name);
};

class Number : public Operand {
public:
  Number(llong nums, int dot);
  Number(double value);
  void multiply(double value);
};

class Dot : public Operand {
public:
  Dot(char name);
};

class Constant : public Operand {
public:
  Constant(char name);
  double value;
};

class Pi : public Constant {
public:
  Pi();
};

class Exp : public Constant {
public:
  Exp();
};

#endif
