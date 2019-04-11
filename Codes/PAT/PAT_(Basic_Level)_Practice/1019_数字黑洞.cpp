#include <iostream>
#include <string>

using namespace std;

int get_next_num(int num, char* num_s);

int main() {
  int num;
  char num_tmp[5] = "0000";
  char* num_s;
  scanf("%d", &num);
  num_s = num_tmp;
  do {
    num = get_next_num(num, num_s);
  } while (num != 6174 && num != 0);
  return 0;
}

int get_next_num(int num, char* num_s) {
  int num1 = 0, num2 = 0, num3, tmp;
  for (int i = 3; i >= 0; i--) {
    num_s[i] = num % 10 + '0';
    num /= 10;
  }
  for (int i = 9; i >= 0; i--) {
    for (int j = 0; j < 4; j++) {
      if (num_s[j] == '0' + i) {
        num1 = num1 * 10 + i;
      }
    }
  }
  tmp = num1;
  for (int i = 0; i < 4; i++) {
    num2 = num2 * 10 + tmp % 10;
    tmp = tmp / 10;
  }
  num3 = num1 - num2;
  printf("%04d - %04d = %04d\n", num1, num2, num3);
  return num3;
}
