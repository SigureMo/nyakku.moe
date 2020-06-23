#include <iostream>

using namespace std;

int gcd(int a, int b) {
  return b == 0? a : gcd(b, a%b);
}

int main() {
  int n1, m1, n2, m2, k;
  bool first = true;
  scanf("%d/%d %d/%d %d", &n1, &m1, &n2, &m2, &k);
  if (n1 * m2 > n2 * m1) {
    swap(n1, n2);
    swap(m1, m2);
  }
  int idx = 1;
  while (n1 * k >= idx * m1) idx++;
  while (n1 * k < idx * m1 && m2 * idx < n2 * k) {
    if (gcd(idx, k) == 1)
    {
      if (first)
        first = false;
      else
        printf(" ");
      printf("%d/%d", idx, k);
    }
    idx++;
  }
  return 0;
}
