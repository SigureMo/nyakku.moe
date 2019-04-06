#include <iostream>

using namespace std;

int main() {
  int a1_cnt = 0, a1 = 0;
  int a2_cnt = 0, a2 = 0;
  int a3_cnt = 0, a3 = 0;
  int a4_cnt = 0, a4 = 0;
  int a5_cnt = 0, a5 = 0;
  int n;
  cin >> n;
  while (n--) {
    int num;
    cin >> num;
    if (num % 5 == 0 && num % 2 == 0) {
      a1_cnt++;
      a1 += num;
    }
    if (num % 5 == 1) {
      if (a2_cnt % 2 == 0) {
        a2 += num;
      }
      else {
        a2 -= num;
      }
      a2_cnt++;
    }
    if (num % 5 == 2) {
      a3_cnt++;
      a3++;
    }
    if (num % 5 == 3) {
      a4_cnt++;
      a4 += num;
    }
    if (num % 5 == 4) {
      if (num > a5) {
        a5_cnt++;
        a5 = num;
      }
    }
  }
  if (a1_cnt) {
    cout << a1;
  }
  else {
    cout << "N";
  }
  cout << " ";

  if (a2_cnt) {
    cout << a2;
  }
  else {
    cout << "N";
  }
  cout << " ";

  if (a3_cnt) {
    cout << a3;
  }
  else {
    cout << "N";
  }
  cout << " ";

  if (a4_cnt) {
    printf("%.1f", 1.0 * a4 / a4_cnt);
  }
  else {
    cout << "N";
  }
  cout << " ";

  if (a5_cnt) {
    cout << a5;
  }
  else {
    cout << "N";
  }
  return 0;
}
