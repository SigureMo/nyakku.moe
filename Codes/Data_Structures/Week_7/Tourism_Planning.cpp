/*
# 旅游规划
有了一张自驾旅游路线图，你会知道城市间的高速公路长度、以及该公路要收取的过路费。现在需要你写一个程序，
帮助前来咨询的游客找一条出发地和目的地之间的最短路径。如果有若干条路径都是最短的，那么需要输出最便宜的
一条路径。

# 输入格式:
输入说明：输入数据的第1行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为
0~(N?1)；M是高速公路的条数；S是出发地的城市编号；D是目的地的城市编号。随后的M行中，每行给出一条高速公
路的信息，分别是：城市1、城市2、高速公路长度、收费额，中间用空格分开，数字均为整数且不超过500。输入保
证解的存在。

# 输出格式:
在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。

# 输入样例:
```
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
``` 

# 输出样例:
```
3 40
```
*/


#include <iostream> 
#include <cstdlib>
#include <vector>

#define MAXSIZE 505
#define INFINITY 999999

using namespace std;

class Way{
	public:
		int price;
		int dist;
		int nextCity;
		Way(int city, int d, int p){
			nextCity = city;
			dist = d;
			price = p;
		}
};

vector<Way> map[MAXSIZE];
bool collected[MAXSIZE];
int dist[MAXSIZE];
int path[MAXSIZE];
int price[MAXSIZE];

void Dijkstra(int city){
	while (true){
		int d = INFINITY;
		int v;
		for (int i = 0; i < map[city].size(); i++){
			if (map[city][i].dist < d && !collected[map[city][i].nextCity]){
				d = map[city][i].dist;
				v = map[city][i].nextCity;
			}
		}
//		cout << v << endl; 
		if (d == INFINITY) break;
		collected[v] = true;
		for (int i = 0; i < map[v].size(); i++){
			if (!collected[map[v][i].nextCity]){
//				cout << "bls" << map[v][i].nextCity << endl;
				if ((dist[v] + map[v][i].dist < dist[map[v][i].nextCity]) ||
				    (dist[v] + map[v][i].dist == dist[map[v][i].nextCity] && price[v] + map[v][i].price < price[map[v][i].nextCity])){
					dist[map[v][i].nextCity] = dist[v] + map[v][i].dist;
					path[map[v][i].nextCity] = v;
					price[map[v][i].nextCity] = price[v] + map[v][i].price;
				}
			}
		}
	}
}

int main(){
	int N, M, S, D;
	cin >> N >> M >> S >> D;
	for (int i = 0; i < N; i++){
		collected[i] = false;
		dist[i] = INFINITY;
		path[MAXSIZE] = -1;
		price[MAXSIZE] = 0;
	}
	while (M--){
		int city1, city2, d, p;
		cin >> city1 >> city2 >> d >> p;
		map[city1].push_back(Way(city2, d, p));
		map[city2].push_back(Way(city1, d, p));
	}

	dist[S] = 0;
	collected[S] = true;
	for (int i = 0; i < map[S].size(); i++){
		dist[map[S][i].nextCity] = map[S][i].dist;
		price[map[S][i].nextCity] = map[S][i].price;
	}
//	for (int i = 0; i < N; i++){
//    	cout << i << ' '<< dist[i] << ' ' << path[i] << ' ' << price[i] << endl;
//	}
	Dijkstra(S);
//	for (int i = 0; i < N; i++){
//		cout << i << " : ";
//		for (int j = 0; j < map[i].size(); j++){
//			cout << ' ' << map[i][j].nextCity;
//		}
//		cout << endl;
//	}
//    for (int i = 0; i < N; i++){
//    	cout << i << ' '<< dist[i] << ' ' << path[i] << ' ' << price[i] << endl;
//	}
	cout << dist[D] << ' ' << price[D] << endl;
	
	return 0;
}
