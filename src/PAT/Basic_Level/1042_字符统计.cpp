#include <iostream>
using namespace std;

int main() {
  string s;
  int a[128] = {0};
  int max_cnt = 0;
  char max_char;
  getline(cin, s);
  for (int i = 0; i < s.size(); i++) {
    char c = s[i];
    if (c >= 'A' && c <= 'Z') {
      c += 'a' - 'A';
    }
    a[c]++;
  }
  for (char c = 'a'; c <= 'z'; c++) {
    if (a[c] > max_cnt) {
      max_cnt = a[c];
      max_char = c;
    }
  }
  cout << max_char << " " << max_cnt;
  return 0;
}
