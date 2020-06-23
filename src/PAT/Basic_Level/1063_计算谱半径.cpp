#include <iostream>
#include <cmath>

using namespace std;

int main() {
  int n, max = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int a, b, c;
    scanf("%d %d", &a, &b);
    c = a * a + b * b;
    if (c > max) max = c;
  }
  printf("%.2f", sqrt(max));
  return 0;
}
