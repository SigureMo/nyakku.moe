/*
# Saving James Bond - Hard Version
This time let us consider the situation in the movie "Live and Let Die" in which James Bond, the world's 
most famous spy, was captured by a group of drug dealers. He was sent to a small piece of land at the 
center of a lake filled with crocodiles. There he performed the most daring action to escape -- he 
jumped onto the head of the nearest crocodile! Before the animal realized what was happening, James 
jumped again onto the next big head... Finally he reached the bank before the last crocodile could 
bite him (actually the stunt man was caught by the big mouth and barely escaped with his extra thick 
boot).

Assume that the lake is a 100 by 100 square one. Assume that the center of the lake is at (0,0) and 
the northeast corner at (50,50). The central island is a disk centered at (0,0) with the diameter of 
15. A number of crocodiles are in the lake at various positions. Given the coordinates of each crocodile 
and the distance that James could jump, you must tell him a shortest path to reach one of the banks. 
The length of a path is the number of jumps that James has to make.

# Input Specification:
Each input file contains one test case. Each case starts with a line containing two positive integers 
N (≤100), the number of crocodiles, and D, the maximum distance that James could jump. Then N lines 
follow, each containing the (x,y) location of a crocodile. Note that no two crocodiles are staying at 
the same position.

# Output Specification:
For each test case, if James can escape, output in one line the minimum number of jumps he must make. 
Then starting from the next line, output the position (x,y) of each crocodile on the path, each pair 
in one line, from the island to the bank. If it is impossible for James to escape that way, simply 
give him 0 as the number of jumps. If there are many shortest paths, just output the one with the 
minimum first jump, which is guaranteed to be unique.

# Sample Input 1:
```
17 15
10 -21
10 21
-40 10
30 -50
20 40
35 10
0 -10
-25 22
40 -40
-30 30
-10 22
0 11
25 21
25 10
10 10
10 35
-30 10
``` 

# Sample Output 1:
```
4
0 11
10 21
10 35
```

# Sample Input 2:
```
4 13
-12 12
12 12
-12 -12
12 -12
```

# Sample Output 2:
```
0
```

# Test Input 1:
```
1 35
0 15
```

# Test Output 1:
```
2
15 15
```
*/


#include <iostream> 
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
//#include <stdlib.h>

using namespace std;

int D;

class Point{
	public:
		int x;
		int y;
		int dist;
		int last;
	    Point(int _x, int _y){
		    x = _x;
		    y = _y;
		    dist = -1;
		    last = -1;
	    }
	    
	    bool canJump(Point p){
	    	return pow(x - p.x, 2) + pow(y - p.y, 2) <= pow(D, 2);
		}
		
		bool firstJump(){
			return pow(x, 2) + pow(y, 2) <= pow(7.5 + D, 2);//pow(15 + D, 2);// 我才知道是直径15……所以我上次是咋通过的…… 
		}
		
		bool isSave(){
			return 50 - abs(x) <= D || 50 - abs(y) <= D;
		}
		
		int firstJumpDist(){
			return pow(x, 2) + pow(y, 2);
		}
};

vector<Point> pool;

void BFS(queue<int> q){
	while (!q.empty()){
		int v = q.front();
		q.pop();
		for (int i = 0; i < pool.size(); i++){
			if(pool[v].canJump(pool[i]) && pool[i].dist == -1){
				pool[i].dist = pool[v].dist + 1;
				pool[i].last = v;
				q.push(i);
			}
		}
	}
}

int main(){
	int N;
	cin >> N >> D;
	if (D + 15 >= 50){
		cout << 1 << endl;
		exit(0);
	}
	for (int i = 0; i < N; i++){
		int x, y;
		cin >> x >> y;
		pool.push_back(Point(x, y));
	}
	queue<int> q;
	for (int i = 0; i < N; i++){
		if (pool[i].firstJump() && pool[i].dist == -1){
			pool[i].dist = 0;
			q.push(i);
		}
	}
//	cout << "first: ";
//	for (int i = 0; i < N; i++){
//		if (pool[i].firstJump())
//		    cout << i << ' ';
//	}
//	cout << endl;
//	
//	cout << "save: ";
//	for (int i = 0; i < N; i++){
//		if (pool[i].isSave())
//		    cout << i << ' ';
//	}
//	cout << endl;
	
	BFS(q);

	int MinDist = 99999;
	int first = -1;
	int end = -1;
	int MinFirstDist = 100 * 100;
	for (int i = 0; i < N; i++){
		if (pool[i].isSave() && pool[i].dist != -1){
			if (pool[i].dist <= MinDist){
//				cout << i << endl;
				int v = i;
			    while (pool[v].last != -1){
				    v = pool[v].last;
			    }
//			    cout << "lala: " << v << endl;
			    if (pool[i].dist < MinDist || pool[v].firstJumpDist() < pool[first].firstJumpDist()){
			    	MinDist = pool[i].dist;
					first = v;
			    	end = i;
				}
//				cout << "first: " << first << " end: " << end << endl;
			}
		}
	}
//	cout << MinDist << ' '<< first << ' ' << end << endl;
//	for (int i = 0; i < N; i++){
//		cout << i << ':' << pool[i].last << "," << pool[i].dist << endl;
//	}
	if (first == -1){
		cout << 0;
	}
	else {
		int temp = end;
		stack<int> s;
		s.push(temp);
		while (pool[temp].last != -1){
			temp = pool[temp].last;
			s.push(temp);
		}
		cout << MinDist + 2 << endl;
		while (!s.empty()){
			int vertex = s.top();
			s.pop();
			cout << pool[vertex].x << ' ' << pool[vertex].y << endl;
		}
	}
	
	return 0;
}
