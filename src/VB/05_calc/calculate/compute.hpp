#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include "arithmetic_unit.hpp"
#include "operand.hpp"
#include "operator.hpp"

using namespace std;

#ifndef COMPUTE_H
#define COMPUTE_H

extern vector<ArithmeticUnit*> arithmeticUnitVector;
extern stack<Operator*> operatorStack;
extern Number* operandTmp;
extern queue<ArithmeticUnit*> postfixExpressionQueue;
extern stack<Operand*> operandStack;

void checkVars();
void fillArithmeticUnitVector(string expression);
void computePostfixExpressionQueue();
void pushOperand(bool& digitFlag, bool& dotFlag);
double computeValue();

#endif
