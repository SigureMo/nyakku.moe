#include <iostream>
using namespace std;
typedef long long llong;

int main() {
  string s;
  cin >> s;
  int len = s.size();
  int P_cnt = 0, T_cnt = 0;
  llong PAT_cnt = 0;
  int T_After[len];
  // 预先计算各位置之前有多少 P 和之后有多少 T，那么只要该位置是 A 就构成了一个 PAT
  // 将 A 的遍历合并入 P 的遍历，以提高效率
  for (int i = len - 1; i >= 0; i--) {
    if (s[i] == 'T') T_cnt++;
    T_After[i] = T_cnt;
  }
  for (int i = 0; i < len; i++) {
    if (s[i] == 'P') P_cnt++;
    if (s[i] == 'A') PAT_cnt += P_cnt * T_After[i];
  }
  cout << PAT_cnt % 1000000007;
  return 0;
}
