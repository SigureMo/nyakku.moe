#include <iostream>

using namespace std;

int main() {
  string s1, s2;
  getline(cin, s1);
  getline(cin, s2);
  for (int i = 0; i < s2.size(); i++) {
    char c = s2[i];
    char cs = c;
    if (c >= 'a' && c <= 'z') {
      cs -= 'a' - 'A';
    }
    if (s1.find(cs) != string::npos) {
      continue;
    }
    if (c >= 'A' && c <= 'Z' && s1.find('+') != string::npos) {
      continue;
      // c += 'a' - 'A'; // 并不是不能上档，而是大写字母直接打不出来了（有点不合理的说）
    }
    cout << c;
  }
  cout << endl;
  return 0;
}
