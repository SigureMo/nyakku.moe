/*
# 排序
给定N个（长整型范围内的）整数，要求输出从小到大排序后的结果。

本题旨在测试各种不同的排序算法在各种数据情况下的表现。各组测试数据特点如下：

* 数据1：只有1个元素；
* 数据2：11个不相同的整数，测试基本正确性；
* 数据3：103个随机整数；
* 数据4：104个随机整数；
* 数据5：105个随机整数；
* 数据6：105个顺序整数；
* 数据7：105个逆序整数；
* 数据8：105个基本有序的整数；
* 数据9：105个随机正整数，每个数字不超过1000。

# 输入格式:
输输入第一行给出正整数N(<=10^5)，随后一行给出N个（长整型范围内的）整数，其间以空格分隔。


# 输出格式:
在一行中输出从小到大排序后的结果，数字间以1个空格分隔，行末不得有多余空格。

# 输入样例:
```
11
4 981 10 -17 0 -20 29 50 8 43 -5
``` 

# 输出样例:
```
-20 -17 -5 0 4 8 10 29 43 50 981
```
*/


#include <iostream> 
#include <cstdlib>

#define MAXSIZE 100005

using namespace std;

template<typename T>
void Bubble_Sort(T A[], int N){
	for (int P = N-1; P >= 0; P--){
		bool flag = false;
		for (int i = 0; i < P; i++){
			if (A[i] > A[i+1]){
				T t = A[i];
				A[i] = A[i+1];
				A[i+1] = t;
				flag = true;
		    }
		}
		if (!flag)
			break;
	}
}

template<typename T>
void Insertion_Sort(T A[], int N){
	int i;
	for ( int P = 1; P < N; P++){
		T Tmp = A[P];
		for (i = P; i > 0 && A[i-1] > Tmp; i--){
			A[i] = A[i-1];
		}
		A[i] = Tmp;
	}
}

template<typename T>
void Shell_Sort(T A[], int N){
	int i;
	for (int D = N/2; D > 0; D /= 2){
		for ( int P = D; P < N; P++){
		    T Tmp = A[P];
		    for (i = P; i >= D && A[i-D] > Tmp; i-=D){
			    A[i] = A[i-D];
		    }
		    A[i] = Tmp;
	    }
	}
}


int main(){
	// IN
	int N, a[MAXSIZE];
	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> a[i];
	}
	// Sort
	Shell_Sort(a, N);
	// OUT
	for (int i = 0; i < N; i++){
		cout << a[i];
		if (i < N-1){
			cout << ' ';
		}
	}
	return 0;
}
