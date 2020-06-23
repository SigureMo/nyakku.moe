#include <iostream>
#include <string>

using namespace std;

bool isPrime(int num) {
  if (num == 0 || num == 1) return false;
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0) return false;
  }
  return true;
}

int main() {
  int L, K;
  string N;
  bool flag = false;
  cin >> L >> K >> N;
  for (int i = 0; i < L-K+1; i++) {
    string s = N.substr(i, K);
    int n = stoi(s);
    if (isPrime(n)) {
      cout << s << endl;
      flag = true;
      break;
    }
  }
  if (!flag) cout << 404 << endl;
  return 0;
}
