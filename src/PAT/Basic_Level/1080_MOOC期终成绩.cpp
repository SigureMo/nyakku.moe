#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Score{
  public:
    string id;
    int Gp;
    int Gm;
    int Gn;
    int G;
    Score (string id, int Gp, int Gm, int Gn, int G) {
      this->id = id;
      this->Gp = Gp;
      this->Gm = Gm;
      this->Gn = Gn;
      this->G = G;
    }
};

int main() {
  int P, M, N;
  map<string, int[4]> score_map;
  vector<Score> score_vector;
  cin >> P >> M >> N;
  int type = 0;
  for (int i = 0; i < P + M + N; i++) {
    string id;
    int score;
    cin >> id >> score;
    if (i == P || i == P+M) type++;
    if (score_map.find(id) == score_map.end()) {
      for (int j = 0; j < 3; j++) {
        score_map[id][j] = -1;
      }
    }
    score_map[id][type] = score;
  }
  for (auto it = score_map.begin(); it != score_map.end(); it++) {
    it->second[3] = it->second[1] > it->second[2] ?
                    it->second[1] * 0.4 + it->second[2] * 0.6 + 0.5 : it->second[2];
    if (it->second[0] >= 200 && it->second[3] >= 60) {
      score_vector.push_back(Score(it->first, it->second[0], it->second[1], it->second[2], it->second[3]));
    }
  }
  auto cmp = [](Score a, Score b) -> bool {
    if (a.G != b.G) return a.G > b.G;
    else return a.id < b.id;
  };
  sort(score_vector.begin(), score_vector.end(), cmp);
  for (auto &it : score_vector) {
    cout << it.id << " " << it.Gp << " " << it.Gm << " " << it.Gn << " " << it.G << endl;
  }
  return 0;
}
