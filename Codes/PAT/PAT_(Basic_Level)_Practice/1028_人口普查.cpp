#include <iostream>

using namespace std;

class Person {
public:
  string name;
  int birthYear;
  int birthMonth;
  int birthDay;
  bool isValid() {
    if (birthYear > 2014) {
      return false;
    }
    else if (birthYear == 2014 && birthMonth > 9) {
      return false;
    }
    else if (birthYear == 2014 && birthMonth == 9 && birthDay > 6) {
      return false;
    }
    if (birthYear < 1814) {
      return false;
    }
    else if (birthYear == 1814 && birthMonth < 9) {
      return false;
    }
    else if (birthYear == 1814 && birthMonth == 9 && birthDay < 6) {
      return false;
    }
    return true;
  }
  bool oldThan(Person p) {
    if (this->birthYear > p.birthYear) {
      return false;
    }
    else if (this->birthYear == p.birthYear && this->birthMonth > p.birthMonth) {
      return false;
    }
    else if (this->birthYear == p.birthYear && this->birthMonth == p.birthMonth && this->birthDay > p.birthDay) {
      return false;
    }
    return true;
  }
};

int main() {
  Person pmax, pmin, tmp;
  pmax.birthYear = 3000;
  pmin.birthYear = 1000;
  int N, cnt = 0;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> tmp.name;
    scanf("%d/%d/%d", &tmp.birthYear, &tmp.birthMonth, &tmp.birthDay);
    if (tmp.isValid()) {
      cnt++;
      if (tmp.oldThan(pmax)) {
        pmax = tmp;
      }
      if (pmin.oldThan(tmp)) {
        pmin = tmp;
      }
    }
  }
  cout << cnt;
  if (cnt != 0) {
    cout << " " << pmax.name << " " << pmin.name << endl;
  }
  return 0;
}
