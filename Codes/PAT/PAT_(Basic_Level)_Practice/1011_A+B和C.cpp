#include <iostream>

using namespace std;

int main() {
  long n, a, b, c;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> c;
    cout << "Case #" << i + 1 << ": " << boolalpha << (a+b>c) << endl;
  }
  return 0;
}
