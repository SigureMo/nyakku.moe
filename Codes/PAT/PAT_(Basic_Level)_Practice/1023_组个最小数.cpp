#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int& a, int& b);

int main() {
  vector<int> v;
  for (int i = 0; i < 10; i++) {
    int num;
    cin >> num;
    while (num--) {
      v.push_back(i);
    }
  }
  sort(v.begin(), v.end(), cmp);
  if (v[0] == 0) {
    for (int i = 0; i < v.size(); i++) {
      if (v[i] != 0) {
        v[0] = v[i];
        v[i] = 0;
        break;
      }
    }
  }
  for (int i = 0; i < v.size(); i++) {
    cout << v[i];
  }
  return 0;
}

bool cmp(int& a, int& b) {
  return a < b;
}
