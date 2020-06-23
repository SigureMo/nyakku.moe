#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int main() {
  int n, m;
  map<int, set<int>> mp;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    mp[a].insert(b);
    mp[b].insert(a);
  }
  for (int i = 0; i < m; i++) {
    int k;
    set<int> s;
    bool flag = true;
    scanf("%d", &k);
    for (int j = 0; j < k; j++) {
      int tmp;
      scanf("%d", &tmp);
      s.insert(tmp);
    }
    for (auto it = s.begin(); it != s.end(); it++) {
      if (mp.find(*it) != mp.end()) {
        set<int> inter;
        set_intersection(mp[*it].begin(), mp[*it].end(), s.begin(), s.end(), inserter(inter, inter.begin()));
        if (!inter.empty()) {
          flag = false;
          break;
        }
      }
    }
    printf("%s\n", flag ? "Yes" : "No");
  }
  return 0;
}
