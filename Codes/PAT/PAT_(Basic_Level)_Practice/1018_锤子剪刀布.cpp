#include <iostream>

using namespace std;

int A_win = 0, A_lose = 0;
int A[3] = {0}, B[3] = {0};
string gesture = "BCJ";

char get_max(int C[]);

int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    char A_tmp, B_tmp;
    int status;
    cin >> A_tmp >> B_tmp;
    status = (gesture.find(A_tmp) - gesture.find(B_tmp) + 3) % 3;

    if (status == 1) {
      A_lose++;
      B[gesture.find(B_tmp)]++;
    }
    else if (status == 2) {
      A_win++;
      A[gesture.find(A_tmp)]++;
    }
  }
  cout << A_win << " " << N - A_win - A_lose << " " << A_lose << endl;
  cout << A_lose << " " << N - A_win - A_lose << " " << A_win << endl;
  cout << get_max(A) << " " << get_max(B);
  return 0;
}

char get_max(int C[]) {
  int max, max_idx;
  for (int i = 0; i < 3; i++) {
    if (C[i] > max) {
      max = C[i];
      max_idx = i;
    }
  }
  return gesture[max_idx];
}
