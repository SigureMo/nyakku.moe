#ifndef CALC_H
#define CALC_H

class ArithmeticUnit {
public:
  ArithmeticUnit(int opType);
  bool isOperator();
  bool isOperand();

private:
  int opType_; // 0 operator 1 operand
};

class Operator : public ArithmeticUnit {
public:
  Operator(char ch);
  bool isLeftBracket();
  bool isRightBracket();
  bool isEqual();
  bool isCE();
  bool isC();
  bool isBackSpace();
  bool isUnaryOperator();
  bool isBinaryOperator();
private:
  int code_; // ascii ...
  int precedence_;
  int varNum_;
};

class Operand : public ArithmeticUnit {
public:
  Operand(int value);
  Operand(char dot);
  Operand();
  bool isDot();
  bool isVariable();
  void cleanZeros(); // clean zeros that behind the dot
protected:
  int value_; // number
  int dot_; // position of dot
  bool variable_;
};

class Variable : public Operand {
public:
  Variable(char name);
  Change(float value);
private:
  char name_;
};

#endif
