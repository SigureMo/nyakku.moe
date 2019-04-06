#include <iostream>

using namespace std;

int main() {
  string s;
  getline(cin, s);
  int end = s.size();
  for (int i = s.size() - 1; i >= -1; i--) {
    if (s[i] == ' ' || i == -1) {
      cout << s.substr(i+1, end - i);
      end = i-1;
      if (i != -1) {
        cout << " ";
      }
    }
  }
  return 0;
}
