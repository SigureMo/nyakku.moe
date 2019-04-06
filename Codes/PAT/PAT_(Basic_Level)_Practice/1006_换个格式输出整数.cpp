#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  int b = n / 100;
  int s = (n - b * 100) / 10;
  int g = n % 10;
  for (int i = 0; i < b; i++) {
    cout << "B";
  }
  for (int i = 0; i < s; i++) {
    cout << "S";
  }
  for (int i = 0; i < g; i++) {
    cout << i + 1;
  }
  return 0;
}
