#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  string n;
  cin >> n;
  int cnt = 10;
  while (cnt) {
    string reverse_n = n;
    reverse(reverse_n.begin(), reverse_n.end());
    if (n == reverse_n) break;
    int carry = 0;
    string next_n = "";
    for (int i = n.length() - 1; i >= 0; i--) {
      next_n += (n[i] - '0' + reverse_n[i] - '0' + carry) % 10 + '0';
      carry = (n[i] - '0' + reverse_n[i] - '0' + carry) / 10;
    }
    if (carry) next_n += carry + '0';
    reverse(next_n.begin(), next_n.end());
    cout << n << " + " << reverse_n << " = " << next_n << endl;
    n = next_n;
    cnt--;
  }
  if (cnt == 0) cout << "Not found in 10 iterations." << endl;
  else cout << n << " is a palindromic number." << endl;
  return 0;
}
