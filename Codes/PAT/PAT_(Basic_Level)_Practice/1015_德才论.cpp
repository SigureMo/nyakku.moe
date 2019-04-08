#include <stdio.h>

// 为什么直接插入排序会比先 push_back 后 vector 慢？还没弄明白，速度慢了不是一点点，这样的算法甚至过不了 4、5

struct student {
  int number;
  int de;
  int cai;
};

typedef struct student Student;
Student team1[100000];
Student team2[100000];
Student team3[100000];
Student team4[100000];

void print(Student team[], int cnt);
int cmp(Student* stu1, Student* stu2);
void insert(Student team[], Student stu, int cnt);

int main() {
  int N, L, H;
  int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
  Student stu;
  scanf("%d %d %d", &N, &L, &H);
  while (N--) {
    scanf("%d %d %d", &stu.number, &stu.de, &stu.cai);
    if (stu.de < L || stu.cai < L) {}
    else if (stu.de >= H && stu.cai >= H) {
      cnt1++;
      insert(team1, stu, cnt1);
    }
    else if (stu.de >= H) {
      cnt2++;
      insert(team2, stu, cnt2);
    }
    else if (stu.de >= stu.cai) {
      cnt3++;
      insert(team3, stu, cnt3);
    }
    else {
      cnt4++;
      insert(team4, stu, cnt4);
    }
  }
  printf("%d\n", cnt1 + cnt2 + cnt3 + cnt4);
  print(team1, cnt1);
  print(team2, cnt2);
  print(team3, cnt3);
  print(team4, cnt4);
  return 0;
}

void print(Student team[], int cnt) {
  for (int i = 0; i < cnt; i++) {
    printf("%d %d %d\n", team[i].number, team[i].de, team[i].cai);
  }
}

int cmp(Student* stu1, Student* stu2) {
  if ((stu1->de + stu1->cai) != (stu2->de + stu2->cai)) {
    return (stu1->de + stu1->cai) > (stu2->de + stu2->cai);
  }
  else if (stu1->de != stu2->de) {
    return stu1->de > stu2->de;
  }
  else
    return stu1->number < stu2->number;
}

void insert(Student team[], Student stu, int cnt) {
  for (; cnt > 0 && cmp(&stu, &team[cnt-1]); cnt--) {
    team[cnt] = team[cnt-1];
  }
  team[cnt] = stu;
}
