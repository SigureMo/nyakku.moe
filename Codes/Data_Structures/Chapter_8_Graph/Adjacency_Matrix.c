#include<stdio.h>
#include<stdlib.h>

typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;
	int Ne;
	WeightType G[MaxVertexNum][MaxVertexNum];
	DataType Data[MaxVertexNum];
}; 

typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;
	WeightType Weight;
};

typedef PtrToENode Edge;

typedef PtrToGNode MGraph;
typedef int Vertex;

MGraph CreateGraph(int VertexNum){
	Vertex V, W;
	MGraph Graph;
	
	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	for (V=0; V<Graph->Nv; V++)
	    for (W=0; W<Graph->Nv; W++)
	        Graph->G[V][W] = 0;
	
	return Graph;
}

void InsertEdge(MGraph Graph, Edge E){
	Graph->G[E->V1][E->V2] = E->Weight;
	Graph->G[E->V2][E->V1] = E->Weight; // ÎŞÏòÍ¼ 
}
