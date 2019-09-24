#include <iostream>

using namespace std;

int main() {
  bool flag = false;
  int k, p;
  while (cin >> k >> p) {
    if (p == 0) {
      continue;
    }
    if (flag) {
      cout << " ";
    }
    flag = true;
    cout << k * p << " " << p - 1;
  }
  if (!flag) {
    cout << "0 0";
  }
  return 0;
}
