#include <iostream>
#include <math.h>

using namespace std;

int main() {
  int N, cnt;
  char c;
  cin >> N >> c;
  cnt = sqrt((N + 1) / 2);
  for (int i = 0; i < cnt; i++) {
    for (int j = 0; j < i; j++) {
      cout << " ";
    }
    for (int j = 0; j < 2 * (cnt - i) - 1; j++) {
      cout << c;
    }
    cout << endl;
  }
  for (int i = 1; i < cnt; i++) {
    for (int j = 0; j < cnt - i - 1; j++) {
      cout << " ";
    }
    for (int j = 0; j < 2 * i + 1; j++) {
      cout << c;
    }
    cout << endl;
  }
  cout << N - 2 * pow(cnt, 2) + 1;
  return 0;
}
