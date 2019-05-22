#include <iostream>
using namespace std;

typedef struct {
  string id;
  int seatNumber1;
  int seatNumber2;
} Student;

int main () {
  int N, M;
  cin >> N;
  Student S[N];
  for (int i = 0; i < N; i++) {
    cin >> S[i].id >> S[i].seatNumber1 >> S[i].seatNumber2;
  }
  cin >> M;
  for (int i = 0; i < M; i++) {
    int num1;
    cin >> num1;
    for (int j = 0; j < N; j++) {
      if (S[j].seatNumber1 == num1) {
        cout << S[j].id << " " << S[j].seatNumber2 << endl;
        break;
      }
    }
  }
  return 0;
}
