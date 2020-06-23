#include <iostream>
#include <algorithm>
#define EMPTY 10001

using namespace std;

int main() {
  int N, m, n;
  int dir[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  cin >> N;
  for (int i = 1; i * i <= N; i++) {
    if (N % i == 0) {
      n = i;
      m = N / i;
    }
  }
  int a[m][n], b[N];
  for (int i = 0; i < N; i++) {
    cin >> b[i];
  }
  auto cmp = [](int a, int b) -> bool {
    return a > b;
  };
  sort(b, b+N, cmp);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = EMPTY;
    }
  }
  int pi = 0, pj = 0, status = 0;
  for (int i = 0; i < N; i++) {
    a[pi][pj] = b[i];
    int pin = pi + dir[status][0];
    int pjn = pj + dir[status][1];
    if (pin < 0 || pjn < 0 || pin >= m || pjn >= n || a[pin][pjn] != EMPTY) {
      status += 1;
      status %= 4;
      pin = pi + dir[status][0];
      pjn = pj + dir[status][1];
    }
    pi = pin;
    pj = pjn;

  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (j != 0) cout << " ";
      cout << a[i][j];
      if (j == n-1) cout << endl;
    }
  }
  return 0;
}
