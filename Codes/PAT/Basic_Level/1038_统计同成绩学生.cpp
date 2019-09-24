#include <iostream>

using namespace std;

int main() {
  int a[101] = {0};
  int N, K, tmp;
  bool first = true;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> tmp;
    a[tmp]++;
  }
  cin >> K;
  for (int i = 0; i < K; i++) {
    cin >> tmp;
    if (!first) cout << " ";
    first = false;
    cout << a[tmp];
  }
}
