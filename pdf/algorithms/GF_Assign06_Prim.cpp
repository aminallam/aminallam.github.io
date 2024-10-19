// GROUP:   X
// ID:      XXXXXXXX
// Assign:  06
// Assign:  Prim
// UVA:     534
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

struct Edge
{
	int		v;  // id of the adjacent node
	double	w;  // edge weight = distance between the two nodes
};

struct Node
{
	int x,y; // x and y coordinates of the node
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

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
