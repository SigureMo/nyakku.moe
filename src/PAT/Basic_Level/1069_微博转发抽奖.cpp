#include <iostream>
#include <set>

using namespace std;

int main() {
  int m, n, s;
  string str;
  cin >> m >> n >> s;
  if (m < s) {
    cout << "Keep going..." << endl;
    return 0;
  }
  int i = 0;
  bool postponed = false;
  set<string> winning;
  while (i < m) {
    i++;
    cin >> str;
    if (postponed || i == s) {
      if (winning.find(str) != winning.end()) {
        postponed = true;
        s += 1;
        continue;
      }
      winning.insert(str);
      cout << str << endl;
      s += n;
      postponed = false;
    }
  }
  return 0;
}
