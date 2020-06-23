#include <iostream>
#define INF 10005
using namespace std;

int main() {
  int K, a[INF];
  scanf("%d", &K);
  for (int i = 0; i < K; i++) {
    scanf("%d", &a[i]);
  }
  int i = 0, j = 0, sum = 0;
  int i_max, j_max, max = -1;
  int num_neg = 0;
  while (j < K) {
    if (a[j] < 0) num_neg++;
    if (sum < 0) {
      i = j;
      sum = 0;
    }
    sum += a[j];
    if (sum > max) {
      i_max = i;
      j_max = j;
      max = sum;
    }
    j++;
  }
  if (num_neg == K) printf("%d %d %d\n", 0, a[0], a[K-1]);
  else printf("%d %d %d\n", max, a[i_max], a[j_max]);
  return 0;
}
