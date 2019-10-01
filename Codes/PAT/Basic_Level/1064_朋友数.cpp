#include <iostream>
#define ID_MAX 37
using namespace std;

int main() {
  int n, cnt = 0;
  bool first = true, flag[ID_MAX] = {false};
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int num, id = 0;
    scanf("%d", &num);
    while (num) {
      id += num % 10;
      num /= 10;
    }
    flag[id] = true;
  }
  for (int i = 0; i < ID_MAX; i++) {
    if (flag[i]) cnt++;
  }
  printf("%d\n", cnt);
  for (int i = 0; i < ID_MAX; i++) {
    if (flag[i]) {
      if (first) first = false;
      else printf(" ");
      printf("%d", i);
    }
  }
  return 0;
}
