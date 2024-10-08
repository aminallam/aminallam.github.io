// GROUP:   5
// ID:      20202020
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    My full name

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
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);

	void Initialize(bool (*_IsBefore)(Elem&, Elem&));
	void Destroy();
	int Child(int i);
	int Parent(int i);
	void MoveUp(int ind);
	void MoveDown(int ind);
	void Add(Elem e);
	Elem GetFirst();
	Elem RetrieveFirst();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
	return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
