#include <iostream>

using namespace std;

int main() {
  int a, b, c;
  bool first = true;
  cin >> a >> b;
  c = a + b;
  string s = to_string(c);
  for (int i = 0; i < s.length(); i++) {
    char c = s[i];
    cout << c;
    if (c == '-') continue;
    else if((s.length()-i-1) % 3 == 0 && i!=s.length()-1)
      cout << ',';
  }
  cout << endl;
  return 0;
}
