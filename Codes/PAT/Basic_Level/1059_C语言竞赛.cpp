#include <iostream>
#define MAX 10000
using namespace std;

bool isPrime(int num) {
  if (num < 2) return false;
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int N, K;
  cin >> N;
  int ranking[MAX] = {0};
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    int id = stoi(s);
    ranking[id] = i+1;
  }
  cin >> K;
  for (int i = 0; i < K; i++) {
    string s;
    cin >> s;
    cout << s << ": ";
    int id = stoi(s);
    if (ranking[id] == 0) {
      cout << "Are you kidding?" << endl;
    }
    else if (ranking[id] == 1) {
      cout << "Mystery Award" << endl;
      ranking[id] = -1;
    }
    else if (isPrime(ranking[id])) {
      cout << "Minion" << endl;
      ranking[id] = -1;
    }
    else if (ranking[id] == -1) {
      cout << "Checked" << endl;
    }
    else {
      cout << "Chocolate" << endl;
      ranking[id] = -1;
    }
  }
  return 0;
}