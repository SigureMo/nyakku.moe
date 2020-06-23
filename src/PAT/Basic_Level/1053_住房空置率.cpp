#include <iostream>

using namespace std;

int main() {
  int N, D;
  float e;
  cin >> N >> e >> D;
  int empty = 0, may_empty = 0;
  for (int i = 0; i < N; i++) {
    int K, empty_cnt = 0;
    cin >> K;
    for (int j = 0; j < K; j++) {
      float E;
      cin >> E;
      if (E < e) empty_cnt++;
    }
    if (K > D && empty_cnt > K/2.0) empty++;
    else if (K <= D && empty_cnt > K/2.0) may_empty++;
  }
  printf("%.1f%% %.1f%%", 1.0 * may_empty / N * 100, 1.0 * empty / N * 100);
  return 0;
}
