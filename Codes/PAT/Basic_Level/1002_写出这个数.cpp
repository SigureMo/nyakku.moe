#include <iostream>
#include <string>

using namespace std;

int main() {
  string s;
  cin >> s;
  string spell_array[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
  int sum = 0;
  for (int i = 0; i < s.length(); i++) {
    sum += s[i] - '0';
  }
  string num = std::to_string(sum);
  for (int i = 0; i < num.length(); i++) {
    if (i != 0) {
      cout << " ";
    }
    cout << spell_array[num[i] - '0'];
  }
  return 0;
}

