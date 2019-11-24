#include <stdio.h>

int main(){
  // LONG_TO_SHORT
  int x1 = 0x7fffffff;
  short y1 = (short) x1;
  printf("%hx\n", y1);        // ffff
  // LONG_TO_SHORT
  // SHORT_TO_LONG
  short x2 = 0x8fff;
  int y2 = (int) x2;
  printf("%x\n", y2);         // ffff8fff
  // SHORT_TO_LONG
  // INT_TO_FLOAT
  int x3 = 0x7fffffff;
  float y3 = (float) x3;
  printf("%d %f\n", x3, y3);  // 2147483647 2147483648.000000
  // INT_TO_FLOAT
  return 0;
}
