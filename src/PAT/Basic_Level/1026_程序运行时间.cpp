#include <iostream>
#define CLK_TCK 100

using namespace std;

int main() {
  int C1, C2, T;
  int h, m, s;
  cin >> C1 >> C2;
  T = 1.0 * (C2 - C1) / CLK_TCK + 0.5;
  s = T % 60;
  m = T / 60;
  h = m / 60;
  m = m % 60;
  printf("%02d:%02d:%02d", h, m, s);
  return 0;
}
