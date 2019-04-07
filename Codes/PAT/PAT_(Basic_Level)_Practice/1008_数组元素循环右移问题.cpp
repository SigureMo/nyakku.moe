#include <iostream>

using namespace std;

// 一步到位算法，直接将数据传到目标位置
// 移动必定构成一个环路，但构成的环路的大小是多大，一共需要几个环路才能将整个数组遍历完呢？
// 这里使用 get_offset 获取最小的偏移量 offset（> 0），这样我们一共只需要遍历 offset 次就可以完成对整个数组的调整了

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
  if (range % step == 0) {
    return step;
  }
  else {
    int offset = ((range / step + 1) * step) % range;
    return get_offset(step, offset);
  }
}
