#include <iostream>

using namespace std;

int main() {
  int N;
  int scores[1005] = {0};
  int team_id, member_id, score;
  int max_team, max_score=-1;
  cin >> N;
  for (int i = 0; i < N; i++) {
    scanf("%d-%d %d", &team_id, &member_id, &score);
    scores[team_id] += score;
    if (scores[team_id] > max_score) {
      max_team = team_id;
      max_score = scores[team_id];
    }
  }
  cout << max_team << " " << max_score;
  return 0;
}
