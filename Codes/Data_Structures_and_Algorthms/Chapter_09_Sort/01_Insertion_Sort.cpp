#include <iostream>

using namespace std;

// SIMPLE_INSERT
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
// SIMPLE_INSERT
// HALF_INSERT
template<typename T>
void Half_Insertion_Sort(T a[], int N) {
	int i, low, high, mid;
	for (int P = 1; P < N; P++) {
		T tmp = a[P];
    low = 0;
    high = P;
    while (low <= high) {
      mid = (low + high) / 2;
      if (tmp < a[mid]) high = mid - 1;
      else low = mid + 1;
    }
		for (i = P; i > low; i--) {
			a[i] = a[i-1];
		}
		a[i] = tmp;
	}
}
// HALF_INSERT
// SHELL_INSERT
template<typename T>
void Shell_Sort(T a[], int N) {
	int i;
	for (int D = N/2; D > 0; D /= 2) {
		for (int P = D; P < N; P++){
		    T tmp = a[P];
		    for (i = P; i >= D && a[i-D] > tmp; i-=D) {
			    a[i] = a[i-D];
		    }
		    a[i] = tmp;
	    }
	}
}
// SHELL_INSERT
// BUBBLE_SWAP
template<typename T>
void Bubble_Sort(T a[], int N) {
	for (int P = N-1; P >= 0; P--) {
		bool flag = false;
		for (int i = 0; i < P; i++) {
			if (a[i] > a[i+1]) {
				T t = a[i];
				a[i] = a[i+1];
				a[i+1] = t;
				flag = true;
		  }
		}
		if (!flag)
			break;
	}
}
// BUBBLE_SWAP

template<typename T>
bool check(T a[], T b[], int N) {
  for (int i = 0; i < N; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

template<typename T>
void print(T a[], int N) {
  for (int i = 0; i < N; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main(int argc, char* argv[]) {
  string mode = argv[1];
  int a[] = {4, 981, 10, -17, 0, -20, 29, 50, 8, 43, -5};
  int b[] = {-20, -17, -5, 0, 4, 8, 10, 29, 43, 50, 981};
  int N = sizeof(a)/sizeof(a[0]);
  if (mode == "insertion") {
    Insertion_Sort(a, N);
  }
  else if (mode == "half_insertion") {
    Half_Insertion_Sort(a, N);
  }
  else if (mode == "shell") {
    Shell_Sort(a, N);
  }
  else if (mode == "bubble") {
    Bubble_Sort(a, N);
  }
  else {
    cout << "Invaild mode!";
    return 1;
  }
  cout << boolalpha << "check " << (check(a, b, N) ? "passed" : "failed") << endl;
  return 0;
}
