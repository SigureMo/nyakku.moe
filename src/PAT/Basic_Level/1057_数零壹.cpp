#include <iostream>

using namespace std;

int main() {
  string s;
  int n = 0, cnt_0 = 0, cnt_1 = 0;
  getline(cin, s);
  for (int i = 0; i < s.length(); i++) {
    char c = s[i];
    if (c >= 'a' && c <= 'z') n += c - 'a' + 1;
    else if (c >= 'A' && c <= 'Z') n += c - 'A' + 1;
  }
  while (n != 0) {
    if (n % 2 == 0) cnt_0++;
    else if (n % 2 == 1) cnt_1++;
    n /= 2;
  }
  cout << cnt_0 << " " << cnt_1 << endl;
  return 0;
}