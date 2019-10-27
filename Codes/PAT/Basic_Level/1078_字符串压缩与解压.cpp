#include <iostream>
#include <cctype>

using namespace std;

int main() {
  char method;
  string raw;
  cin >> method;
  getchar();
  getline(cin, raw);
  if (method == 'C') {
    char pre = raw[0];
    int cnt = 1;
    for (int i = 1; i < raw.length(); i++) {
      if (raw[i] == pre) cnt++;
      else {
        if (cnt > 1) cout << cnt;
        cout << pre;
        pre = raw[i];
        cnt = 1;
      }
    }
    if (cnt > 1) cout << cnt;
    cout << pre;
  }
  else if (method == 'D') {
    int num = 0;
    for (int i = 0; i < raw.length(); i++) {
      if (isdigit(raw[i]))
        num = num * 10 + raw[i] - '0';
      else {
        if (num)
          for (int j = 0; j < num; j++)
            cout << raw[i];
        else
          cout << raw[i];
        num = 0;
      }
    }
  }
  return 0;
}
