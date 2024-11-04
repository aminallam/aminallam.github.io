// GROUP:   X
// ID:      XXXXXXXX
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;

	void Initialize();
	void Destroy();
	void AddLast(Value v);
	void RemoveLast();
	Value& operator[](int i);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap
{
	int* pos; // pos[v]=i where a[i].v=v, otherwise pos[v]=-1
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);

	void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n); // n is required to allocate and initialize pos[]
	void Destroy();
	void Print();
	int Child(int i);
	int Parent(int i);
	Elem GetFirst();
	Elem RetrieveFirst();
	void Add(Elem e);
	void MoveUp(int ind);
	void MoveDown(int ind);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int		v;
	int		w;
};

struct Node
{
	Array<Edge> adj;

	void Initialize();
	void Destroy();
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n);
	void Destroy();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
