#include <iostream>
#include <string>

using namespace std;

int main() {
  string s1, s2, s = "";
  char c;
  cin >> s1;
  cin >> s2;
  for (int i = 0, j = 0; j < s1.size(); j++) {
    for (; s2[i] != s1[j] && j < s1.size(); j++) {
      c = s1[j];
      if (c >= 'a' && c <= 'z') {
        c -= 'a' - 'A';
      }
      if (s.find(c) == string::npos) {
        s += c;
      }
    }
    if (i != s2.size() - 1) {
      i++;
    }
  }
  cout << s;
  return 0;
}
