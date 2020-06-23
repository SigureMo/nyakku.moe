#include <iostream>
#define MaxSize 50
typedef int ElemType;

class Stack {
public:
  Stack() {
    top = -1;
  }
  bool isEmpty() {
    return (top == -1);
  }
  ElemType peek() {
    return data[top];
  }
  ElemType push(ElemType value) {
    return data[++top] = value;
  }
  ElemType pop() {
    return data[top--];
  }
  int getSize() {
    return top+1;
  }
private:
  int data[MaxSize];
  int top;
};

int main() {
  Stack stack;
  for (int i = 0; i < 10; i++) {
    stack.push(i);
  }
  while (!stack.isEmpty()) {
    std::cout << stack.pop() << std::endl;
  }
  return 0;
}
