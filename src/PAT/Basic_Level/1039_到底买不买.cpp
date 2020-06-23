#include <iostream>

using namespace std;

int main() {
  int have[128] = {0};
  int need[128] = {0};
  int surplus = 0;
  string have_string, need_string;
  cin >> have_string;
  cin >> need_string;
  for (int i = 0; i < have_string.size(); i++) {
    have[have_string[i]]++;
  }
  for (int i = 0; i < need_string.size(); i++) {
    need[need_string[i]]++;
  }
  for (int i = 0; i < 128; i++) {
    if (have[i] < need[i]) {
      if (surplus > 0) surplus = 0;
      surplus += have[i] - need[i];
    }
    else if (have[i] > need[i] && surplus >= 0) {
      surplus += have[i] - need[i];
    }
  }
  if (surplus >= 0) cout << "Yes " << surplus;
  else cout << "No " << -surplus;
  return 0;
}
