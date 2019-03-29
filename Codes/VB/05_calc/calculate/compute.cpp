#include <iostream>
#include "compute.hpp"

using namespace std;

vector<ArithmeticUnit*> arithmeticUnitVector;
stack<Operator*> operatorStack;
Number* operandTmp = new Number(0, 0);
queue<ArithmeticUnit*> postfixExpressionQueue;
stack<ArithmeticUnit*> runtimeStack;

void checkVars() {
  if (!arithmeticUnitVector.empty()) {
    cout << "arithmeticUnitVector is not empty!" << endl;
  }
  if (!operatorStack.empty()) {
    cout << "operatorStack is not empty!" << endl;
  }
  if (!operandTmp->nums) {
    cout << "operandTmp.nums is not zero!" << endl;
  }
  if (!operandTmp->dot) {
    cout << "operandTmp.dot is not zero!" << endl;
  }
  if (!postfixExpressionQueue.empty()) {
    cout << "postfixExpressionQueue is not empty!" << endl;
  }
  if (!runtimeStack.empty()) {
    cout << "runtimeStack is not empty!" << endl;
  }
}

void fillarithmeticUnitVector(string expression) {
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
    else {
      cout << "Operator " << c << " is not defined!" << endl;
    }
  }
}

void computePostfixExpressionQueue() {
  for (int i = 0; i < arithmeticUnitVector.size(); i++) {
    ArithmeticUnit* unit = arithmeticUnitVector[i];

    if (unit->isOperator()) {

      Number* newOperand = new Number(operandTmp->nums, operandTmp->dot-1);
      postfixExpressionQueue.push(newOperand);
      operandTmp->dot = 0;
      operandTmp->nums = 0;

      Operator* ot = (Operator*) &unit;
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
      Operand* oa = (Operand*) &unit;
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
}
