#include <iostream>
#define MAX 10000
using namespace std;

int main() {
  int n, m;
  int cnt_n = 0, cnt_m = 0;
  bool flag[MAX] = {false};
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    int id;
    scanf("%d", &id);
    flag[id] = true;
  }
  for (int i = 0; i < n; i++) {
    char name[5];
    int k;
    bool first = true;
    scanf("%s %d", name, &k);
    for (int j = 0; j < k; j++) {
      int id;
      scanf("%d", &id);
      if (flag[id]) {
        cnt_m++;
        if (first) {
          cnt_n++;
          printf("%s:", name);
        }
        first = false;
        printf(" %04d", id);
      }
    }
    if (!first) printf("\n");
  }
  printf("%d %d", cnt_n, cnt_m);
  return 0;
}
