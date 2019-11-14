#include <iostream>

using namespace std;

// :::
template<typename T>
void Insertion_Sort(T a[], int N){
	int i;
	for (int P = 1; P < N; P++){
		T tmp = a[P];
		for (i = P; i > 0 && a[i-1] > tmp; i--){
			a[i] = a[i-1];
		}
		a[i] = tmp;
	}
}
// :::

template<typename T>
bool check(T a[], T b[], int N) {
  for (int i = 0; i < N; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

int main() {
  int a[] = {4, 981, 10, -17, 0, -20, 29, 50, 8, 43, -5};
  int b[] = {-20, -17, -5, 0, 4, 8, 10, 29, 43, 50, 981};
  int N = sizeof(a)/sizeof(a[0]);
  Insertion_Sort(a, N);
  cout << boolalpha << "check " << (check(a, b, N) ? "passed" : "failed") << endl;
  return 0;
}
