#include <iostream>

using namespace std;

int main() {
  int col, row;
  char c;
  cin >> col >> c;
  row = (col + 1) / 2;
  for (int i = 0; i < col; i++) {
    cout << c;
  }
  cout << endl;
  for (int i = 0; i < row - 2; i++) {
    cout << c;
    for (int j = 0; j < col - 2; j++) {
      cout << " ";
    }
    cout << c;
    cout << endl;
  }
  for (int i = 0; i < col; i++) {
    cout << c;
  }
  return 0;
}
