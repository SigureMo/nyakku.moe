#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    vector<int> v;
    int g2;
    cin >> g2;
    for (int j = 0; j < N-1; j++) {
      int score;
      cin >> score;
      if (score <= M && score >= 0) {
        v.push_back(score);
      }
    }

    sort(v.begin(), v.end());
    int sum = 0;
    for (int j = 1; j < v.size() - 1; j++) {
      sum += v[j];
    }
    float g1 = 1.0 * sum / (v.size() - 2);
    cout << (int)((g1 + g2) / 2 + 0.5) << endl;
  }
  return 0;
}
