#include <iostream>
#include <string>

using namespace std;

int main() {
  const string WEEK[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
  const string HOUR = "0123456789ABCDEFGHIJKLMN";
  string str1, str2, str3, str4;
  bool flag = false;
  string day;
  int hour, minute;
  cin >> str1 >> str2 >> str3 >> str4;
  for (int i = 0; i < min(str1.size(), str2.size()); i++) {
    if (!flag) {
      if (str1[i] == str2[i] && str1[i] >= 'A' && str2[i] <= 'G') {
        day = WEEK[str1[i] - 'A'];
        flag = true;
      }
    }
    else {
      if (str1[i] == str2[i] && ((str1[i] >= '0' && str1[i] <= '9') || (str1[i] >= 'A' && str1[i] <= 'N'))) {
        hour = HOUR.find(str1[i]);
        break;
      }
    }
  }
  for (int i = 0; i < min(str3.size(), str4.size()); i++) {
    if (str3[i] == str4[i] && ((str3[i] >= 'A' && str3[i] <= 'Z') || (str3[i] >= 'a' && str3[i] <= 'z'))) {
      minute = i;
      break;
    }
  }
  cout << day;
  printf(" %02d:%02d",hour, minute);
  return 0;
}
