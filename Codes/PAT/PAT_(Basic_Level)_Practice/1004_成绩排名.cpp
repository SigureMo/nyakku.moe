#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  string name_max, name_min, number_max, number_min;
  int score_max = -1, score_min = 101;
  for (int i = 0; i < n; i++) {
    string name;
    string number;
    int score;
    cin >> name;
    cin >> number;
    cin >> score;
    if (score < score_min) {
      score_min = score;
      name_min = name;
      number_min = number;
    }
    if (score > score_max) {
      score_max = score;
      name_max = name;
      number_max = number;
    }
  }
  cout << name_max << " " << number_max << endl;
  cout << name_min << " " << number_min << endl;
  return 0;
}
