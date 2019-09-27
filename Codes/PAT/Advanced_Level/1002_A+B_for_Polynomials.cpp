#include <iostream>
#define M 1005
using namespace std;

int main() {
  float a[M] = {0.0};
  float an;
  int K, n, cnt = 0;
  for (int i = 0; i < 2; i++) {
    cin >> K;
    for (int j = 0; j < K; j++) {
      cin >> n >> an;
      a[n] += an;
    }
  }
  for (int i = 0; i < M; i++) {
    if (a[i] != 0.0) cnt++;
  }
  cout << cnt;
  for (int i = M-1; i >= 0; i--) {
    if (a[i] != 0.0) {
      printf(" %d %.1f", i, a[i]);
    }
  }
  cout << endl;
  return 0;
}