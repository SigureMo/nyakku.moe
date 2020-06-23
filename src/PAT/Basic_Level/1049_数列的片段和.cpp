#include <iostream>

using namespace std;

int main() {
  int N;
  double t, result = 0;
  cin >> N;
  for (int i = 0; i < N; i++) {
    scanf("%lf", &t);
    result += t * (i + 1) * (N - i);
  }
  printf("%.2lf", result);
  return 0;
}
