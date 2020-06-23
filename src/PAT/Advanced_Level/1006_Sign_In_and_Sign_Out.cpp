#include <iostream>

using namespace std;

typedef struct time {
  int hour;
  int minute;
  int second;
} Time;

bool compare(Time t1, Time t2) {
  if ((t1.hour > t2.hour) ||
      (t1.hour == t2.hour && t1.minute > t2.minute) ||
      (t1.hour == t2.hour && t1.minute == t2.minute && t1.second > t2.second))
      return true;
  return false;
}

int main() {
  int M;
  cin >> M;
  Time first, last;
  string first_id, last_id;
  first.hour = 24, first.minute = 60, first.second = 60;
  last.hour = -1, last.minute = -1, last.second = -1;
  for (int i = 0; i < M; i++) {
    Time t1, t2;
    string id;
    cin >> id;
    scanf("%d:%d:%d %d:%d:%d", &t1.hour, &t1.minute, &t1.second,
                               &t2.hour, &t2.minute, &t2.second);
    if (compare(first, t1)) {
      first = t1;
      first_id = id;
    }
    if (compare(t2, last)) {
      last = t2;
      last_id = id;
    }
  }
  cout << first_id << " " << last_id << endl;
  return 0;
}
