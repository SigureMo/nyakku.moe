#include <iostream>
using namespace std;

int main() {
  int N, p = 0, q, t = 0;
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &q);
    if (q > p) t += (q - p) * 6;
    else t += (p - q) * 4;
    t += 5;
    p = q;
  }
  printf("%d\n", t);
  return 0;
}
