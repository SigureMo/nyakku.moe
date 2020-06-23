#include <iostream>
#define MAX 1005
using namespace std;

int main() {
  int n, cnt = 0;
  scanf("%d", &n);
  float arr[MAX] = {0.0}, ans[2*MAX] = {0.0};
  for (int i = 0; i < n; i++) {
    int idx;
    scanf("%d", &idx);
    scanf("%f", &arr[idx]);
  }
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int idx;
    float t;
    scanf("%d", &idx);
    scanf("%f", &t);
    for (int j = 0; j < MAX; j++) {
      ans[idx + j] += t * arr[j];
    }
  }
  for (int i = 0; i < 2*MAX; i++) {
    if (ans[i] != 0.0) cnt++;
  }
  printf("%d", cnt);
  for (int i = 2*MAX - 1 ; i >= 0; i--) {
    if (ans[i] != 0.0) printf(" %d %.1f", i, ans[i]);
  }
}
