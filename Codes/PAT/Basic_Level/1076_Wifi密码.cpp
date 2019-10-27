#include <iostream>

using namespace std;

int main() {
  int N;
  scanf("%d\n", &N);
  for (int i = 0; i < N; i++) {
    char a[4], r[4];
    scanf("%c-%c %c-%c %c-%c %c-%c\n",
          &a[0], &r[0], &a[1], &r[1], &a[2], &r[2], &a[3], &r[3]);
    for (int j = 0; j < 4; j++) {
      if (r[j] == 'T') {
        cout << a[j] - 'A' + 1;
        break;
      }
    }
  }
  return 0;
}
