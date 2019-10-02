#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  int a[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  sort(a, a+n);
  int ans = a[0];
  for (int i = 1; i < n; i++) {
    ans += a[i];
    ans /= 2;
  }
  printf("%d\n", (int)ans);
  return 0;
}
