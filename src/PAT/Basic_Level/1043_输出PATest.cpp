#include <iostream>
using namespace std;

int main() {
  int a[128] = {0};
  bool flag = true;
  string s, PATest = "PATest";
  cin >> s;
  for (int i = 0; i < s.size(); i++) {
    a[s[i]]++;
  }
  while (flag) {
    flag = false;
    for (int i = 0; i < 6; i++) {
      char c = PATest[i];
      if (a[c] > 0) {
        flag = true;
        a[c]--;
        cout << c;
      }
    }
  }
  return 0;
}
