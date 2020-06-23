#include <iostream>

using namespace std;

int main() {
  string A, B;
  int DA, DB, result_A = 0, result_B = 0;
  cin >> A >> DA >> B >> DB;
  for (int i = 0; i < A.size(); i++) {
    if (A[i] == '0' + DA) {
      result_A = result_A * 10 + DA;
    }
  }
  for (int i = 0; i < B.size(); i++) {
    if (B[i] == '0' + DB) {
      result_B = result_B * 10 + DB;
    }
  }
  cout << result_A + result_B;
  return 0;
}
