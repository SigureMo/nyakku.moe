#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

int main() {
  int N, cnt = 0;
  cin >> N;
  double sum = 0.0;
  char s[30];
  for (int i = 0; i < N; i++) {
    bool flag = true;
    char s1[100], s2[100];
    double a;
    stringstream ss;
    cin >> s1;
    sscanf(s1, "%lf", &a);
    sprintf(s2, "%.2lf", a);
    // cout << s1 << " " << s2 << endl;
    for (int i = 0; i < strlen(s1); i++) {
      if (s1[i] != s2[i]) {
        flag = false;
        break;
      }
    }
    flag = flag && (a <= 1000 && a >= -1000 && strlen(s1) <= strlen(s2));
    if (flag) {
      cnt++;
      sum += a;
    }
    else cout << "ERROR: " << s1 << " is not a legal number" << endl;
  }
  if (cnt == 0) cout << "The average of 0 numbers is Undefined";
  else {
    sprintf(s, "%.2lf", sum/cnt);
    if (cnt == 1) cout << "The average of 1 number is " << s;
    else cout << "The average of " << cnt << " numbers is " << s;
  }
  return 0;
}
