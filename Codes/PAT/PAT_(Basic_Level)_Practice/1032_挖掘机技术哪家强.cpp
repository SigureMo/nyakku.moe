#include <iostream>
#define INF 100005
using namespace std;

int main() {
  int a[INF] = {0};
  int N, id, score, max_id = 0, max_score = 0;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> id >> score;
    a[id] += score;
    if (a[id] > max_score) {
      max_id = id;
      max_score = a[id];
    }
  }
  cout << max_id << " " << max_score;
  return 0;
}
