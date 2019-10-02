#include <iostream>

using namespace std;

int main() {
  int total, k;
  scanf("%d %d", &total, &k);
  for (int i = 0; i < k; i++) {
    int n1, b, t, n2;
    scanf("%d %d %d %d", &n1, &b, &t, &n2);
    if (total < t) {
      printf("Not enough tokens.  Total = %d.\n", total);
      continue;
    }
    if ((n1 < n2 && b == 1) || (n1 > n2 && b == 0)) {
      total += t;
      printf("Win %d!  Total = %d.\n", t, total);
    }
    else {
      if (total >= t) {
        total -= t;
        printf("Lose %d.  Total = %d.\n", t, total);
        if (total == 0) {
          printf("Game Over.\n");
          return 0;
        }
      }
    }
  }
  return 0;
}
