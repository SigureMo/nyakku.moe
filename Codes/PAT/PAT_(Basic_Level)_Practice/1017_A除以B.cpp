#include <iostream>

using namespace std;

int main() {
  string A;
  int B, tmp = 0;
  bool flag = false;
  cin >> A >> B;
  for (int i = 0; i < A.size(); i++) {
    tmp = tmp * 10 + A[i] - '0';
    if (tmp >= B) {
      flag = true;
      cout << tmp / B;
      tmp %= B;
    }
    else {
      if (flag) {
        cout << 0;
      }
    }
  }
  if (!flag) cout << 0;
  cout << " " << tmp;
  return 0;
}
