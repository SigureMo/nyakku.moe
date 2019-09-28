#include <iostream>
#include <vector>

using namespace std;

typedef struct question {
  int num_total;
  int num_right;
  int score;
  bool anwser[5];
} *Question;

int main() {
  int N, M;
  cin >> N >> M;
  Question q[M];
  int wrong[105] = {0};
  int num_max = 0;
  vector<int> maxWrongs;
  for (int i = 0; i < M; i++) {
    q[i] = (Question)malloc(sizeof(struct question));
    scanf("%d %d %d", &q[i]->score, &q[i]->num_total, &q[i]->num_right);
    // clear anwser array
    for (int j = 0; j < 5; j++) {
      q[i]->anwser[j] = false;
    }
    for (int j = 0; j < q[i]->num_right; j++) {
      char c;
      scanf(" %c", &c);
      q[i]->anwser[c - 'a'] = true;
    }
  }
  for (int i = 0; i < N; i++) {
    string s;
    int score = 0;
    for (int j = 0; j < M; j++) {
      int num_choice;
      bool isRight = true;
      scanf("\n(%d", &num_choice);
      bool anwser[5] = {false};
      for (int k = 0; k < num_choice; k++) {
        char c;
        scanf(" %c", &c);
        anwser[c - 'a'] = true;
      }
      scanf(")");
      for (int k = 0; k < 5; k++) {
        if (q[j]->anwser[k] != anwser[k]) {
          isRight = false;
          wrong[j]++;
          break;
        }
      }
      if (isRight) score += q[j]->score;
    }
    printf("%d\n", score);
  }
  for (int i = 0; i < M; i++) {
    if (wrong[i] > num_max) {
      maxWrongs.clear();
      num_max = wrong[i];
      maxWrongs.push_back(i+1);
    }
    else if (wrong[i] == num_max) {
      maxWrongs.push_back(i+1);
    }
  }
  if (num_max == 0)
    printf("Too simple");
  else {
    printf("%d", num_max);
    for (int i = 0; i < maxWrongs.size(); i++) {
      printf(" %d", maxWrongs[i]);
    }
  }
  return 0;
}