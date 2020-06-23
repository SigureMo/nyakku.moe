#include <iostream>

using namespace std;

int main() {
  int N;
  int A1, A2, B1, B2;
  int A_cnt = 0, B_cnt = 0;
  bool A_win, B_win;
  cin >> N;
  while (N--) {
    cin >> A1 >> A2 >> B1 >> B2;
    A_win = A1 + B1 == A2;
    B_win = A1 + B1 == B2;
    if (A_win && !B_win) B_cnt++;
    if (B_win && !A_win) A_cnt++;
  }
  cout << A_cnt << " " << B_cnt << endl;
  return 0;
}
