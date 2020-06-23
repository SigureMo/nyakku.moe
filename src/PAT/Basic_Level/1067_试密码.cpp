#include <iostream>

using namespace std;

int main() {
  string password;
  int max_cnt;
  string s;
  cin >> password >> max_cnt;
  getline(cin, s);
  while (true) {
    // string s;
    getline(cin, s);
    if (s == "#") break;
    else if (s == password) {
      cout << "Welcome in" << endl;
      break;
    }
    else {
      cout << "Wrong password: " << s << endl;
    }
    max_cnt--;
    if (max_cnt == 0) {
      cout << "Account locked" << endl;
      break;
    }
  }
  return 0;
}
