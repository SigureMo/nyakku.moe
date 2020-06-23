#include <iostream>
#include <string>

using namespace std;

int main() {
  int sum = 0;
  string words[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  string s, s_sum;
  cin >> s;
  for (int i = 0; i < s.length(); i++) {
    sum += s[i] - '0';
  }
  s_sum = to_string(sum);
  for (int i = 0; i < s_sum.length(); i++) {
    if (i != 0) cout << " ";
    cout << words[s_sum[i] - '0'];
  }
  cout << endl;
  return 0;
}
