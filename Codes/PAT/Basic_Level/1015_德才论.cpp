#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct student {
  int number;
  int de;
  int cai;
} Student;

bool cmp(Student stu1, Student stu2);
void print(vector<Student> team);

int main() {
  int N, L, H;
  int cnt[4] = {0};
  Student stu;
  vector<Student> teams[4];
  scanf("%d %d %d", &N, &L, &H);
  while (N--) {
    scanf("%d %d %d", &stu.number, &stu.de, &stu.cai);
    if (stu.de < L || stu.cai < L) {}
    else if (stu.de >= H && stu.cai >= H) {
      cnt[0]++;
      teams[0].push_back(stu);
    }
    else if (stu.de >= H) {
      cnt[1]++;
      teams[1].push_back(stu);
    }
    else if (stu.de >= stu.cai) {
      cnt[2]++;
      teams[2].push_back(stu);
    }
    else {
      cnt[3]++;
      teams[3].push_back(stu);
    }
  }
  for (auto &team : teams) {
    sort(team.begin(), team.end(), cmp);
  }
  printf("%d\n", cnt[0] + cnt[1] + cnt[2] + cnt[3]);
  for (auto team : teams) {
    print(team);
  }
  return 0;
}

void print(vector<Student> team) {
  for (auto stu : team) {
    printf("%d %d %d\n", stu.number, stu.de, stu.cai);
  }
}

bool cmp(Student stu1, Student stu2) {
  if ((stu1.de + stu1.cai) != (stu2.de + stu2.cai)) {
    return (stu1.de + stu1.cai) > (stu2.de + stu2.cai);
  }
  else if (stu1.de != stu2.de) {
    return stu1.de > stu2.de;
  }
  else
    return stu1.number < stu2.number;
}
