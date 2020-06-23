#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(int a, int b) {
  return a > b;
}

int main() {
  int N, E = 0;
  scanf("%d", &N);
  int a[N];
  for (int i = 0; i < N; i++) {
    scanf("%d", &a[i]);
  }
  sort(a, a+N, cmp);
  for (int i = 1; i <= N; i++) {
    if (a[i-1] > i) E = i;
  }
  printf("%d\n", E);
  return 0;
}
