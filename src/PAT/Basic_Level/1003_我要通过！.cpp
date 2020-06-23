#include <iostream>

using namespace std;

bool check_string(string s);

int main() {
  int n;
  cin >> n;
  string s;
  while (n > 0) {
    cin >> s;
    if (check_string(s)) {
      cout << "YES" << endl;
    }
    else {
      cout << "NO" << endl;
    }
    n--;
  }
  return 0;
}

bool check_string(string s) {
  int pre_A = 0, mid_A = 0, post_A = 0;
  // Only P A T
  for (int i = 0; i < s.length(); i++) {
    if (s[i] != 'P' && s[i] != 'A' && s[i] != 'T') {
      return false;
    }
  }
  // P_num == 1, T_num == 1
  if (s.rfind("P") != s.find("P") or s.rfind("T") != s.find("T")) {
    return false;
  }
  pre_A = s.find("P");
  mid_A = s.find("T") - pre_A - 1;
  post_A = s.length() - pre_A - mid_A - 2;

  // mid_A != 0
  if (mid_A == 0) {
    return false;
  }

  // pre_A * mid_A == post_A
  if (pre_A * mid_A != post_A) {
    return false;
  }
  else {
    return true;
  }
}
