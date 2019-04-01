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
    else if (c >= 48 && c <= 57) {
      arithmeticUnitVector.push_back(new Constant(c));
    }
    else if (c == '.') {
      arithmeticUnitVector.push_back(new Dot('.'));
    }
    else if (c == '+') {
      arithmeticUnitVector.push_back(new Plus);
    }
    else if (c == '-') {
      if (i == 0 || !(expression[i-1] >= 48 && expression[i-1] <=57)) {
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
      cout << 1;
    }
    else {
      cout << "Operator " << c << " is not defined!" << endl;
    }
  }
}

void computePostfixExpressionQueue() {
  bool operandFlag = false;
  for (int i = 0; i < arithmeticUnitVector.size(); i++) {
    ArithmeticUnit* unit = arithmeticUnitVector[i];

    if (unit->isOperator()) {

      if (operandFlag) {
        pushOperand();
      }
      operandFlag = false;

      Operator* ot = (Operator*) unit;
      if (ot->isLeftBracket()) {
        ot->precedence = 0;
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
      else if (operatorStack.empty() || ot->precedence > operatorStack.top()->precedence) {
        operatorStack.push(ot);
      }
      else {
        while (!operatorStack.empty() && ot->precedence <= operatorStack.top()->precedence) {
          postfixExpressionQueue.push(operatorStack.top());
          operatorStack.pop();
        }
        operatorStack.push(ot);
      }
    }
    else if (unit->isOperand()) {
      operandFlag = true;
      Operand* oa = (Operand*) unit;
      if (oa->isDot()) {
        operandTmp->dot = 1;
      }
      else if (oa->isConstant()) {
        if (operandTmp->dot) {
          operandTmp->dot++;
        }
        operandTmp->nums = operandTmp->nums * 10 + oa->nums;
      }
    }
  }

  // clear operandTmp
  if (operandFlag) {
    pushOperand();
  }
  operandFlag = false;

  // clear operatorStack
  while (!operatorStack.empty()) {
    postfixExpressionQueue.push(operatorStack.top());
    operatorStack.pop();
  }

  // clear arithmeticUnitVector
  arithmeticUnitVector.clear();
}

void pushOperand() {
  if (operandTmp->dot) {
    operandTmp->dot -= 1;
  }
  Number* newOperand = new Number(operandTmp->nums, operandTmp->dot);
  postfixExpressionQueue.push(newOperand);
  operandTmp->dot = 0;
  operandTmp->nums = 0;
}

float computeValue() {
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
