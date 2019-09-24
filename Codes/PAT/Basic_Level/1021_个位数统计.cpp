#include <iostream>

using namespace std;

int main() {
  string N;
  int a[10] = {0};
  cin >> N;
  for (int i = 0; i < N.size(); i++) {
    a[N[i] - '0']++;
  }
  for (int i = 0; i < 10; i++) {
    if (a[i]) {
      cout << i << ":" << a[i] << endl;
    }
  }
  return 0;
}
