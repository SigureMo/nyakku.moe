#include <iostream>
#include <map>
#define MAX 100000

using namespace std;

int main() {
  int n, m, cnt = 0;
  bool guests[MAX] = {false}, dogs[MAX] = {false};
  bool first = true;
  map<int, int> cp;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    cp[a] = b;
    cp[b] = a;
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int c;
    scanf("%d", &c);
    guests[c] = true;
  }
  for (int i = 0; i < MAX; i++) {
    if (guests[i] && (cp.find(i) == cp.end() || !guests[cp[i]])) {
      dogs[i] = true;
      cnt++;
    }
  }
  printf("%d\n", cnt);
  for (int i = 0; i < MAX; i++) {
    if (dogs[i]) {
      if (first) first = false;
      else printf(" ");
      printf("%05d", i);
    }
  }
  return 0;
}
