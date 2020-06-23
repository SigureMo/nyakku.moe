/*
# 哈利·波特的考试
哈利·波特要考试了，他需要你的帮助。这门课学的是用魔咒将一种动物变成另一种动物的本事。例如将猫变成老鼠
的魔咒是haha，将老鼠变成鱼的魔咒是hehe等等。反方向变化的魔咒就是简单地将原来的魔咒倒过来念，例如ahah可
以将老鼠变成猫。另外，如果想把猫变成鱼，可以通过念一个直接魔咒lalala，也可以将猫变老鼠、老鼠变鱼的魔咒
连起来念：hahahehe。

现在哈利·波特的手里有一本教材，里面列出了所有的变形魔咒和能变的动物。老师允许他自己带一只动物去考场，
要考察他把这只动物变成任意一只指定动物的本事。于是他来问你：带什么动物去可以让最难变的那种动物（即该
动物变为哈利·波特自己带去的动物所需要的魔咒最长）需要的魔咒最短？例如：如果只有猫、鼠、鱼，则显然哈
利·波特应该带鼠去，因为鼠变成另外两种动物都只需要念4个字符；而如果带猫去，则至少需要念6个字符才能把猫
变成鱼；同理，带鱼去也不是最好的选择。

# 输入格式:
输入说明：输入第1行给出两个正整数N (≤100)和M，其中N是考试涉及的动物总数，M是用于直接变形的魔咒条数。为
简单起见，我们将动物按1~N编号。随后M行，每行给出了3个正整数，分别是两种动物的编号、以及它们之间变形需
要的魔咒的长度(≤100)，数字之间用空格分隔。

# 输出格式:
输出哈利·波特应该带去考场的动物的编号、以及最长的变形魔咒的长度，中间以空格分隔。如果只带1只动物是不可
能完成所有变形要求的，则输出0。如果有若干只动物都可以备选，则输出编号最小的那只。

# 输入样例:
```
6 11
3 4 70
1 2 1
5 4 50
2 6 50
5 6 60
1 3 70
4 6 60
3 6 80
5 1 100
2 4 60
5 2 80
``` 

# 输出样例:
```
4 70
```
*/


#include <iostream> 
#include <cstdlib>

#define MAXSIZE 100
#define INFINITY 999999

using namespace std;


class MGraph{
	public:
		int vertexNum;
		int graph[MAXSIZE][MAXSIZE];
		int dist[MAXSIZE][MAXSIZE];
		MGraph(int num){
			vertexNum = num;
		}
		void create(){
			for (int i = 0; i < vertexNum; i++)
			    for (int j = 0; j < vertexNum; j++)
			        graph[i][j] = INFINITY;
		}
		
		void insertEdge(int V, int W, int weight){
			graph[V][W] = graph[W][V] = weight;
		}
		
		bool Floyd(){
			for (int i = 0; i < vertexNum; i++)
			    for (int j = 0; j < vertexNum; j++)
			        dist[i][j] = graph[i][j];
//			this->show();
			for (int k = 0; k < vertexNum; k++)
			    for (int i = 0; i < vertexNum; i++)
			        for (int j = 0; j < vertexNum; j++)
			            if ((dist[i][k] + dist[k][j] < dist[i][j]) && i != j){
			            	dist[i][j] = dist[i][k] + dist[k][j];
			            	if (i == j && dist[i][j] < 0) // 发现负值圈 
			            	    return false;
						}
			return true;
		}
		
		void FindAnimal(){
			int animal;
			int MinDist = INFINITY;
			for (int i = 0; i < vertexNum; i++){
				int MaxDist = this->FindMaxDist(i);
//				cout << MaxDist << endl;
				if (MaxDist == INFINITY){
					cout << 0 << endl;
					return;
				}
				if (MinDist > MaxDist){
					MinDist = MaxDist;
					animal = i+1;
				}
			}
			cout << animal << " " << MinDist << endl;
		}
		
		int FindMaxDist(int vertex){
			int MaxDist = 0;
			for (int i = 0; i < vertexNum; i++){
				if (vertex != i && dist[vertex][i] > MaxDist)
				    MaxDist = dist[vertex][i];
			}
			return MaxDist;
		}
		
		void show(){
			for (int i = 0; i < vertexNum; i++){
				for (int j = 0; j < vertexNum; j++)
			        cout << this->dist[i][j] << '\t';
			    cout << endl;
			}
		}
};

int main(){
	int N, M;
	int G[N][N];
	cin >> N >> M;
	MGraph graph(N);
	graph.create();
	while (M--){
		int V, W, weight;
		cin >> V >> W >> weight;
		graph.insertEdge(V - 1, W - 1, weight);
	}
	if (!graph.Floyd()) exit(0);
//	graph.show();
	graph.FindAnimal();
	return 0;
}
