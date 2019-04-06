#include <iostream>

using namespace std;

int get_offset(int range, int step);

int main() {
  int range, step, offset;
  cin >> range >> step;
  int a[range];
  if (step >= range) {
    step %= range;
  }
  for (int i = 0; i < range; i++) {
    cin >> a[i];
  }

  if (step != 0) {
    offset = get_offset(range, step);
    for (int i = 0; i < offset; i++) {
      bool flag = true;
      for (int j = i; j != i || flag; ) {
        flag = false;
        int next_j = (j + step) % range;
        int tmp = a[next_j];
        a[next_j] = a[i];
        a[i] = tmp;
        j = next_j;
      }
    }
  }

  for (int i = 0; i < range; i++) {
    if (i != 0) {
      cout << " ";
    }
    cout << a[i];
  }
  return 0;
}

int get_offset(int range, int step) {
  // cout << range << " " << step << endl;
  if (range % step == 0) {
    return step;
  }
  else {
    int offset = ((range / step + 1) * step) % range;
    if (offset == 1) {
      return 1;
    }
    else {
      return get_offset(step, offset);
    }
  }
}
