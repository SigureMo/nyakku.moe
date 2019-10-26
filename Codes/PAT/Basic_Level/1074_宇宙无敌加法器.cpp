#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  string s[3];
  cin >> s[0] >> s[1] >> s[2];
  for (auto &i : s) {
    reverse(i.begin(), i.end());
  }
  int length = s[0].size();
  for (auto &i : s) {
    while (i.size() < length) {
      i += "0";
    }
  }
  string result = "";
  int carry = 0;
  for (int i = 0; i < length; i++) {
    int k = s[0][i] - '0';
    int i1 = s[1][i] - '0';
    int i2 = s[2][i] - '0';
    if (k == 0) k = 10;
    result += (i1 + i2 + carry) % k + '0';
    carry = (i1 + i2 + carry) / k;
  }
  result += carry + '0';
  reverse(result.begin(), result.end());
  bool flag = true;
  for (auto c : result) {
    if (c == '0' && flag) continue;
    flag = false;
    cout << c;
  }
  if (flag) cout << 0;
  cout << endl;
  return 0;
}
