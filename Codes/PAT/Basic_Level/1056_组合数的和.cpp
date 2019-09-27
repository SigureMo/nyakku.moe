#include <iostream>

using namespace std;

int main() {
  int N, t, s=0;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> t;
    s += t * 11;
  }
  cout << s*(N-1) << endl;
  return 0;
}