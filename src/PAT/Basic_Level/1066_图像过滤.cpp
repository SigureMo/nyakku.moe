#include <iostream>

using namespace std;

int main() {
  int m, n, min, max, val;
  scanf("%d %d %d %d %d", &m, &n, &min, &max, &val);
  for (int i = 0; i < m; i++) {
    bool first = true;
    for (int j = 0; j < n; j++) {
      int a;
      scanf("%d", &a);
      a = a >= min && a <= max ? val : a;
      if (first) first = false;
      else printf(" ");
      printf("%03d", a);
    }
    printf("\n");
  }
  return 0;
}
