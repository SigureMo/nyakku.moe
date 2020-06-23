#include <iostream>

using namespace std;

int main() {
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int k, num = -1;
    cin >> k;
    for (int j = 1; j < 10; j++) {
      string s1, s2;
      s1 = to_string(k);
      s2 = to_string(j * k * k);
      if (s2.substr(s2.length()-s1.length()) == s1) {
        num = j;
        break;
      }
    }
    if (num == -1) cout << "No" << endl;
    else cout << num << " " << k * k * num << endl;
  }
  return 0;
}
