#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int num);

int main() {
  int N, lastPrime = 2, cnt = 0;
  cin >> N;
  for (int i = 2; i <= N; i++) {
    if (isPrime(i)) {
      if (i - lastPrime == 2) cnt++;
      lastPrime = i;
    }
  }
  cout << cnt;
}

bool isPrime(int num) {
  for (int i = 2; i <= sqrt(num); i++) {
    if (num % i == 0) return false;
  }
  return true;
}
