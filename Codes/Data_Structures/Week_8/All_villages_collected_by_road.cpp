/*
# 公路村村通现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路的成本，求使每个村落都
有公路连通所需要的最低成本。

# 输入格式:
输入数据包括城镇数目正整数N（≤1000）和候选道路数目M（≤3N）；随后的M行对应M条道路，每行给出3个正整数，
分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。为简单起见，城镇从1到N编号。

# 输出格式:
输出村村通需要的最低成本。如果输入数据不足以保证畅通，则输出?1，表示需要建设更多公路。

# 输入样例:
```
6 15
1 2 5
1 3 3
1 4 7
1 5 4
1 6 2
2 3 4
2 4 6
2 5 2
2 6 6
3 4 6
3 5 1
3 6 1
4 5 10
4 6 8
5 6 3
``` 

# 输出样例:
```
12
```
*/


#include <iostream> 
#include <cstdlib>
#include <vector>

#define MAXSIZE 100
#define INFINITY 999999

using namespace std;

class Edge{
	public:
		Edge(int village1, int village2, int d): v1(village1), v2(village2), dist(d){};
		int v1;
		int v2;
		int dist;
};

int MST[1000];
vector<Edge> E;

int main(){
	int N, M;
	cin >> N >> M;
	for (int i = 0; i < M; i++){
		int v1, v2, dist;
		cin >> v1 >> v2 >> dist;
		E.push_back(Edge(v1, v2, dist));
	}
	return 0;
}
