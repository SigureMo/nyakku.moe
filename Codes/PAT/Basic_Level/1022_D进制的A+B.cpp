#include <iostream>

using namespace std;

int main() {
  int A, B, C, D;
  string out;
  cin >> A >> B >> D;
  C = A + B;
  if (C == 0) cout << 0;
  else {
    while (C > 0) {
      out += C % D + '0';
      C /= D;
    }
    for (int i = out.size()-1; i >= 0; i--) {
      cout << out[i];
    }
  }
  return 0;
}
