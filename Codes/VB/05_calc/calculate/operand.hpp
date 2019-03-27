#include <cmath>
#include "arithmetic_unit.hpp"

#ifndef OPERAND_H
#define OPERAND_H

class Operator;

class Operand : public ArithmeticUnit {
public:
  Operand(int oaType);
  friend Operator;
  bool isDot();
  bool isConstant();
  bool isNumber();
  bool isVariable();
  void cleanZeros(); // clean zeros that behind the dot
  int value; // number
  int dot; // position of dot
protected:
  int oaType_;
  int name_; // char
};

class Constant : public Operand {
public:
  Constant(char name);
};

class Variable : public Operand {
public:
  Variable(char name);
  Change(float value);
};

class Number : public Operand {
public:
  Number(int value, int dot);
};

class Dot : public Operand {
public:
  Dot(char name);
};

#endif
