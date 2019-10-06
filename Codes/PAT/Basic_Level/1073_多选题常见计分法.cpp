#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  int scores[m], num_options[m], cnt[5 * m] = {0};
  bool anwsers[m][5] = {{false}};
  for (int i = 0; i < m; i++) {
    int num_anwser;
    scanf("%d %d %d", &scores[i], &num_options[i], &num_anwser);
    for (int j = 0; j < num_anwser; j++) {
      char c;
      scanf(" %c", &c);
      anwsers[i][c - 'a'] = true;
    }
  }
  for (int i = 0; i < n; i++) {
    float score = 0.0;
    for (int j = 0; j < m; j++) {
      int num_option;
      float times = 1.0;
      bool anwser[5] = {false};
      scanf("\n(%d", &num_option);
      for (int k = 0; k < num_option; k++) {
        char c;
        scanf(" %c", &c);
        anwser[c - 'a'] = true;
      }
      scanf(")");
      for (int k = 0; k < 5; k++) {
        if (anwsers[j][k] != anwser[k]) {
          cnt[j * 5 + k] += 1;
          if (anwsers[j][k] && !anwser[k]) {
            times = (times > 0.0) ? 0.5 : 0.0;
          }
          else if (!anwsers[j][k] && anwser[k]) {
            times = 0.0;
          }
        }
      }
      score += times * scores[j];
    }
    printf("%.1f\n", score);
  }
  int max = 0, idx;
  vector<int> v;
  for (int i = 0; i < 5*m; i++) {
    if (cnt[i] >= max) {
      if (cnt[i] > max) v.clear();
      idx = i;
      max = cnt[i];
      v.push_back(idx);
    }
  }
  if (max == 0) printf("Too simple\n");
  else {
    for (auto i: v) {
      printf("%d %d-%c\n", max, i/5+1, 'a'+(i%5));
    }
  }
  return 0;
}
