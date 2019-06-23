#include <iostream>

using namespace std;

int main() {
  string sign[3][11] = {""};
  int cnt[3] = {0};
  for (int i = 0; i < 3; i++) {
    string sign_line;
    getline(cin, sign_line);
    int idx = 0;
    bool flag = false;
    for (int j = 0; j < sign_line.length(); j++) {
      if (sign_line[j] == '[') {
        flag = true;
      }
      else if (sign_line[j] == ']') {
        flag = false;
        idx += 1;
      }
      else if (flag) {
        sign[i][idx] += sign_line[j];
      }
    }
    cnt[i] = idx;
  }
  int K;
  cin >> K;
  for (int i = 0; i < K; i++) {
    string out_str = "";
    bool flag = true;
    for (int j = 0; j < 5; j++) {
      int idx;
      cin >> idx;
      idx -= 1;
      int t;
      t = j < 3? j: 4-j;
      if (idx >= cnt[t] || idx < 0) {
        flag = false;
        break;
      }
      out_str += sign[t][idx];
      if (j == 0) out_str += '(';
      if (j == 3) out_str += ')';
    }
    if (flag) cout << out_str << endl;
    else cout << "Are you kidding me? @\\/@" << endl;
  }
  return 0;
}
