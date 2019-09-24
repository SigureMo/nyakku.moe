#include <iostream>
#include <math.h>

using namespace std;

int main() {
  double r1, p1, r2, p2;
  double a1, b1, a2, b2, a, b;
  scanf("%lf %lf %lf %lf", &r1, &p1, &r2, &p2);
  a1 = r1 * cos(p1);
  b1 = r1 * sin(p1);
  a2 = r2 * cos(p2);
  b2 = r2 * sin(p2);
  a = a1*a2 - b1*b2;
  b = a1*b2 + a2*b1;
  if (fabs(a) < 0.005) a = 0;
  if (fabs(b) < 0.005) b = 0;
  printf("%.2lf", a);
  if (b >= 0) cout << "+";
  printf("%.2lfi", b);
  return 0;
}
