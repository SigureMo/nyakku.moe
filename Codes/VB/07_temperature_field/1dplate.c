#include <stdio.h>

// 初窥有限差分法

int main() {
  double dx, ds, s, s1, tf, t0, p, cp, h, l, f1, f2, fx;
  double t1[1000], t2[1000];
  FILE *fp;
  fp = fopen("1dplate.dat", "w");

  /* 获取淬火时间 */
  printf("输入淬火时间 s1 = ");
  scanf("%lf", &s1);

  /* 输入相关系数 */
  int n1 = 101; // 空间单元数
  dx = 0.025; // 空间单元
  ds = 0.003; // 时间单元
  tf = 20.0; // 终温
  t0 = 860.0; // 始温
  p = 7.8; // 密度
  cp = 0.50; // 比热
  l = 0.30; // 热导率
  h = 0.2; // 边界换热系数
  fx = l * ds / (cp * p * dx *dx); // 计算傅里叶数

  /* 赋初值 */
  int i;
  for (i = 0; i < n1; i++) {
    t1[i] = t0;
  }

  /* 计算各时刻 */
  for (s=0.0; s1 - s > 1e-6; s+=ds) {
    for (i = 1; i < n1 - 1; i++) {
      t2[i] = t1[i] + fx * (t1[i+1] - 2*t1[i] + t1[i-1]);
    }
    t2[0] = t1[0] + 2*fx*(t1[1] - t1[0]);
    t2[n1-1] = t1[n1-1] + 2*fx*(t1[n1-2] - t1[n1-1]) + 2*fx*dx*h/l*(tf - t1[n1-1]);
    for (i = 0; i < n1; i++) {
      t1[i] = t2[i];
    }
    printf("%.2lf %.2lf %.2lf %.2lf %.2lf\n", s, t1[0], t1[50], t1[92], t1[100]);
    fprintf(fp, "%.2lf %.2lf %.2lf %.2lf %.2lf\n", s, t1[0], t1[50], t1[92], t1[100]);
  }
  fclose(fp);

  printf("Done!");
  return 0;
}
