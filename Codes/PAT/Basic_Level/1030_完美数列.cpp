#include <iostream>
#include <algorithm>
#define INF 100005

using namespace std;

int main() {
  int N;
  long long p, max = 0;
  int a[INF];
  cin >> N >> p;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }
  sort(a, a + N);
  for (int i = 0; i < N && N-i > max; i++) {
    for (int j = i + max; j < N; j++) {
      if (a[i] * p >= a[j]) {
        max = j-i+1;
      }
      else break;
    }
  }
  cout << max;
  return 0;
}
