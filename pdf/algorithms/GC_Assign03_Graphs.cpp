// GROUP:   X
// ID:      XXXXXXXX
// Assign:  03
// Assign:  Graphs
// UVA:     924
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

struct Node
{
	Array<int> adj;

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

template <class Type>
struct Queue
{
	int f, n;
	Type* elems;

	void Initialize(int size);
	void Destroy();
	void Add(Type t);
	Type Pop();
	Type Peek();
	int Num();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
