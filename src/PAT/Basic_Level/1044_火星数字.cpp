#include <iostream>
#include <cctype>
#include <vector>
#define NOT_FOUND -1

using namespace std;

int index(vector<string> v, string s) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == s) return i;
  }
  return NOT_FOUND;
}

int main() {
  vector<string> va = {"", "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou"};
  vector<string> vb = {"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec"};
  int n;
  string line;
  getline(cin, line);
  n = stoi(line);
  for (int i = 0; i < n; i++) {
    getline(cin, line);
    if (isdigit(line[0])) {
      int num = stoi(line);
      int a, b;
      a = num / 13;
      b = num % 13;
      if (a != 0) {
        cout << va[a];
        if (b != 0) {
          cout << " " << vb[b] << endl;
        }
        else {
          cout << endl;
        }
      }
      else {
        cout << vb[b] << endl;
      }
    }
    else {
      int a, b;
      int pos = line.find(" ");
      if (pos != NOT_FOUND) {
        a = index(va, line.substr(0, pos));
      }
      else {
        a = 0;
      }
      b = index(vb, line.substr(pos + 1));
      if (b == NOT_FOUND) {
        b = 0;
        a = index(va, line);
      }
      int num = a * 13 + b;
      cout << num << endl;
    }
  }
  return 0;
}
