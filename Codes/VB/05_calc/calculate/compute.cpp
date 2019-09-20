#include <iostream>
#include "compute.hpp"

using namespace std;

vector<ArithmeticUnit*> arithmeticUnitVector;
stack<Operator*> operatorStack;
Number* operandTmp = new Number(0, 0);
queue<ArithmeticUnit*> postfixExpressionQueue;
stack<Operand*> operandStack;

void checkVars() {
  if (!arithmeticUnitVector.empty()) {
    cout << "arithmeticUnitVector is not empty!" << endl;
  }
  if (!operatorStack.empty()) {
    cout << "operatorStack is not empty!" << endl;
  }
  if (operandTmp->nums) {
    cout << "operandTmp->nums is not zero!" << endl;
  }
  if (operandTmp->dot) {
    cout << "operandTmp->dot is not zero!" << endl;
  }
  if (!postfixExpressionQueue.empty()) {
    cout << "postfixExpressionQueue is not empty!" << endl;
  }
  if (!operandStack.empty()) {
    cout << "operandStack is not empty!" << endl;
  }
}

void fillArithmeticUnitVector(string expression) {
  for (int i = 0; i < expression.size(); i++) {
    char c = expression[i];
    if (c == '\b') { // backspace
      if (!arithmeticUnitVector.empty()) {
        arithmeticUnitVector.pop_back();
      }
    }
    else if (c == 27) { // delete CE
      while (arithmeticUnitVector.back()->isOperand()) {
        arithmeticUnitVector.pop_back();
      }
    }
    else if (c == 127) { // esc C
      arithmeticUnitVector.clear();
    }
    else if (c == '=') {
      computePostfixExpressionQueue();
    }
    else if (c >= 48 && c <= 57) { // digit
      arithmeticUnitVector.push_back(new Digit(c));
    }
    else if (c == 'e') { // constant
      arithmeticUnitVector.push_back(new Exp);
    }
    else if (c == 'p') {
      arithmeticUnitVector.push_back(new Pi);
    }
    else if (c == '.') { // dot
      arithmeticUnitVector.push_back(new Dot('.'));
    }
    else if (c == '+') { // operators
      arithmeticUnitVector.push_back(new Plus);
    }
    else if (c == '-') {
      if (i == 0 || (!(expression[i-1] >= 48 && expression[i-1] <=57) && (expression[i-1] != '!'))) {
        arithmeticUnitVector.push_back(new Negative);
      }
      else {
        arithmeticUnitVector.push_back(new Minus);
      }
    }
    else if (c == '*') {
      arithmeticUnitVector.push_back(new Multiply);
    }
    else if (c == '/') {
      arithmeticUnitVector.push_back(new Divide);
    }
    else if (c == '%') {
      arithmeticUnitVector.push_back(new Mod);
    }
    else if (c == '^') {
      arithmeticUnitVector.push_back(new Power);
    }
    else if (c == '(') {
      arithmeticUnitVector.push_back(new LeftBracket);
    }
    else if (c == ')') {
      arithmeticUnitVector.push_back(new RightBracket);
    }
    else if (c == ' ') {
      ;
    }
    else if (c == 'l') {
      arithmeticUnitVector.push_back(new Log);
    }
    else if (c == 'n') {
      arithmeticUnitVector.push_back(new Ln);
    }
    else if (c == 's') {
      arithmeticUnitVector.push_back(new Sin);
    }
    else if (c == 'o') {
      arithmeticUnitVector.push_back(new Cos);
    }
    else if (c == 't') {
      arithmeticUnitVector.push_back(new Tan);
    }
    else if (c == 'S') {
      arithmeticUnitVector.push_back(new ArcSin);
    }
    else if (c == 'O') {
      arithmeticUnitVector.push_back(new ArcCos);
    }
    else if (c == 'T') {
      arithmeticUnitVector.push_back(new ArcTan);
    }
    else if (c == '!') {
      arithmeticUnitVector.push_back(new Factorial);
    }
    else if (c == '@') {
      arithmeticUnitVector.push_back(new Sqrt);
    }
    else {
      cout << "Operator " << c << " is not defined!" << endl;
    }
  }
}

void computePostfixExpressionQueue() {
  bool digitFlag = false;
  bool dotFlag = false;
  for (int i = 0; i < arithmeticUnitVector.size(); i++) {
    ArithmeticUnit* unit = arithmeticUnitVector[i];

    if (unit->isOperator()) {

      pushOperand(digitFlag, dotFlag);

      Operator* ot = (Operator*) unit;
      if (ot->isLeftBracket()) {
        ot->priority = 0;
        operatorStack.push(ot);
      }
      else if (ot->isRightBracket()) {
        while (!operatorStack.empty()) {
          Operator* otmp = operatorStack.top();
          operatorStack.pop();
          if (otmp->isLeftBracket()) {
            break;
          }
          postfixExpressionQueue.push(otmp);
        }
      }
      else if (operatorStack.empty() || ot->isPrefixUnaryOperator() || ot->priority > operatorStack.top()->priority) {
        operatorStack.push(ot);
      }
      else {
        while (!operatorStack.empty() && ot->priority <= operatorStack.top()->priority) {
          postfixExpressionQueue.push(operatorStack.top());
          operatorStack.pop();
        }
        operatorStack.push(ot);
      }
    }
    else if (unit->isOperand()) {
      Operand* oa = (Operand*) unit;
      if (oa->isDot()) {
        dotFlag = true;
      }
      else if (oa->isDigit()) {
        digitFlag = true;
        if (dotFlag) {
          operandTmp->dot++;
        }
        operandTmp->nums = operandTmp->nums * 10 + oa->nums;
      }
      else if (oa->isConstant()) {
        Constant* ct = (Constant*) oa;
        if (!digitFlag) {
          operandTmp->nums = 1;
        }
        digitFlag = true;
        operandTmp->multiply(ct->value);
        pushOperand(digitFlag, dotFlag);
      }
    }
  }

  // clear operandTmp
  pushOperand(digitFlag, dotFlag);

  // clear operatorStack
  while (!operatorStack.empty()) {
    postfixExpressionQueue.push(operatorStack.top());
    operatorStack.pop();
  }

  // clear arithmeticUnitVector
  arithmeticUnitVector.clear();
}

void pushOperand(bool& digitFlag, bool& dotFlag) {
  /* push operandTmp into postfixExpressionQueue and clear operandTmp */
  if (digitFlag) {
    Number* newOperand = new Number(operandTmp->nums, operandTmp->dot);
    postfixExpressionQueue.push(newOperand);
    operandTmp->dot = 0;
    operandTmp->nums = 0;
  }
  digitFlag = false;
  dotFlag = false;
}

double computeValue() {
  while (!postfixExpressionQueue.empty()) {
    ArithmeticUnit* unit = postfixExpressionQueue.front();
    postfixExpressionQueue.pop();
    if (unit->isOperand()) {
      Number* oa = (Number*) unit;
      operandStack.push(oa);
    }
    else if (unit->isOperator()) {
      Operator* ot = (Operator*) unit;
      Number* res;
      if (ot->isUnaryOperator()) {
        Number* oa1 = (Number*) operandStack.top();
        operandStack.pop();
        res = ot->compute(oa1);
      }
      else if (ot->isBinaryOperator()) {
        Number* oa2 = (Number*) operandStack.top();
        operandStack.pop();
        Number* oa1 = (Number*) operandStack.top();
        operandStack.pop();
        res = ot->compute(oa1, oa2);
      }
      else {
        cout << "varnum > 2!" << endl;
      }

      operandStack.push(res);
    }
  }
  Number* res = (Number*) operandStack.top();
  operandStack.pop();
  return res->getValue();
}
