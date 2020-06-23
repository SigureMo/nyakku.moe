#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int num);

int main() {
  int cnt = 0, M, N;
  cin >> M >> N;
  for (int i = 2; cnt < N; i++) {
    if (isPrime(i)) {
      cnt++;
      if (cnt >= M) {
        if ((cnt - M) % 10 != 0) cout << " ";
        cout << i;
        if ((cnt - M) % 10 == 9) cout << endl;
      }
    }
  }
  return 0;
}

bool isPrime(int num) {
  for (int i = 2; i <= sqrt(num); i++) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}
