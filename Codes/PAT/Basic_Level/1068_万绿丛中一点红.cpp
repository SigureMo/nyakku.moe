#include <iostream>
#include <map>
#include <cmath>

using namespace std;

int main() {
  int m, n, tol, cnt = 0;
  int x, y, color;
  map<int, int> p;
  scanf("%d %d %d", &m, &n, &tol);
  int a[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
      if (p.find(a[i][j]) != p.end()) p[a[i][j]]++;
      else p[a[i][j]] = 1;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      bool flag = true;
      for (int u = -1; flag && (u < 2); u++) {
        for (int v = -1; flag && (v < 2); v++) {
          if (u == 0 && v == 0) continue;
          if (i+u >= 0 && j+v >= 0 && i+u < n && j+v < m)
            flag = flag && (abs(a[i][j] - a[i+u][j+v]) > tol);
        }
      }
      flag = flag && (p[a[i][j]] == 1);
      if (flag) {
        x = j + 1;
        y = i + 1;
        color = a[i][j];
        cnt++;
      }
    }
  }
  if (cnt == 0) printf("Not Exist\n");
  else if (cnt > 1) printf("Not Unique\n");
  else printf("(%d, %d): %d\n", x, y, color);
  return 0;
}
