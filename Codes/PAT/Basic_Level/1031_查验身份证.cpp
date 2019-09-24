#include <iostream>
#define L 18
using namespace std;

int main() {
  int N;
  bool allPassed = true;
  int Ws[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
  string Ms = "10X98765432";
  string s;
  cin >> N;
  for (int i = 0; i < N; i++) {
    bool valid = true;
    int Z = 0;
    char c;
    cin >> s;
    c = s[L - 1];
    for (int j = 0; j < L - 1; j++) {
      if (s[j] < '0' || s[j] > '9') {
        valid = false;
        break;
      }
      Z += Ws[j] * (s[j] - '0');
    }
    Z %= 11;
    if (Ms[Z] != c) valid = false;
    if (!valid) {
      allPassed = false;
      cout << s << endl;
    }
  }
  if (allPassed) {
    cout << "All passed" << endl;
  }
  return 0;
}
