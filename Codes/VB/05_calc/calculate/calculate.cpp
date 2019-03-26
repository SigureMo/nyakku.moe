#include <iostream>
#include "calc.hpp"

using namespace std;

int main(void) {
  Operand oa(0);
  cout << oa.isOperand() << endl;
  return 0;
}
