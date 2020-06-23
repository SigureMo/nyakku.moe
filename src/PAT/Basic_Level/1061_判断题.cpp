#include <iostream>

using namespace std;

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  int scores[M], anwsers[M];
  for (int i = 0; i < M; i++) {
    scanf("%d", &scores[i]);
  }
  for (int i = 0; i < M; i++) {
    scanf("%d", &anwsers[i]);
  }
  for (int i = 0; i < N; i++) {
    int a[M], score = 0;
    for (int j = 0; j < M; j++) {
      scanf("%d", &a[j]);
      if (a[j] == anwsers[j])
        score += scores[j];
    }
    printf("%d\n", score);
  }
  return 0;
}
