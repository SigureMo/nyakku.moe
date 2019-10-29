#include <iostream>

using namespace std;

int main() {
  int a[5] = {0}, cnt[5] = {0};
  int n;
  cin >> n;
  while (n--) {
    int num;
    cin >> num;
    if (num % 5 == 0 && num % 2 == 0) {
      cnt[0]++;
      a[0] += num;
    }
    if (num % 5 == 1) {
      if (cnt[1] % 2 == 0) {
        a[1] += num;
      }
      else {
        a[1] -= num;
      }
      cnt[1]++;
    }
    if (num % 5 == 2) {
      cnt[2]++;
      a[2]++;
    }
    if (num % 5 == 3) {
      cnt[3]++;
      a[3] += num;
    }
    if (num % 5 == 4) {
      if (num > a[4]) {
        cnt[4]++;
        a[4] = num;
      }
    }
  }
  for (int i = 0; i < 5; i++) {
    if (cnt[i]) {
      if (i == 3) printf("%.1f", 1.0 * a[i] / cnt[i]);
      else cout << a[i];
    }
    else {
      cout << "N";
    }
    if (i != 4) cout << " ";
  }
  return 0;
}
