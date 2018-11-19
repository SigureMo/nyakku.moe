#include<stdio.h>
#include<stdlib.h>

typedef struct GNode *PtrToGNode;
// 这个嘛 就是图的组织结点 
struct GNode{
	int Nv;
	int Ne;
	AdjList G; 
}; 

// 这个是图每个链表的头结点指针（构成的数组） 
typedef struct Vnode{
	PtrToAdjVNode FirstEdge;
	DataType Data;
} AdjList[MaxVertexNum];

typedef struct ENode *PtrToENode;
typedef struct AdjVNode *PtrToAdhVNode;

// 这就是真的结点啦 
struct AdjVNode{
	Vertex AdjV;
	WeightType Weight;
	PtrToAdjVNode Next;
}; 

typedef PtrToGNode LGraph;
typedef int Vertex;

LGraph CreateGraph(int VertexNum){
	Vertex V, W;
	LGraph Graph;
	
	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	for (V=0; V<Graph->Nv; V++)
	    Graph->G[V].FirstEdge = NULL;
	
	return Graph;
}

void InsertEdge(MGraph Graph, Edge E){
	PtrToAdjVNode NewNode;
	 
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
	
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}
