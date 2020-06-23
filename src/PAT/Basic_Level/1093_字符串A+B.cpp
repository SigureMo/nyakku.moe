#include <iostream>

using namespace std;

int main() {
  string s, s1, s2;
  bool flag[128] = {false};
  getline(cin, s1);
  getline(cin, s2);
  s = s1 + s2;
  for (int i = 0; i < s.size(); i++) {
    char c = s[i];
    if (!flag[c]) {
      flag[c] = true;
      cout << c;
    }
  }
  cout << endl;
  return 0;
}
