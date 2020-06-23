#ifndef ARITHMETICUNIT_H
#define ARITHMETICUNIT_H

typedef long long llong;

class ArithmeticUnit {
public:
  ArithmeticUnit(int opType);
  bool isOperator();
  bool isOperand();

private:
  int opType_; // 0 operator 1 operand
};

#endif
