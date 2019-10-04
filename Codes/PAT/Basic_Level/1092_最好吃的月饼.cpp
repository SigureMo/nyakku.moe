#include <iostream>
#include <cstring>

using namespace std;

int main() {
  int n, m, max = 0;
  cin >> n >> m;
  bool flag[n], first = true;
  int a[n];
  memset(a, 0, sizeof(a));
  memset(flag, false, sizeof(flag));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int t;
      cin >> t;
      a[j] += t;
      if (a[j] >= max) {
        if (a[j] > max) memset(flag, false, sizeof(flag));
        max = a[j];
        flag[j] = true;
      }
    }
  }
  cout << max << endl;
  for (int i = 0; i < n; i++) {
    if (flag[i]) {
      if (!first) cout << " ";
      first = false;
      cout << i + 1;
    }
  }
  return 0;
}
